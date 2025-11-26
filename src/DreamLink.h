#ifndef DREAMLINK_H
#define DREAMLINK_H

#include "behavior/types.h"
#include "behavior/reflex.h"
#include "behavior/pattern.h"
#include "core/sensor.h"
#include "core/movement.hpp"
#include <Arduino.h>

// ========================================
// DREAMLINK - Where Physical Meets Meaning
// Embodied cognition library for ESP32 probes
// Part of MDS (Meaning-Driven Systems) ecosystem
// ========================================

// Forward declarations
class Condition;
class RuleBuilder;

// ========================================
// CONDITION - สำหรับ when() API
// ========================================
class Condition {
public:
  SensorType sensor;
  CompareOp op;
  int threshold;

  Condition(SensorType s, CompareOp o, int t)
    : sensor(s), op(o), threshold(t) {}
};

// Helper functions for readable conditions
inline Condition operator<(SensorType s, int threshold) {
  return Condition(s, LESS_THAN, threshold);
}

inline Condition operator>(SensorType s, int threshold) {
  return Condition(s, GREATER, threshold);
}

inline Condition operator==(SensorType s, int threshold) {
  return Condition(s, EQUAL, threshold);
}

inline Condition operator!=(SensorType s, int threshold) {
  return Condition(s, NOT_EQUAL, threshold);
}

// Special constant for ALWAYS condition
extern const Condition ALWAYS_CONDITION;
#define ALWAYS ALWAYS_CONDITION

// ========================================
// RULE BUILDER - สำหรับ method chaining
// ========================================
class RuleBuilder {
private:
  const char* name;
  Condition condition;
  ActionType action;
  int param;
  uint8_t probability;
  Rule* targetRule;

public:
  RuleBuilder(const char* n, Condition c)
    : name(n), condition(c), action(NO_ACTION), param(0), probability(100), targetRule(nullptr) {}

  RuleBuilder& then(ActionType act, int p = 0);
  RuleBuilder& sometimes(uint8_t prob);
  Rule build();
};

// ========================================
// DREAMLINK - Main API Class
// ========================================
class DreamLink {
private:
  static const int MAX_RULES = 32;
  Rule rules[MAX_RULES];
  int ruleCount;

  Reflex* reflexEngine;
  Movement* movement;
  DistanceSensor* distanceSensor;
  BatterySensor* batterySensor;

  bool isAwake;
  bool debugEnabled;
  unsigned long lastDebugTime;

  RuleBuilder* pendingBuilder;

public:
  DreamLink();
  ~DreamLink();

  // ========================================
  // CORE LIFECYCLE
  // ========================================
  void begin();                    // เริ่มต้นระบบ (sensors, motors)
  void wakeup();                   // เริ่มทำงาน (start reflex engine)
  void sleep();                    // หยุดชั่วคราว
  void live();                     // main loop (call ใน loop())

  // ========================================
  // SIMPLE API - เพิ่ม rule แบบง่าย
  // ========================================
  RuleBuilder& when(Condition cond);
  void addRule(const char* name, Condition cond, ActionType action, int param, uint8_t prob = 100);

  // ========================================
  // PATTERN API - ใช้ pattern สำเร็จรูป
  // ========================================
  void behave(const char* patternName);
  void loadPattern(Rule* pattern, int count);

  // ========================================
  // ADVANCED API - ควบคุมแบบละเอียด
  // ========================================
  void loadRules(Rule* customRules, int count);
  void clearRules();
  int getRuleCount() const { return ruleCount; }

  // ========================================
  // SENSOR ACCESS
  // ========================================
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
