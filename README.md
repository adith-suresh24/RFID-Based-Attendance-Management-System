# 📡 RFID-Based Attendance Management System (Arduino UNO + SD Card)

## 📌 Project Overview

This project is an **RFID-based Attendance Management System** built using Arduino UNO. It allows automatic recording of attendance using RFID cards and stores the data in a **CSV file on an SD card**, making it completely independent (no computer required).

The system records both **Entry and Exit time** for each user and provides visual feedback using an LED.

---

## 🎯 Features

* 📡 RFID-based identification
* 💾 Data stored directly in SD card (CSV format)
* ⏱️ Entry and Exit time tracking
* 🔄 Automatic entry/exit detection
* 💡 LED indication for successful scan
* 🧠 Works without a computer (standalone system)

---

## 🛠️ Hardware Components

* Arduino UNO
* MFRC522 RFID Module
* RFID Cards/Tags
* SD Card Module
* Micro SD Card
* DS3231 RTC Module (for real-time clock)
* Green LED
* 220Ω Resistor
* Jumper Wires

---

## 🔌 Circuit Connections

### 📡 RFID Module (MFRC522)

| RFID Pin | Arduino Pin |
| -------- | ----------- |
| SDA      | D10         |
| SCK      | D13         |
| MOSI     | D11         |
| MISO     | D12         |
| RST      | D9          |
| GND      | GND         |
| 3.3V     | 3.3V        |

---

### 💾 SD Card Module

| SD Pin | Arduino Pin |
| ------ | ----------- |
| CS     | D4          |
| MOSI   | D11         |
| MISO   | D12         |
| SCK    | D13         |
| VCC    | 5V          |
| GND    | GND         |

---

### ⏰ RTC Module (DS3231)

| RTC Pin | Arduino Pin |
| ------- | ----------- |
| VCC     | 5V          |
| GND     | GND         |
| SDA     | A4          |
| SCL     | A5          |

---

### 💡 LED

* D7 → Resistor → LED → GND

---

## 📂 Project Structure

```
project-folder/
│
├── main.ino
├── attendance.csv   (auto-created on SD card)
└── README.md
```

---

## ⚙️ Setup Instructions

1. Connect all components as per wiring diagram
2. Insert SD card into module
3. Upload the Arduino code to UNO
4. Power the system

---

## 🧪 How It Works

1. User scans RFID card
2. Arduino reads UID
3. UID is matched with stored user database
4. System checks:

   * If no open record → **Entry Time recorded**
   * If already entered → **Exit Time recorded**
5. Data is saved in `attendance.csv`
6. LED turns ON to confirm scan

---

## 📊 CSV Output Format(Example)

```
Name,UID,Entry Time,Exit Time
Adith,a1b2c3d4,2026-04-07 09:00:00,2026-04-07 15:00:00
John,12345678,2026-04-07 09:05:00,
```

---

## 🧠 Entry/Exit Logic

* First scan → Entry recorded
* Second scan → Exit recorded
* Stored in the same row
* If exit is missing, system assumes user is still inside

---

## ⚠️ Limitations

* Limited storage based on SD card
* Requires proper scanning order (Entry → Exit)
* Basic UID matching (no encryption)

---

## 🔮 Future Improvements

* Add LCD display (show name + time)
* Add buzzer for sound alerts
* Add fingerprint authentication
* Wireless sync using WiFi (ESP32)
* Mobile app integration
* Daily attendance report generation

---

## 👨‍💻 Author

Adith Suresh

---

## 📄 Disclaimer

This project is for educational purposes and basic automation use only.
