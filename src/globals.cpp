#include "globals.h"
#include "core/board.hpp"

// ========================================
// GLOBAL INSTANCES (definitions)
// ========================================

Motor motorLeft(MOTOR_A_PWM, MOTOR_A_IN1, MOTOR_A_IN2, PWM_CHANNEL_A);
Motor motorRight(MOTOR_B_PWM, MOTOR_B_IN1, MOTOR_B_IN2, PWM_CHANNEL_B);
Movement movement;
DistanceSensor distanceSensor;
BatterySensor batterySensor;
