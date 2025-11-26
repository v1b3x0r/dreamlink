// ========================================
// DreamLink Example 03: Explorer
// สำรวจแบบสุ่มเดิน (Random Walk)
// ========================================

#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();

  // Rule 1: หลบกำแพง
  probe.when(DISTANCE < 20).then(TURN_RIGHT, 120);

  // Rule 2: เดินหน้าเมื่อทางว่าง
  probe.when(DISTANCE > 50).then(FORWARD, 100);

  // Rule 3: เลี้ยวซ้ายแบบสุ่ม (5% chance)
  probe.when(ALWAYS).then(TURN_LEFT, 80).sometimes(5);

  // Rule 4: เลี้ยวขวาแบบสุ่ม (5% chance)
  probe.when(ALWAYS).then(TURN_RIGHT, 80).sometimes(5);

  probe.enableDebug(true);
  probe.wakeup();

  Serial.println("Robot จะเดินสำรวจแบบสุ่ม");
  Serial.println("บางครั้งจะเลี้ยวเองโดยไม่มีเหตุผล!\n");
}

void loop() {
  probe.live();
}

/*
 * ========================================
 * WHAT TO EXPECT:
 * ========================================
 * - Robot เดินหน้าเหมือน example 02
 * - แต่บางครั้งจะเลี้ยวซ้าย/ขวาเอง (random!)
 * - ทำให้ดูเหมือน "อยากรู้อยากเห็น"
 *
 * ========================================
 * EXPERIMENT:
 * ========================================
 * ลองเปลี่ยน probability:
 * - sometimes(5) → sometimes(20)  // เลี้ยวบ่อยขึ้น
 * - sometimes(5) → sometimes(1)   // เลี้ยวน้อยลง
 *
 * ลองเพิ่ม rule ใหม่:
 * - probe.when(ALWAYS).then(STOP, 0).sometimes(3); // หยุดคิดบ้าง
 * - probe.when(ALWAYS).then(BACKWARD, 100).sometimes(2); // ถอยหลังบ้าง
 */
