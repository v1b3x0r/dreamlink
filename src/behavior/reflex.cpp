#include "reflex.h"
#include "types.h"
#include "../core/sensor.h"
#include "../core/movement.hpp"
#include <Arduino.h>

// Global sensor instances
extern DistanceSensor distanceSensor;
extern BatterySensor batterySensor;

// Global movement instance
extern Movement movement;

Reflex::Reflex(Rule* ruleArray, int count)
  : rules(ruleArray), ruleCount(count) {}

void Reflex::tick() {
  for (int i = 0; i < ruleCount; i++) {
    Rule& r = rules[i];

    // Check if rule should execute (probability check)
    if (r.probability < 100) {
      int roll = random(0, 100);
      if (roll >= r.probability) {
        continue; // skip this rule
      }
    }

    // Evaluate condition
    if (checkCondition(r)) {
      executeAction(r);

      // Debug log
      Serial.print("[REFLEX] ");
      Serial.print(r.name);
      Serial.print(" triggered → action: ");
      Serial.println(r.action);
    }
  }
}

bool Reflex::checkCondition(Rule& r) {
  int sensorValue = readSensor(r.sensor);

  switch (r.op) {
    case LESS_THAN:
      return sensorValue < r.threshold;
    case GREATER:
      return sensorValue > r.threshold;
    case EQUAL:
      return sensorValue == r.threshold;
    case NOT_EQUAL:
      return sensorValue != r.threshold;
    case ALWAYS:
      return true;
    default:
      return false;
  }
}

int Reflex::readSensor(SensorType type) {
  switch (type) {
    case DISTANCE:
      return distanceSensor.readCM();
    case BATTERY:
      return batterySensor.readPercent();
    case NONE:
      return 0;
    default:
      return 0; // unsupported sensor
  }
}

void Reflex::executeAction(Rule& r) {
  switch (r.action) {
    case TURN_RIGHT:
      movement.turnRight(r.param);
      break;
    case TURN_LEFT:
      movement.turnLeft(r.param);
      break;
    case FORWARD:
      movement.forward(r.param);
      break;
    case BACKWARD:
      movement.backward(r.param);
      break;
    case STOP:
      movement.stop();
      break;
    case WAIT:
      delay(r.param);
      break;
    case LOG_EVENT:
      Serial.print("[EVENT] ");
      Serial.println(r.name);
      break;
    case BEEP:
      // TODO: implement buzzer
      Serial.println("[BEEP]");
      break;
    case NO_ACTION:
      // do nothing (for testing)
      break;
    default:
      Serial.print("[ERROR] Unknown action: ");
      Serial.println(r.action);
  }
}
