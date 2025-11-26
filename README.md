# DreamLink 🌙

> **Where Physical Meets Meaning**

**DreamLink** เป็น Arduino library สำหรับสร้างหุ่นยนต์ที่ "รู้สึก" และ "เข้าใจ" โลก ผ่านการเชื่อมโยงระหว่างการรับรู้ทางกายภาพ (sensors) กับความหมาย (meaning-driven behavior)

Part of [MDS (Meaning-Driven Systems)](https://github.com/v1b3x0r/mds) ecosystem

---

## ✨ Features

- 🎯 **Declarative Rules** - เขียน behavior แบบ readable เหมือน JavaScript
- 🧠 **Embodied Cognition** - ออกแบบจาก physical sensing ตั้งแต่ต้น
- 🎨 **Ready-to-Use Patterns** - 5 behavior patterns สำเร็จรูป
- 🔧 **Extensible** - เพิ่ม sensor/action ใหม่ได้ง่าย
- 📡 **MDS-Ready** - เตรียมพร้อมเชื่อม semantic bus (soon)
- ⚡ **Embedded-Friendly** - ไม่มี malloc, RAM น้อย, รวดเร็ว

---

## 🚀 Quick Start

### 1. ติดตั้ง Library

ดูคู่มือติดตั้งแบบละเอียดที่: **[INSTALL.md](INSTALL.md)**

**TL;DR:**
```bash
# macOS/Linux
cp -r fese-probe-261125 ~/Documents/Arduino/libraries/DreamLink

# Windows: Copy folder ไปที่
# C:\Users\<YourName>\Documents\Arduino\libraries\DreamLink
```

เปิด Arduino IDE ใหม่ → File → Examples → DreamLink

### 2. Hello World

```cpp
#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();

  probe.when(DISTANCE < 20).then(TURN_RIGHT, 120);
  probe.when(DISTANCE > 50).then(FORWARD, 100);

  probe.wakeup();
}

void loop() {
  probe.live();
}
```

**เท่านี้หุ่นก็หลบกำแพงได้แล้ว!** 🎉

### 3. ใช้ Pattern สำเร็จรูป

ไม่อยากเขียน rule เอง? ใช้ pattern ที่มีให้:

```cpp
#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();
  probe.behave("explorer");  // ใช้ pattern สำเร็จรูป
  probe.wakeup();
}

void loop() {
  probe.live();
}
```

Patterns ที่มี:
- **explorer** - เดินสำรวจแบบสุ่ม
- **obstacle-avoidance** - หลบกำแพงธรรมดา
- **cautious** - เดินระวังๆ ช้าๆ หยุดบ่อย
- **wall-follower** - เดินตามกำแพงด้านขวา
- **energy-saver** - ประหยัดแบต เดินช้าเมื่อแบตต่ำ

---

## 📖 API Reference

### Lifecycle Methods

```cpp
probe.begin();      // เริ่มต้นระบบ (sensors, motors)
probe.wakeup();     // เริ่มทำงาน (start reflex engine)
probe.sleep();      // หยุดชั่วคราว
probe.live();       // main loop (เรียกใน loop())
```

### Simple API (Recommended)

```cpp
// เพิ่ม rule แบบ readable
probe.when(DISTANCE < 20).then(TURN_RIGHT, 120);

// เพิ่ม probability
probe.when(ALWAYS).then(TURN_LEFT, 80).sometimes(10); // 10%

// ใช้ pattern สำเร็จรูป
probe.behave("explorer");
```

### Advanced API

```cpp
// อ่าน sensor
int distance = probe.readDistance();  // cm
int battery = probe.readBattery();    // %

// ควบคุมแบบ manual
probe.forward(100);
probe.turnLeft(80);
probe.stop();

// Debug
probe.enableDebug(true);
probe.printRules();
probe.identify("probe-001");
```

---

## 📐 สถาปัตยกรรม (Architecture)

```
┌─────────────────────────────────────────────┐
│         DREAMLINK LIBRARY                   │
│  ┌────────────┐         ┌────────────┐     │
│  │  Rules[]   │────────>│   Reflex   │     │
│  │  (array)   │         │   Engine   │     │
│  └────────────┘         └──────┬─────┘     │
│                                 │           │
│          ┌──────────────────────┴─────┐    │
│          ▼                            ▼    │
│  ┌──────────────┐            ┌─────────┐  │
│  │   Condition  │            │ Action  │  │
│  │   Checker    │            │Executor │  │
│  └──────┬───────┘            └────┬────┘  │
└─────────┼─────────────────────────┼───────┘
          │                         │
          ▼                         ▼
┌─────────────────┐       ┌──────────────────┐
│  Sensor Layer   │       │  Actuator Layer  │
│  - Distance     │       │  - Movement      │
│  - Battery      │       │  - Motor         │
│  - Light        │       │  - LED/Buzzer    │
│  - Humidity     │       │  - Servo         │
└─────────────────┘       └──────────────────┘
```

---

## 📁 โครงสร้างไฟล์

```
DreamLink/
├── src/
│   ├── DreamLink.h/cpp      ← Main API
│   ├── globals.h/cpp        ← Global instances
│   ├── behavior/
│   │   ├── types.h          ← SensorType, ActionType, Rule struct
│   │   ├── pattern.h        ← Pattern สำเร็จรูป (5 แบบ)
│   │   └── reflex.h/cpp     ← Reflex engine
│   ├── core/
│   │   ├── board.hpp        ← GPIO configuration
│   │   ├── motor.hpp/cpp    ← Motor control (TB6612)
│   │   ├── movement.hpp/cpp ← Movement primitives
│   │   └── sensor.h/cpp     ← Sensor abstractions
│   └── net/
│       ├── client.h         ← (Future) WiFi client
│       └── worldlog.h       ← (Future) MDS World sync
│
├── examples/
│   ├── 01_BasicMovement/
│   ├── 02_ObstacleAvoidance/
│   ├── 03_Explorer/
│   ├── 04_Patterns/
│   └── 05_Advanced/
│
├── library.properties       ← Arduino library metadata
├── keywords.txt             ← IDE syntax highlighting
├── README.md                ← ไฟล์นี้
├── LIBRARY_README.md        ← Full documentation
├── INSTALL.md               ← Installation guide
└── LICENSE                  ← MIT License
```

---

## 🔧 Hardware Setup

### อุปกรณ์ที่ต้องใช้:
- ESP32 DevKit v1 (หรือ ESP32-S3)
- TB6612FNG motor driver
- DC motors x2 (left + right)
- HC-SR04 ultrasonic sensor
- Battery (LiPo 3.7V recommended)
- Voltage divider (10kΩ + 10kΩ) สำหรับวัดแบต

### การต่อขา (Pinout):

| Component        | ESP32 Pin | TB6612 Pin |
|------------------|-----------|------------|
| Motor A PWM      | GPIO 25   | PWMA       |
| Motor A IN1      | GPIO 26   | AIN1       |
| Motor A IN2      | GPIO 27   | AIN2       |
| Motor B PWM      | GPIO 32   | PWMB       |
| Motor B IN1      | GPIO 33   | BIN1       |
| Motor B IN2      | GPIO 14   | BIN2       |
| Motor Standby    | GPIO 12   | STBY       |
| Ultrasonic TRIG  | GPIO 18   | -          |
| Ultrasonic ECHO  | GPIO 19   | -          |
| Battery Monitor  | GPIO 34   | -          |

แก้ไขได้ที่: [src/core/board.hpp](src/core/board.hpp)

---

## 🧪 ตัวอย่างการใช้งาน

### ตัวอย่าง 1: หุ่นหลบกำแพง
```cpp
#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();

  probe.when(DISTANCE < 10).then(STOP, 0);
  probe.when(DISTANCE < 25).then(TURN_RIGHT, 120);
  probe.when(DISTANCE > 40).then(FORWARD, 100);

  probe.wakeup();
}

void loop() {
  probe.live();
}
```

### ตัวอย่าง 2: สุ่มเดิน (Random Walk)
```cpp
#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();

  probe.when(DISTANCE < 20).then(TURN_RIGHT, 120);
  probe.when(DISTANCE > 50).then(FORWARD, 100);
  probe.when(ALWAYS).then(TURN_LEFT, 90).sometimes(20);   // 20%
  probe.when(ALWAYS).then(TURN_RIGHT, 90).sometimes(20);  // 20%

  probe.wakeup();
}

void loop() {
  probe.live();
}
```

### ตัวอย่าง 3: ประหยัดแบต
```cpp
#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();

  probe.when(BATTERY < 10).then(STOP, 0);
  probe.when(BATTERY < 30).then(FORWARD, 50);    // ช้าๆ
  probe.when(BATTERY > 50).then(FORWARD, 120);
  probe.when(DISTANCE < 20).then(TURN_RIGHT, 100);

  probe.wakeup();
}

void loop() {
  probe.live();
}
```

---

## 🧩 Sensor Types

```cpp
DISTANCE    // ultrasonic (cm)
BATTERY     // battery level (%)
LIGHT       // LDR (0-1023)
HUMIDITY    // DHT22 (0-100%)
TEMPERATURE // DHT22 (celsius)
NONE        // สำหรับ ALWAYS condition
```

---

## 🎯 Action Types

```cpp
TURN_RIGHT   // เลี้ยวขวา
TURN_LEFT    // เลี้ยวซ้าย
FORWARD      // เดินหน้า
BACKWARD     // ถอยหลัง
STOP         // หยุด
WAIT         // รอ (milliseconds)
LOG_EVENT    // เขียน log (Serial)
BEEP         // เสียงบี๊บ (ถ้ามี buzzer)
```

---

## 🐛 Debug Tips

### ดูค่า Sensor แบบ real-time:
```cpp
void setup() {
  probe.begin();
  probe.enableDebug(true);  // ← เปิด debug mode
  // ...
}
```

เปิด Serial Monitor (115200 baud) จะเห็น:
```
========================================
   DreamLink - Where Physical Meets Meaning
========================================

[DreamLink] System initialized
[DreamLink] Awakened with 3 rules
[SENSORS] Distance: 35cm | Battery: 78%
[REFLEX] avoid-wall triggered → action: TURN_RIGHT
```

---

## 🎨 วิธีเพิ่ม Sensor ใหม่

1. เพิ่ม enum ใน [src/behavior/types.h](src/behavior/types.h):
```cpp
enum SensorType {
  DISTANCE,
  BATTERY,
  MY_NEW_SENSOR, // ← เพิ่มตรงนี้
};
```

2. เขียน class ใน [src/core/sensor.h](src/core/sensor.h):
```cpp
class MyNewSensor {
public:
  MyNewSensor();
  int readValue();
};
```

3. เพิ่ม case ใน [src/behavior/reflex.cpp](src/behavior/reflex.cpp):
```cpp
int Reflex::readSensor(SensorType type) {
  switch (type) {
    case MY_NEW_SENSOR:
      return myNewSensor.readValue();
    // ...
  }
}
```

4. ใช้ใน rule:
```cpp
probe.when(MY_NEW_SENSOR > 50).then(FORWARD, 100);
```

---

## 🎯 วิธีเพิ่ม Action ใหม่

1. เพิ่ม enum ใน [src/behavior/types.h](src/behavior/types.h):
```cpp
enum ActionType {
  FORWARD,
  TURN_LEFT,
  MY_NEW_ACTION, // ← เพิ่มตรงนี้
};
```

2. เพิ่ม case ใน [src/behavior/reflex.cpp](src/behavior/reflex.cpp):
```cpp
void Reflex::executeAction(Rule& r) {
  switch (r.action) {
    case MY_NEW_ACTION:
      // ทำอะไรสักอย่าง
      break;
    // ...
  }
}
```

3. ใช้ใน rule:
```cpp
probe.when(DISTANCE < 30).then(MY_NEW_ACTION, 0);
```

---

## 🌐 อนาคต (Roadmap)

### v1.x (Current)
- ✅ Reflex-based behavior
- ✅ Pattern library
- ✅ Sensor abstraction
- ✅ JS-friendly API

### v2.x (Coming Soon)
- [ ] WiFi + MDS World integration
- [ ] `probe.broadcastContext()` → Semantic Bus
- [ ] `probe.subscribe()` → listen to world events
- [ ] Event logger → world.log

### v3.x (Future)
- [ ] Affect layer (simple emotion)
- [ ] Memory system
- [ ] Multi-probe coordination
- [ ] Learning layer (optional)

---

## 🧩 ปรัชญา (Philosophy)

DreamLink ไม่ใช่แค่ library สำหรับควบคุมหุ่นยนต์

มันเป็น **embodied cognition framework** ที่:
- ความหมายเกิดจาก interaction กับโลกจริง
- Behavior ไม่ใช่ hard-coded แต่เป็น **declarative interpretation**
- Physical body = interface กับโลกความหมาย (MDS World)
- MDS **suggests context**, DreamLink **interprets and decides**
- Agency อยู่ที่ probe, ไม่ใช่ที่ cloud

> **"มันไม่เดา, มันไม่เชื่อ, มันแค่เข้าใจสิ่งที่มีอยู่จริง"**

---

## 📚 Documentation

- **[INSTALL.md](INSTALL.md)** - Installation guide
- **[LIBRARY_README.md](LIBRARY_README.md)** - Full API reference
- **[examples/](examples/)** - 5 complete examples

---

## 📝 License

MIT License - ใช้อะไรก็ได้ แต่อย่าลืมเครดิต 😊

---

## 🙏 Credits

- Inspired by [Dreamflow](https://github.com/v1b3x0r/dreamflow) (JS version)
- Part of [MDS (Meaning-Driven Systems)](https://github.com/v1b3x0r/mds) ecosystem
- Built with ❤️ for embodied AI research

---

**Happy hacking! 🌙✨**
