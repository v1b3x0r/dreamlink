#include "motor.hpp"
#include "board.hpp"
#include <Arduino.h>

Motor::Motor(int pwm, int in1, int in2, int channel)
  : pwmPin(pwm), in1Pin(in1), in2Pin(in2), pwmChannel(channel) {

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  // Setup PWM channel (ESP32 style)
  ledcSetup(pwmChannel, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(pwmPin, pwmChannel);

  stop();
}

void Motor::forward(int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  ledcWrite(pwmChannel, speed);
}

void Motor::backward(int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  ledcWrite(pwmChannel, speed);
}

void Motor::stop() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  ledcWrite(pwmChannel, 0);
}
