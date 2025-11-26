#include "sensor.h"
#include "board.hpp"
#include <Arduino.h>

// ========================================
// DISTANCE SENSOR (HC-SR04 Ultrasonic)
// ========================================

DistanceSensor::DistanceSensor() {
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
}

int DistanceSensor::readCM() {
  digitalWrite(ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);

  long duration = pulseIn(ULTRASONIC_ECHO, HIGH, 30000); // timeout 30ms
  if (duration == 0) return 999; // out of range

  int distance = duration * 0.034 / 2; // speed of sound: 340 m/s
  return constrain(distance, 0, 400);
}

// ========================================
// BATTERY SENSOR (Voltage Divider)
// ========================================

BatterySensor::BatterySensor() {
  pinMode(BATTERY_PIN, INPUT);
}

int BatterySensor::readPercent() {
  int raw = analogRead(BATTERY_PIN);
  // ADC: 0-4095 (12-bit on ESP32)
  // Voltage divider: R1=10kΩ, R2=10kΩ (assuming 1:1 ratio)
  // Battery: 3.0V (empty) to 4.2V (full) for LiPo

  float voltage = (raw / 4095.0) * 3.3 * 2.0; // *2 for voltage divider

  // Map 3.0V-4.2V to 0-100%
  int percent = ((voltage - 3.0) / 1.2) * 100;
  return constrain(percent, 0, 100);
}
