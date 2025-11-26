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

// Optional Sensors (comment out if not used)
// #define LIGHT_SENSOR_PIN    35  // LDR analog input
// #define DHT22_PIN           4   // Temperature/Humidity sensor
// #define LED_PIN             2   // Built-in LED (ESP32)

// PWM Configuration
#define PWM_FREQ      1000  // 1kHz
#define PWM_RESOLUTION 8    // 8-bit (0-255)

// Motor PWM Channels (ESP32 has 16 PWM channels)
#define PWM_CHANNEL_A  0
#define PWM_CHANNEL_B  1

#endif
