#ifndef GLOBALS_H
#define GLOBALS_H

#include "core/motor.hpp"
#include "core/movement.hpp"
#include "core/sensor.h"

// ========================================
// GLOBAL INSTANCES (declarations)
// ========================================

extern Motor motorLeft;
extern Motor motorRight;
extern Movement movement;
extern DistanceSensor distanceSensor;
extern BatterySensor batterySensor;

#endif
