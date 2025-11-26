#ifndef CONFIG_BUILDER_H
#define CONFIG_BUILDER_H

#include "board.hpp"

// Forward declaration
class DreamLink;

class ConfigBuilder {
private:
  BoardConfig config;
  DreamLink* probe;

public:
  ConfigBuilder(DreamLink* p) : probe(p) {
    // Initialize with safe defaults (all -1 or standard)
    // We start with standard DevKit to be safe, but user can override
    config = Boards::ESP32_DEVKIT_V1;
  }

  ConfigBuilder& setMotorA(int pwm, int in1, int in2) {
    config.motorA_PWM = pwm;
    config.motorA_IN1 = in1;
    config.motorA_IN2 = in2;
    return *this;
  }

  ConfigBuilder& setMotorB(int pwm, int in1, int in2) {
    config.motorB_PWM = pwm;
    config.motorB_IN1 = in1;
    config.motorB_IN2 = in2;
    return *this;
  }

  ConfigBuilder& setStandbyPin(int pin) {
    config.motorStandby = pin;
    return *this;
  }

  ConfigBuilder& setUltrasonic(int trig, int echo) {
    config.ultrasonicTrig = trig;
    config.ultrasonicEcho = echo;
    return *this;
  }

  ConfigBuilder& setBattery(int pin) {
    config.batteryPin = pin;
    return *this;
  }

  ConfigBuilder& setBuzzer(int pin) {
    config.buzzerPin = pin;
    return *this;
  }

  ConfigBuilder& noBattery() {
    config.batteryPin = -1;
    return *this;
  }

  // Terminal operation: Apply config and start DreamLink
  void begin(); 
};

#endif
