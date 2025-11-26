#ifndef RULES_H
#define RULES_H

#include "types.h"

// ========================================
// YOUR CUSTOM RULES
// Edit this file to change robot behavior!
// ========================================

// Uncomment one of these to use a pre-made pattern:
// #include "pattern.h"
// Rule myRules[] = ObstacleAvoidance::rules;
// const int myRulesCount = ObstacleAvoidance::count;

// OR write your own custom rules below:

Rule myRules[] = {
  // name             sensor    op          threshold  action       param  probability
  // ================================================================================

  // Safety: stop if wall is VERY close
  {"emergency-stop",  DISTANCE, LESS_THAN,  10,        STOP,        0,     100},

  // Avoidance: turn right if wall detected
  {"avoid-wall",      DISTANCE, LESS_THAN,  25,        TURN_RIGHT,  120,   100},

  // Exploration: move forward when clear
  {"explore",         DISTANCE, GREATER,    40,        FORWARD,     100,   100},

  // Energy: stop if battery is critical
  {"low-battery",     BATTERY,  LESS_THAN,  15,        STOP,        0,     100},

  // Playful: random turn sometimes (10% chance)
  {"random-spin",     NONE,     ALWAYS,     0,         TURN_LEFT,   150,   10},

  // Add your own rules here!
  // {"my-rule",       DISTANCE, GREATER,    50,        FORWARD,     80,    100},
};

const int myRulesCount = sizeof(myRules) / sizeof(Rule);

#endif
