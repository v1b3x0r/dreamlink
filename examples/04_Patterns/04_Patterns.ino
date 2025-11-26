// ========================================
// DreamLink Example 04: Using Patterns
// ใช้ behavior pattern สำเร็จรูป
// ========================================

#include <DreamLink.h>

DreamLink probe;

void setup() {
  probe.begin();

  // ใช้ pattern สำเร็จรูป (แทนการเขียน rule เอง)
  // ลองเปลี่ยนระหว่างเหล่านี้:

  probe.behave("explorer");           // สำรวจแบบสุ่ม
  // probe.behave("obstacle-avoidance"); // หลบกำแพงธรรมดา
  // probe.behave("cautious");           // เดินระวังๆ ช้าๆ
  // probe.behave("wall-follower");      // เดินตามกำแพง
  // probe.behave("energy-saver");       // ประหยัดแบต

  probe.enableDebug(true);
  probe.wakeup();

  Serial.println("Robot กำลังใช้ pattern: Explorer");
  Serial.println("ลอง uncomment pattern อื่นๆ แล้ว upload ใหม่!\n");
}

void loop() {
  probe.live();
}

/*
 * ========================================
 * AVAILABLE PATTERNS:
 * ========================================
 *
 * 1. "explorer"
 *    - เดินสำรวจแบบสุ่ม
 *    - เลี้ยวซ้าย/ขวาบางครั้ง (5%)
 *
 * 2. "obstacle-avoidance"
 *    - หลบกำแพงธรรมดา
 *    - เลี้ยวขวาเมื่อเจอสิ่งกีดขวาง
 *
 * 3. "cautious"
 *    - เดินช้าๆ ระวังๆ
 *    - หยุดบ่อย (500ms)
 *    - หลบกำแพงไวกว่าปกติ
 *
 * 4. "wall-follower"
 *    - พยายามเดินตามกำแพงด้านขวา
 *    - เลี้ยวซ้ายถ้าใกล้เกินไป
 *    - เลี้ยวขวาถ้าไกลเกินไป
 *
 * 5. "energy-saver"
 *    - ตรวจสอบแบตเตอรี่
 *    - หยุดถ้าแบตเหลือน้อยกว่า 10%
 *    - เดินช้าถ้าแบตเหลือน้อยกว่า 30%
 *
 * ========================================
 * NEXT STEPS:
 * ========================================
 * ลอง pattern แต่ละตัว แล้วสังเกตพฤติกรรม!
 * ตัวไหนเหมาะกับ use case ของคุณ?
 */
