# DreamLink 🌙

> **Where Physical Meets Meaning**

**DreamLink** เป็น Arduino library สำหรับสร้างหุ่นยนต์ที่ "รู้สึก" และ "เข้าใจ" โลก ผ่านการเชื่อมโยงระหว่างการรับรู้ทางกายภาพ (sensors) กับความหมาย (meaning-driven behavior)

Part of [MDS (Meaning-Driven Systems)](https://github.com/v1b3x0r/mds) ecosystem

---

## ✨ Features

- 🎯 **Declarative Rules** - เขียน behavior แบบ readable เหมือน JavaScript
- 🧠 **Embodied Cognition** - ออกแบบจาก physical sensing ตั้งแต่ต้น
- 🎨 **Ready-to-Use Patterns** - 5 behavior patterns สำเร็จรูป
- 🔌 **Magic Drivers (BYOD)** - รองรับ Sensor ทุกรุ่นด้วยบรรทัดเดียว! (VL53L0X, BME280, etc.)
- 🔊 **Audio Feedback** - สื่อสารผ่านเสียง Beep/Tone
- 🔧 **Fluent Configuration** - ตั้งค่าบอร์ดง่ายๆ ด้วย API แบบลูกโซ่

---

## 🚀 Quick Start

### 1. ติดตั้ง Library
Copy folder `DreamLink` ไปที่ `Documents/Arduino/libraries/`

### 2. Hello World (Magic Driver Edition 🪄)
ตัวอย่างการใช้ **ESP32-S3** กับ **VL53L0X (ToF)**:

```cpp
#include <DreamLink.h>
#include <Adafruit_VL53L0X.h> // 1. Include manufacturer's lib

DreamLink probe;
Adafruit_VL53L0X lox; // 2. Declare sensor object

// 3. INSTALL DRIVER (The Magic Line!)
INSTALL_SENSOR_DRIVER(probe, DISTANCE, lox.readRangeStatus() == 4 ? 999 : lox.readRange());

void setup() {
  Serial.begin(115200);
  lox.begin(); // Init sensor
  
  // 4. Configure Board & Start
  probe.configure()
       .setBuzzer(27) // Atom Echo speaker
       .begin();

  // 5. Define Behavior
  probe.when(DISTANCE < 20).then(BEEP, 100);
  probe.when(DISTANCE > 50).then(FORWARD, 100);

  probe.wakeup();
}

void loop() {
  probe.live();
}
```

---

## 🛠 Hardware Configuration

### Board Presets
DreamLink รองรับบอร์ดหลากหลายรุ่นผ่าน `BoardConfig`:

```cpp
// ใช้ Preset ที่มีให้
probe.begin(Boards::ATOM_ECHO);
probe.begin(Boards::M5STICK_C_PLUS);
probe.begin(Boards::ESP32_S3_DEVKIT);
```

### Fluent Configuration (Custom Board)
ถ้าใช้บอร์ดแปลกๆ หรือต่อสายเอง:

```cpp
probe.configure()
     .setMotorA(25, 26, 27) // PWM, IN1, IN2
     .setMotorB(32, 33, 14)
     .setUltrasonic(18, 19) // Trig, Echo
     .setBuzzer(12)         // Buzzer Pin
     .begin();
```

---

## 🔊 Audio Feedback
สั่งให้ Probe ส่งเสียงได้ง่ายๆ:

```cpp
// ร้องปี๊บ 500ms เมื่อเจอสิ่งกีดขวาง
probe.when(DISTANCE < 10).then(BEEP, 500);
```

---

## 📖 API Reference

### Lifecycle
```cpp
probe.configure();  // เริ่มตั้งค่า
probe.begin();      // เริ่มต้นระบบ
probe.wakeup();     // เริ่มทำงาน (Reflex Engine)
probe.sleep();      // หยุดทำงาน
probe.live();       // ใส่ใน loop()
```

### Magic Drivers
```cpp
// ติดตั้ง Driver สำหรับ Sensor ประเภทต่างๆ
INSTALL_SENSOR_DRIVER(probe, DISTANCE, expression);
INSTALL_SENSOR_DRIVER(probe, BATTERY, expression);
```

### Rules
```cpp
probe.when(CONDITION).then(ACTION, PARAM);
// Example:
probe.when(BATTERY < 20).then(STOP);
```

---

## 🤝 Contributing
DreamLink is open-source. Pull requests are welcome!

License: MIT
