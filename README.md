# ESP32 Health Monitoring System 🚑📡

This project is a **real-time health monitoring system** using an **ESP32**, **BMP280 temperature/pressure sensor**, and a **pulse sensor**, integrated with **Firebase Realtime Database**.

## 🔧 Features

- 🌡️ Measures ambient **temperature** using BMP280.
- ❤️ Monitors **heart rate** (BPM) using PulseSensor.
- 📶 Sends real-time data to **Firebase**.
- 🚨 Triggers alerts in Firebase if:
  - Temperature exceeds **38°C**
  - BPM exceeds **120**

## 🧰 Hardware Used

- [ESP32 Dev Board]
- [BMP280 Sensor (I2C)]
- [PulseSensor]
- Jumper wires, Breadboard
- Internet access via Wi-Fi

## 🛠️ Wiring

| Component     | ESP32 Pin  |
|---------------|------------|
| BMP280 SDA    | GPIO 21    |
| BMP280 SCL    | GPIO 22    |
| Pulse Sensor  | GPIO 34 (Analog Input) |

## 🧪 Firebase Structure (Realtime Database)

```json
{
  "numbers": {
    "number1": 85,     // BPM
    "number3": "37.65" // Temperature in Celsius
  },
  "sensors": {
    "sensor1": 0, // Heart rate alert (1 if >120 BPM)
    "sensor3": 0  // Temperature alert (1 if >38°C)
  }
}
