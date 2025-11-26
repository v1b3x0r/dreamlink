// ========================================
// FESE PROBE - Main Program
// Dreamflow-Lite Behavior Engine
// ========================================

#include "core/board.hpp"
#include "core/motor.hpp"
#include "core/movement.hpp"
#include "core/sensor.h"
#include "behavior/types.h"
#include "behavior/reflex.h"
#include "behavior/rules.h"

// Global instances (sensors, movement, reflex)
DistanceSensor distanceSensor;
BatterySensor batterySensor;
Movement movement;
Reflex reflex(myRules, myRulesCount);

// ========================================
// SETUP (runs once on boot)
// ========================================
void setup() {
  Serial.begin(115200);
  delay(1000); // wait for serial monitor

  Serial.println("========================================");
  Serial.println("   FESE PROBE - Dreamflow-Lite v1.0    ");
  Serial.println("========================================");
  Serial.println();

  // Print loaded rules
  Serial.print("Loaded ");
  Serial.print(myRulesCount);
  Serial.println(" behavior rules:");
  Serial.println();

  for (int i = 0; i < myRulesCount; i++) {
    Serial.print("  [");
    Serial.print(i + 1);
    Serial.print("] ");
    Serial.print(myRules[i].name);
    Serial.print(" (prob: ");
    Serial.print(myRules[i].probability);
    Serial.println("%)");
  }

  Serial.println();
  Serial.println("System ready. Starting main loop...");
  Serial.println("========================================");
  Serial.println();

  randomSeed(analogRead(0)); // seed random number generator
}

// ========================================
// LOOP (runs continuously)
// ========================================
void loop() {
  // Execute all rules
  reflex.tick();

  // Optional: print sensor values for debugging
  static unsigned long lastDebug = 0;
  if (millis() - lastDebug > 1000) { // every 1 second
    lastDebug = millis();

    Serial.print("[SENSORS] Distance: ");
    Serial.print(distanceSensor.readCM());
    Serial.print("cm | Battery: ");
    Serial.print(batterySensor.readPercent());
    Serial.println("%");
  }

  delay(50); // 20Hz loop rate (adjust as needed)
}
