#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>

#define SS_PIN 10
#define RST_PIN 9
#define SD_CS 4
#define LED_PIN 7

MFRC522 rfid(SS_PIN, RST_PIN);
RTC_DS3231 rtc;

File file;

// -------- USER DATABASE --------
struct User {
  String uid;
  String name;
};

User users[] = {
  {"a1b2c3d4", "Adith"},
  {"12345678", "John"}
};

int userCount = 2;

// -------- SETUP --------
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_PIN, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("RTC ERROR");
    while (1);
  }

  if (!SD.begin(SD_CS)) {
    Serial.println("SD ERROR");
    while (1);
  }

  Serial.println("System Ready");
}

// -------- GET TIME --------
String getTime() {
  DateTime now = rtc.now();
  return String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) +
         " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

// -------- FIND USER --------
String getName(String uid) {
  for (int i = 0; i < userCount; i++) {
    if (users[i].uid == uid) return users[i].name;
  }
  return "Unknown";
}

// -------- CHECK ENTRY/EXIT --------
bool hasOpenEntry(String uid) {
  file = SD.open("attendance.csv", FILE_READ);

  if (!file) return false;

  String lastLine = "";
  while (file.available()) {
    lastLine = file.readStringUntil('\n');
  }
  file.close();

  if (lastLine.indexOf(uid) != -1 && lastLine.endsWith(",")) {
    return true;  // Entry exists but no exit
  }
  return false;
}

// -------- WRITE ENTRY --------
void writeEntry(String name, String uid, String time) {
  file = SD.open("attendance.csv", FILE_WRITE);

  file.print(name);
  file.print(",");
  file.print(uid);
  file.print(",");
  file.print(time);
  file.println(",");  // Empty exit

  file.close();
}

// -------- UPDATE EXIT --------
void updateExit(String uid, String time) {
  File readFile = SD.open("attendance.csv", FILE_READ);
  File tempFile = SD.open("temp.csv", FILE_WRITE);

  while (readFile.available()) {
    String line = readFile.readStringUntil('\n');

    if (line.indexOf(uid) != -1 && line.endsWith(",")) {
      line += time;  // add exit time
    }

    tempFile.println(line);
  }

  readFile.close();
  tempFile.close();

  SD.remove("attendance.csv");
  SD.rename("temp.csv", "attendance.csv");
}

// -------- LOOP --------
void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  String name = getName(uid);
  String time = getTime();

  Serial.println("UID: " + uid);
  Serial.println("Name: " + name);

  if (hasOpenEntry(uid)) {
    updateExit(uid, time);
    Serial.println("EXIT recorded");
  } else {
    writeEntry(name, uid, time);
    Serial.println("ENTRY recorded");
  }

  // LED feedback
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

  rfid.PICC_HaltA();
}
