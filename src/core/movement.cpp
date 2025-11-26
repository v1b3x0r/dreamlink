#include "movement.hpp"
#include "motor.hpp"
#include "board.hpp"
#include <Arduino.h>

// Global motor instances
Motor motorLeft(MOTOR_A_PWM, MOTOR_A_IN1, MOTOR_A_IN2, PWM_CHANNEL_A);
Motor motorRight(MOTOR_B_PWM, MOTOR_B_IN1, MOTOR_B_IN2, PWM_CHANNEL_B);

Movement::Movement() {
  pinMode(MOTOR_STBY, OUTPUT);
  digitalWrite(MOTOR_STBY, HIGH); // Enable motor driver
}

void Movement::forward(int speed) {
  speed = constrain(speed, 0, 255);
  motorLeft.forward(speed);
  motorRight.forward(speed);
}

void Movement::backward(int speed) {
  speed = constrain(speed, 0, 255);
  motorLeft.backward(speed);
  motorRight.backward(speed);
}

void Movement::turnLeft(int speed) {
  speed = constrain(speed, 0, 255);
  motorLeft.backward(speed);
  motorRight.forward(speed);
}

void Movement::turnRight(int speed) {
  speed = constrain(speed, 0, 255);
  motorLeft.forward(speed);
  motorRight.backward(speed);
}

void Movement::stop() {
  motorLeft.stop();
  motorRight.stop();
}
