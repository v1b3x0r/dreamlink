#ifndef PATTERN_H
#define PATTERN_H

#include "types.h"

// ========================================
// PRE-MADE BEHAVIOR PATTERNS
// These are ready-to-use rule sets that
// you can copy into your main rules array
// ========================================

// Pattern 1: Obstacle Avoidance
// Robot stops and turns when hitting wall
namespace ObstacleAvoidance {
  Rule rules[] = {
    {"avoid-close-wall", DISTANCE, LESS_THAN, 15, STOP,       0,   100},
    {"turn-away",        DISTANCE, LESS_THAN, 15, TURN_RIGHT, 150, 100},
    {"keep-moving",      DISTANCE, GREATER,   30, FORWARD,    120, 100},
  };
  const int count = 3;
}

// Pattern 2: Explorer (random walk)
// Wanders around with occasional random turns
namespace Explorer {
  Rule rules[] = {
    {"avoid-wall",      DISTANCE, LESS_THAN, 20, TURN_RIGHT, 120, 100},
    {"explore-forward", DISTANCE, GREATER,   50, FORWARD,    100, 100},
    {"random-left",     NONE,     ALWAYS,    0,  TURN_LEFT,  80,  5},  // 5% chance
    {"random-right",    NONE,     ALWAYS,    0,  TURN_RIGHT, 80,  5},  // 5% chance
  };
  const int count = 4;
}

// Pattern 3: Energy Saver
// Slows down when battery is low
namespace EnergySaver {
  Rule rules[] = {
    {"critical-battery", BATTERY, LESS_THAN, 10, STOP,       0,   100},
    {"low-battery",      BATTERY, LESS_THAN, 30, FORWARD,    60,  100}, // slow speed
    {"normal-speed",     BATTERY, GREATER,   50, FORWARD,    120, 100},
    {"avoid-wall",       DISTANCE, LESS_THAN, 20, TURN_RIGHT, 100, 100},
  };
  const int count = 4;
}

// Pattern 4: Wall Follower
// Tries to keep a wall on the right side
namespace WallFollower {
  Rule rules[] = {
    {"too-close",   DISTANCE, LESS_THAN, 15, TURN_LEFT,  100, 100},
    {"too-far",     DISTANCE, GREATER,   35, TURN_RIGHT, 80,  100},
    {"sweet-spot",  DISTANCE, GREATER,   15, FORWARD,    100, 100},
  };
  const int count = 3;
}

// Pattern 5: Cautious (very defensive)
// Stops frequently, slow movement
namespace Cautious {
  Rule rules[] = {
    {"far-wall",     DISTANCE, LESS_THAN, 40, STOP,       0,   100},
    {"think",        NONE,     ALWAYS,    0,  WAIT,       500, 100}, // wait 500ms
    {"careful-turn", DISTANCE, LESS_THAN, 40, TURN_RIGHT, 80,  100},
    {"slow-crawl",   DISTANCE, GREATER,   50, FORWARD,    50,  100}, // very slow
  };
  const int count = 4;
}

#endif
