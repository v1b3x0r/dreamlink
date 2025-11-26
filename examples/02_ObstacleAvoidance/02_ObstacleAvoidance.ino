// ========================================
// DreamLink Example 02: Obstacle Avoidance
// หลบกำแพงอัตโนมัติ
// ========================================

#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();

  // Rule 1: ถ้าเจอกำแพงใกล้มาก (<10cm) → หยุดฉุกเฉิน
  probe.when(DISTANCE < 10).then(STOP, 0);

  // Rule 2: ถ้าเจอกำแพงใกล้ (<25cm) → เลี้ยวขวา
  probe.when(DISTANCE < 25).then(TURN_RIGHT, 120);

  // Rule 3: ถ้าทางว่าง (>40cm) → เดินหน้า
  probe.when(DISTANCE > 40).then(FORWARD, 100);

  probe.enableDebug(true);
  probe.wakeup();

  Serial.println("Robot จะหลบกำแพงอัตโนมัติ");
  Serial.println("ลองเอามือปิดหน้า ultrasonic sensor ดู!\n");
}

void loop() {
  probe.live();
}

/*
 * ========================================
 * WHAT TO EXPECT:
 * ========================================
 * - Robot เดินหน้าตราบที่ทางว่าง
 * - พอใกล้กำแพง (25cm) → เลี้ยวขวา
 * - ถ้าใกล้มากๆ (10cm) → หยุดก่อน
 * - Serial Monitor จะแสดง distance + battery
 *
 * ========================================
 * EXPERIMENT:
 * ========================================
 * ลองเปลี่ยน threshold:
 * - 25 → 30 (หลบไวขึ้น)
 * - 25 → 15 (หลบช้าลง, อันตราย!)
 *
 * ลองเปลี่ยน action:
 * - TURN_RIGHT → TURN_LEFT
 * - TURN_RIGHT → BACKWARD
 */
