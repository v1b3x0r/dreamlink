#include "movement.hpp"
#include "motor.hpp"
#include "board.hpp"
#include <Arduino.h>

Movement::Movement() : motorLeft(nullptr), motorRight(nullptr), standbyPin(-1) {
}

Movement::~Movement() {
  if (motorLeft) delete motorLeft;
  if (motorRight) delete motorRight;
}

void Movement::begin(const BoardConfig& config) {
  standbyPin = config.motorStandby;
  
  if (standbyPin != -1) {
    pinMode(standbyPin, OUTPUT);
    digitalWrite(standbyPin, HIGH); // Enable motor driver
  }

  // Initialize motors with config
  motorLeft = new Motor(config.motorA_PWM, config.motorA_IN1, config.motorA_IN2, PWM_CHANNEL_A);
  motorRight = new Motor(config.motorB_PWM, config.motorB_IN1, config.motorB_IN2, PWM_CHANNEL_B);

  motorLeft->begin();
  motorRight->begin();
}

void Movement::forward(int speed) {
  if (!motorLeft || !motorRight) return;
  speed = constrain(speed, 0, 255);
  motorLeft->forward(speed);
  motorRight->forward(speed);
}

void Movement::backward(int speed) {
  if (!motorLeft || !motorRight) return;
  speed = constrain(speed, 0, 255);
  motorLeft->backward(speed);
  motorRight->backward(speed);
}

void Movement::turnLeft(int speed) {
  if (!motorLeft || !motorRight) return;
  speed = constrain(speed, 0, 255);
  motorLeft->backward(speed);
  motorRight->forward(speed);
}

void Movement::turnRight(int speed) {
  if (!motorLeft || !motorRight) return;
  speed = constrain(speed, 0, 255);
  motorLeft->forward(speed);
  motorRight->backward(speed);
}

void Movement::stop() {
  if (motorLeft) motorLeft->stop();
  if (motorRight) motorRight->stop();
}
