#ifndef DREAMLINK_H
#define DREAMLINK_H

#include "behavior/types.h"
  // ========================================
  void loadRules(Rule* customRules, int count);
  void clearRules();
  int getRuleCount() const { return ruleCount; }

  // ========================================
  // SENSOR ACCESS
  // ========================================
  int readSensor(SensorType type); // Unified read
  int readDistance();              // อ่านระยะ (cm)
  int readBattery();               // อ่านแบต (%)

  // ========================================
  // MANUAL CONTROL
  // ========================================
  void forward(int speed);
  void backward(int speed);
  void turnLeft(int speed);
  void turnRight(int speed);
  void stop();

  // ========================================
  // DEBUG & UTILITIES
  // ========================================
  void enableDebug(bool enable = true);
  void printRules();
  void identify(const char* id);   // ตั้งชื่อ probe (สำหรับ MDS)

  // ========================================
  // FUTURE: MDS INTEGRATION
  // ========================================
  // void connect(const char* host, int port);
  // void broadcastContext();
  // void subscribe(const char* event, void (*callback)(float));
};

#endif
