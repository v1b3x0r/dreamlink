#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// ========================================
// SENSOR TYPES
// ========================================
enum SensorType {
  DISTANCE = 0,   // ultrasonic (cm)
  BATTERY,        // voltage (0-100%)
  LIGHT,          // LDR (0-1023)
  HUMIDITY,       // DHT22 (0-100%)
  TEMPERATURE,    // DHT22 (celsius)
  COLOR,          // TCS34725 (RGB)
  NONE            // no sensor (always-on rules)
};

// ========================================
// COMPARISON OPERATORS
// ========================================
enum CompareOp {
  LESS_THAN = 0,  // <
  GREATER,        // >
  EQUAL,          // ==
  NOT_EQUAL,      // !=
  ALWAYS          // ignore condition, always execute
};

// ========================================
// ACTION TYPES
// ========================================
enum ActionType {
  TURN_RIGHT = 0,
  TURN_LEFT,
  FORWARD,
  BACKWARD,
  STOP,
  GO_HOME,        // navigate to start position
  BLINK_LED,
  BEEP,
  LOG_EVENT,      // write to serial/world log
  WAIT,           // pause for N milliseconds
  NO_ACTION       // skip (for testing)
};

// ========================================
// RULE STRUCTURE
// ========================================
struct Rule {
  const char* name;        // human-readable label (e.g., "avoid-wall")
  SensorType sensor;       // which sensor to check
  CompareOp op;            // comparison operator
  int threshold;           // value to compare against
  ActionType action;       // what to do when condition is true
  int param;               // action parameter (speed, duration, angle, etc.)
  uint8_t probability;     // 0-100: chance of executing (100 = always)
};

#endif
