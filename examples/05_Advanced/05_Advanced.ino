// ========================================
// DreamLink Example 05: Advanced Usage
// ใช้ฟีเจอร์ขั้นสูง + custom rules
// ========================================

#include <DreamLink.h>

DreamLink probe;

// Custom rules (แบบ low-level)
Rule customRules[] = {
  // name              sensor    op          threshold  action       param  prob
  {"emergency-stop",   DISTANCE, LESS_THAN,  10,        STOP,        0,     100},
  {"avoid-wall",       DISTANCE, LESS_THAN,  25,        TURN_RIGHT,  120,   100},
  {"explore",          DISTANCE, GREATER,    50,        FORWARD,     100,   100},
  {"low-battery",      BATTERY,  LESS_THAN,  15,        STOP,        0,     100},
  {"random-spin",      NONE,     ALWAYS,     0,         TURN_LEFT,   150,   10},
};
const int customRulesCount = sizeof(customRules) / sizeof(Rule);

void setup() {
  probe.begin();

  // ตั้งชื่อ probe (สำหรับ MDS ในอนาคต)
  probe.identify("probe-001");

  // วิธีที่ 1: ใช้ custom rules (low-level)
  probe.loadRules(customRules, customRulesCount);

  // วิธีที่ 2: ใช้ API แบบ readable (comment ออกถ้าใช้วิธีที่ 1)
  // probe.when(DISTANCE < 10).then(STOP, 0);
  // probe.when(DISTANCE < 25).then(TURN_RIGHT, 120);
  // probe.when(DISTANCE > 50).then(FORWARD, 100);
  // probe.when(BATTERY < 15).then(STOP, 0);
  // probe.when(ALWAYS).then(TURN_LEFT, 150).sometimes(10);

  probe.enableDebug(true);
  probe.printRules();
  probe.wakeup();

  Serial.println("Advanced mode enabled");
  Serial.println("Monitoring sensors...\n");
}

void loop() {
  probe.live();

  // ตัวอย่างการควบคุมแบบ manual (นอกเหนือจาก reflex)
  static unsigned long lastManualControl = 0;

  if (millis() - lastManualControl > 10000) { // ทุก 10 วินาที
    lastManualControl = millis();

    // ตรวจสอบเงื่อนไขพิเศษ
    int battery = probe.readBattery();
    int distance = probe.readDistance();

    if (battery < 20) {
      Serial.println("[MANUAL] Battery critical! Forcing stop.");
      probe.sleep(); // หยุด reflex engine
      probe.stop();  // หยุดมอเตอร์
      delay(5000);   // รอ 5 วินาที
      // probe.wakeup(); // เริ่มต้นใหม่ (ถ้าต้องการ)
    }

    if (distance > 100) {
      Serial.println("[MANUAL] Clear path detected! Speed boost!");
      probe.forward(200); // เร่งความเร็ว
      delay(1000);
    }
  }
}

/*
 * ========================================
 * ADVANCED FEATURES:
 * ========================================
 *
 * 1. Custom Rules (struct array)
 *    - ควบคุมแบบละเอียด
 *    - เหมาะกับ advanced users
 *
 * 2. Manual Control
 *    - probe.sleep() / probe.wakeup()
 *    - probe.forward() / probe.stop()
 *    - ควบคุมนอกเหนือจาก reflex
 *
 * 3. Sensor Access
 *    - probe.readDistance()
 *    - probe.readBattery()
 *    - ใช้ใน custom logic
 *
 * 4. Debug Tools
 *    - probe.printRules()
 *    - probe.enableDebug(true)
 *    - probe.identify("name")
 *
 * ========================================
 * USE CASES:
 * ========================================
 * - State machine hybrid (reflex + manual)
 * - Emergency override logic
 * - Performance monitoring
 * - MDS integration (future)
 */
