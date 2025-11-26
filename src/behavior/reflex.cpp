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

Reflex::Reflex(Rule* ruleArray, int count, AudioFeedback* audioInstance, SensorCallback reader)
  : rules(ruleArray), ruleCount(count), audio(audioInstance), sensorReader(reader) {}

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

// We need access to DreamLink instance to use readSensor()
// But Reflex is a member of DreamLink.
// For now, we'll keep using the global instances for internal sensors,
// BUT we need a way to access the drivers.
//
// BETTER APPROACH: Pass the sensor reading function or interface to Reflex.
// OR: Make DreamLink singleton (easy but dirty).
// OR: Pass DreamLink* to Reflex.

// Let's modify Reflex to take a callback or interface.
// Actually, since we are in the same codebase, let's just use the drivers directly if we can access them.
// But drivers are private in DreamLink.

// Quick fix: Make Reflex call a static method or global wrapper? No.
// Correct fix: Pass a "SensorReader" interface to Reflex.

// For this iteration, let's update Reflex::readSensor to use the global DreamLink instance if available?
// Wait, DreamLink is usually instantiated as `DreamLink probe;` in user sketch.
// We don't have a global pointer to it here.

// REFACTOR: Reflex should ask DreamLink for sensor data.
// We will change Reflex to accept a "SensorProvider" function.

// ... actually, let's look at how Reflex is constructed.
// It's created inside DreamLink.
// We can pass `this` to Reflex.

int Reflex::readSensor(SensorType type) {
  if (sensorReader) {
    return sensorReader(type);
  }
  return 0;
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
      if (audio) audio->beep(r.param);
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
