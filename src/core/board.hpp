#ifndef BOARD_HPP
#define BOARD_HPP

// ========================================
// FESE PROBE - BOARD CONFIGURATION
// ESP32 DevKit v1 + TB6612FNG Motor Driver
// ========================================

// Motor Driver (TB6612FNG) Pins
#define MOTOR_A_PWM   25  // Left motor speed (PWM)
#define MOTOR_A_IN1   26  // Left motor direction 1
#define MOTOR_A_IN2   27  // Left motor direction 2

#define MOTOR_B_PWM   32  // Right motor speed (PWM)
#define MOTOR_B_IN1   33  // Right motor direction 1
#define MOTOR_B_IN2   14  // Right motor direction 2

#define MOTOR_STBY    12  // Standby pin (HIGH = enabled)

// Ultrasonic Sensor (HC-SR04)
#define ULTRASONIC_TRIG  18
#define ULTRASONIC_ECHO  19

// Battery Monitoring
#define BATTERY_PIN   34  // ADC pin (voltage divider)

// PWM Configuration
#define PWM_FREQ      1000  // 1kHz
#define PWM_RESOLUTION 8    // 8-bit (0-255)

// Motor PWM Channels (ESP32 has 16 PWM channels)
#define PWM_CHANNEL_A  0
#define PWM_CHANNEL_B  1

// ========================================
// BOARD CONFIGURATION STRUCT
// ========================================
struct BoardConfig {
  int motorA_PWM;
  int motorA_IN1;
  int motorA_IN2;
  int motorB_PWM;
  int motorB_IN1;
  int motorB_IN2;
  int motorStandby;
  int ultrasonicTrig;
  int ultrasonicEcho;
  int batteryPin;
  int buzzerPin;
};

// ========================================
// PRESETS
// ========================================
namespace Boards {
  // Default ESP32 DevKit V1
  const BoardConfig ESP32_DEVKIT_V1 = {
    MOTOR_A_PWM, MOTOR_A_IN1, MOTOR_A_IN2,
    MOTOR_B_PWM, MOTOR_B_IN1, MOTOR_B_IN2,
    MOTOR_STBY,
    ULTRASONIC_TRIG, ULTRASONIC_ECHO,
    BATTERY_PIN,
    -1 // No buzzer by default
  };

  // ESP32-S3 DevKit (Example mapping, adjustable)
  const BoardConfig ESP32_S3_DEVKIT = {
    1, 2, 42,   // Motor A
    41, 40, 39, // Motor B
    38,         // Standby
    5, 6,       // Ultrasonic
    7,          // Battery
    -1          // Buzzer
  };

  // M5Stack Core2 (Internal motor driver if available, or external via Grove)
  // Note: This is a placeholder for external driver connected to Port A/B/C
  const BoardConfig M5STACK_CORE2 = {
    19, 33, 32, // Motor A (Port A)
    27, 26, 25, // Motor B (Port B)
    -1,         // Standby (Not used)
    13, 14,     // Ultrasonic (Port C)
    34,         // Battery (Internal)
    -1          // Buzzer (Core2 has speaker on I2S, simple buzzer not mapped)
  };
  
  // M5StickC Plus
  const BoardConfig M5STICK_C_PLUS = {
    26, 0, 36,  // Motor A
    32, 33, 25, // Motor B
    -1,         // Standby
    13, 14,     // Ultrasonic
    34,         // Battery
    2           // Buzzer (Internal Piezo)
  };
  
  // Atom Echo (Speaker on G27)
  const BoardConfig ATOM_ECHO = {
    -1, -1, -1, // No motors by default
    -1, -1, -1,
    -1,
    -1, -1,
    -1,
    27          // Speaker Pin
  };
}

#endif
