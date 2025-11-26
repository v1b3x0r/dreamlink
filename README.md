# FESE Probe - Dreamflow-Lite 🤖

**First Embodied Sensing Entity** - หุ่นยนต์ที่ใช้ Dreamflow-Lite behavior engine บน ESP32

---

## 📐 สถาปัตยกรรม (Architecture)

```
┌─────────────────────────────────────────────┐
│         DREAMFLOW-LITE ENGINE               │
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

## 🎯 Dreamflow-Lite คืออะไร?

**Dreamflow-Lite** เป็น DSL (Domain-Specific Language) น้อยๆ ที่ออกแบบมาให้:
- เขียนง่าย อ่านง่าย (แม้แต่เด็ก 7 ขวบก็เข้าใจ!)
- ทำงานบน ESP32 โดยไม่ต้องใช้ JavaScript engine
- แก้ไขพฤติกรรมหุ่นยนต์โดยไม่ต้องโค้ด C++ ซับซ้อน
- รองรับ probability (บางครั้งทำ, บ่อยครั้งทำ, เสี่ยงโชคทำ)

### ตัวอย่าง Rule

```cpp
{"avoid-wall", DISTANCE, LESS_THAN, 20, TURN_RIGHT, 120, 100}
```

อ่านว่า:
- **"avoid-wall"** = ชื่อ rule (สำหรับ debug)
- **DISTANCE** = เซนเซอร์วัดระยะ
- **LESS_THAN** = ตัวดำเนินการ (<)
- **20** = threshold (20 เซนติเมตร)
- **TURN_RIGHT** = action (เลี้ยวขวา)
- **120** = parameter (ความเร็ว 120/255)
- **100** = probability (100% = ทำทุกครั้ง)

แปลเป็นภาษาคน:
> **"ถ้าเจอกำแพงใกล้กว่า 20cm → เลี้ยวขวาที่ความเร็ว 120"**

---

## 🚀 Quick Start

### 1. ติดตั้งบน Arduino IDE

1. เปิด Arduino IDE
2. ติดตั้ง board support สำหรับ ESP32:
   - File → Preferences → Additional Board Manager URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Tools → Board → ESP32 Arduino → ESP32 Dev Module
4. เปิดไฟล์ `main.ino`
5. Upload!

### 2. ปรับแต่งพฤติกรรม

แก้ไขไฟล์ [behavior/rules.h](behavior/rules.h):

```cpp
Rule myRules[] = {
  // ชื่อ           sensor    op          threshold  action       param  prob
  {"avoid-wall",   DISTANCE, LESS_THAN,  20,        TURN_RIGHT,  120,   100},
  {"explore",      DISTANCE, GREATER,    50,        FORWARD,     100,   100},
  {"random-spin",  NONE,     ALWAYS,     0,         TURN_LEFT,   150,   10}, // 10%
};
```

### 3. ใช้ Pattern สำเร็จรูป

ไม่อยากเขียน rule เอง? ใช้ pattern ที่มีให้:

```cpp
#include "pattern.h"
Rule myRules[] = ObstacleAvoidance::rules;
const int myRulesCount = ObstacleAvoidance::count;
```

Patterns ที่มี:
- **ObstacleAvoidance** - หลบกำแพง
- **Explorer** - เดินสำรวจแบบสุ่ม
- **EnergySaver** - ประหยัดแบตเตอรี่
- **WallFollower** - เดินตามกำแพง
- **Cautious** - เดินระวังๆ ช้าๆ

---

## 📁 โครงสร้างไฟล์

```
fese-probe-261125/
├── core/
│   ├── board.hpp          ← การตั้งค่าขา GPIO
│   ├── motor.hpp/cpp      ← ควบคุมมอเตอร์ (TB6612)
│   ├── movement.hpp/cpp   ← การเคลื่อนที่ (forward, turn, stop)
│   ├── sensor.h/cpp       ← เซนเซอร์ (ultrasonic, battery)
│   └── rtc.hpp            ← (ยังไม่ได้ใช้)
│
├── behavior/
│   ├── types.h            ← นิยาม SensorType, ActionType, Rule struct
│   ├── rules.h            ← ⭐ แก้ไขตรงนี้เพื่อเปลี่ยนพฤติกรรม!
│   ├── pattern.h          ← Pattern สำเร็จรูป (5 แบบ)
│   ├── reflex.h/cpp       ← Reflex engine (อ่าน + execute rules)
│
├── net/
│   ├── client.h           ← (อนาคต) WiFi client
│   └── worldlog.h         ← (อนาคต) MDS World sync
│
├── main.ino               ← โปรแกรมหลัก
└── README.md              ← ไฟล์นี้
```

---

## 🔧 Hardware Setup

### อุปกรณ์ที่ต้องใช้:
- ESP32 DevKit v1
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

แก้ไขได้ที่: [core/board.hpp](core/board.hpp)

---

## 🎨 วิธีเพิ่ม Sensor ใหม่

1. เพิ่ม enum ใน [behavior/types.h](behavior/types.h):
```cpp
enum SensorType {
  DISTANCE,
  BATTERY,
  MY_NEW_SENSOR, // ← เพิ่มตรงนี้
};
```

2. เขียน class ใน [core/sensor.h](core/sensor.h):
```cpp
class MyNewSensor {
public:
  MyNewSensor();
  int readValue();
};
```

3. เพิ่ม case ใน [behavior/reflex.cpp](behavior/reflex.cpp):
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
{"my-rule", MY_NEW_SENSOR, GREATER, 50, FORWARD, 100, 100}
```

---

## 🎯 วิธีเพิ่ม Action ใหม่

1. เพิ่ม enum ใน [behavior/types.h](behavior/types.h):
```cpp
enum ActionType {
  FORWARD,
  TURN_LEFT,
  MY_NEW_ACTION, // ← เพิ่มตรงนี้
};
```

2. เพิ่ม case ใน [behavior/reflex.cpp](behavior/reflex.cpp):
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
{"test", DISTANCE, LESS_THAN, 30, MY_NEW_ACTION, 0, 100}
```

---

## 🧪 ตัวอย่างการใช้งาน

### ตัวอย่าง 1: หุ่นหลบกำแพง
```cpp
Rule myRules[] = {
  {"emergency-stop", DISTANCE, LESS_THAN, 10, STOP,       0,   100},
  {"avoid-wall",     DISTANCE, LESS_THAN, 25, TURN_RIGHT, 120, 100},
  {"explore",        DISTANCE, GREATER,   40, FORWARD,    100, 100},
};
```

### ตัวอย่าง 2: สุ่มเดิน (Random Walk)
```cpp
Rule myRules[] = {
  {"avoid-wall",   DISTANCE, LESS_THAN, 20, TURN_RIGHT, 120, 100},
  {"go-forward",   DISTANCE, GREATER,   50, FORWARD,    100, 100},
  {"random-left",  NONE,     ALWAYS,    0,  TURN_LEFT,  90,  20}, // 20%
  {"random-right", NONE,     ALWAYS,    0,  TURN_RIGHT, 90,  20}, // 20%
};
```

### ตัวอย่าง 3: ประหยัดแบต
```cpp
Rule myRules[] = {
  {"critical",     BATTERY,  LESS_THAN, 10, STOP,    0,  100},
  {"low-power",    BATTERY,  LESS_THAN, 30, FORWARD, 50, 100}, // ช้าๆ
  {"normal",       BATTERY,  GREATER,   50, FORWARD, 120, 100},
  {"avoid-wall",   DISTANCE, LESS_THAN, 20, TURN_RIGHT, 100, 100},
};
```

---

## 🐛 Debug Tips

### ดูค่า Sensor แบบ real-time:
เปิด Serial Monitor (115200 baud) จะเห็น:
```
[SENSORS] Distance: 35cm | Battery: 78%
[REFLEX] avoid-wall triggered → action: TURN_RIGHT
[SENSORS] Distance: 12cm | Battery: 78%
[REFLEX] emergency-stop triggered → action: STOP
```

### แก้ไข debug interval:
ในไฟล์ [main.ino](main.ino):
```cpp
if (millis() - lastDebug > 1000) { // ← แก้เป็น 500 = เร็วขึ้น
```

### ปิด debug:
```cpp
// if (millis() - lastDebug > 1000) { ... } // ← comment ทั้งหมด
```

---

## 🌐 อนาคต (Roadmap)

- [ ] WiFi sync กับ MDS World
- [ ] เพิ่ม sensor: gyro, compass, GPS
- [ ] State machine layer (นอกเหนือจาก reflex)
- [ ] Rule editor บน web UI
- [ ] Learning layer (Q-learning, simple RL)
- [ ] Multi-probe coordination (swarm behavior)

---

## 🧩 ปรัชญา (Philosophy)

Dreamflow-Lite ไม่ใช่ AI
มันเป็น **symbolic behavior system** ที่:
- ใกล้เคียงภาษาธรรมชาติ
- แสดงความตั้งใจ (intent) แบบชัดเจน
- เด็กก็แก้ไขได้
- ทำงานได้แม้ไม่มี internet
- เก็บ log ได้ดี (สำหรับ learning ภายหลัง)

**"มันไม่เดา, มันไม่เชื่อ, มันแค่เข้าใจสิ่งที่มีอยู่จริง"**

---

## 📝 License

MIT License - ใช้อะไรก็ได้ แต่อย่าลืมเครดิต 😊

---

## 🙏 Credits

- Inspired by **Dreamflow** (JS version): https://github.com/v1b3x0r/dreamflow
- Part of **MDS Ecosystem** (Meaning-Driven Systems)
- Built with ❤️ for playful, embodied AI research

---

**Happy hacking! 🚀**
