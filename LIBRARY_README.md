# DreamLink 🌙

> **Where Physical Meets Meaning**

DreamLink เป็น library สำหรับสร้างหุ่นยนต์ที่ "รู้สึก" และ "เข้าใจ" โลก ผ่านการเชื่อมโยงระหว่างการรับรู้ทางกายภาพ (sensors) กับความหมาย (meaning-driven behavior)

Part of [MDS (Meaning-Driven Systems)](https://github.com/v1b3x0r/mds) ecosystem

---

## ✨ Features

- 🎯 **Declarative Rules** - เขียน behavior แบบ readable เหมือน JS
- 🧠 **Embodied Cognition** - ออกแบบจาก physical sensing ตั้งแต่ต้น
- 🎨 **Ready-to-Use Patterns** - 5 behavior patterns สำเร็จรูป
- 🔧 **Extensible** - เพิ่ม sensor/action ใหม่ได้ง่าย
- 📡 **MDS-Ready** - เตรียมพร้อมเชื่อม semantic bus (soon)
- ⚡ **Embedded-Friendly** - ไม่มี malloc, RAM น้อย, รวดเร็ว

---

## 🚀 Quick Start

### Installation

**ดูคู่มือติดตั้งแบบละเอียดที่:** [INSTALL.md](INSTALL.md)

**TL;DR:**
```bash
cp -r fese-probe-261125 ~/Documents/Arduino/libraries/DreamLink
```
เปิด Arduino IDE ใหม่ → File → Examples → DreamLink

### Hello World

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
// Load custom rules
Rule myRules[] = { ... };
probe.loadRules(myRules, count);

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

## 🎨 Available Patterns

| Pattern | Description |
|---------|-------------|
| `"explorer"` | เดินสำรวจแบบสุ่ม (random walk) |
| `"obstacle-avoidance"` | หลบกำแพงธรรมดา |
| `"cautious"` | เดินระวังๆ ช้าๆ หยุดบ่อย |
| `"wall-follower"` | เดินตามกำแพงด้านขวา |
| `"energy-saver"` | ประหยัดแบต เดินช้าเมื่อแบตต่ำ |

### ตัวอย่าง:
```cpp
probe.behave("explorer");  // ใช้ pattern สำเร็จรูป
```

---

## 🔧 Supported Hardware

### Tested On:
- ESP32 DevKit v1
- ESP32-S3
- TB6612FNG Motor Driver
- HC-SR04 Ultrasonic Sensor
- 18650 LiPo Battery

### Pin Configuration:
ดูที่ [core/board.hpp](core/board.hpp)

---

## 📚 Examples

| Example | Description |
|---------|-------------|
| [01_BasicMovement](examples/01_BasicMovement) | ทดสอบมอเตอร์เบื้องต้น |
| [02_ObstacleAvoidance](examples/02_ObstacleAvoidance) | หลบกำแพงอัตโนมัติ |
| [03_Explorer](examples/03_Explorer) | Random walk behavior |
| [04_Patterns](examples/04_Patterns) | ใช้ pattern สำเร็จรูป |
| [05_Advanced](examples/05_Advanced) | Custom rules + manual control |

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

## 🌟 Philosophy

DreamLink ไม่ใช่แค่ library สำหรับควบคุมหุ่นยนต์

มันเป็น **embodied cognition framework** ที่:
- ความหมายเกิดจาก interaction กับโลกจริง
- Behavior ไม่ใช่ hard-coded แต่เป็น **declarative interpretation**
- Physical body = interface กับโลกความหมาย (MDS World)

> **"มันไม่เดา, มันไม่เชื่อ, มันแค่เข้าใจสิ่งที่มีอยู่จริง"**

---

## 🔮 Roadmap

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

## 🤝 Contributing

ยินดีรับ PR! กรุณา:
1. Fork repo
2. สร้าง branch ใหม่
3. Commit changes
4. Push + create PR

---

## 📜 License

MIT License - ใช้อะไรก็ได้ แต่อย่าลืมเครดิต 😊

---

## 💬 Support

- GitHub Issues: [v1b3x0r/mds](https://github.com/v1b3x0r/mds/issues)
- MDS Ecosystem: [https://github.com/v1b3x0r/mds](https://github.com/v1b3x0r/mds)

---

## 🙏 Credits

- Inspired by [Dreamflow](https://github.com/v1b3x0r/dreamflow)
- Part of MDS (Meaning-Driven Systems) ecosystem
- Built with ❤️ for embodied AI research

---

**Happy hacking! 🌙✨**
