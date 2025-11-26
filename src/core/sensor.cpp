#include "sensor.h"
#include "board.hpp"
#include <Arduino.h>

// ========================================
// DISTANCE SENSOR (HC-SR04 Ultrasonic)
// ========================================

// ========================================
// DISTANCE SENSOR (HC-SR04 Ultrasonic)
// ========================================

DistanceSensor::DistanceSensor() : trigPin(-1), echoPin(-1) {
}

void DistanceSensor::begin(int trig, int echo) {
  trigPin = trig;
  echoPin = echo;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int DistanceSensor::readCM() {
  if (trigPin == -1 || echoPin == -1) return 0;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  if (duration == 0) return 999; // out of range

  int distance = duration * 0.034 / 2; // speed of sound: 340 m/s
  return constrain(distance, 0, 400);
}

// ========================================
// BATTERY SENSOR (Voltage Divider)
// ========================================

BatterySensor::BatterySensor() : pin(-1) {
}

void BatterySensor::begin(int p) {
  pin = p;
  pinMode(pin, INPUT);
}

int BatterySensor::readPercent() {
  if (pin == -1) return 0;
  
  int raw = analogRead(pin);
  // ADC: 0-4095 (12-bit on ESP32)
  // Voltage divider: R1=10kΩ, R2=10kΩ (assuming 1:1 ratio)
  // Battery: 3.0V (empty) to 4.2V (full) for LiPo

  float voltage = (raw / 4095.0) * 3.3 * 2.0; // *2 for voltage divider

  // Map 3.0V-4.2V to 0-100%
  int percent = ((voltage - 3.0) / 1.2) * 100;
  return constrain(percent, 0, 100);
}
