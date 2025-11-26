#ifndef REFLEX_H
#define REFLEX_H

#include "types.h"
#include "../core/audio.h"
#include <functional>

using SensorCallback = std::function<int(SensorType)>;

class Reflex {
private:
  Rule* rules;
  int ruleCount;
  AudioFeedback* audio;
  SensorCallback sensorReader;

  bool checkCondition(Rule& r);
  int readSensor(SensorType type);
  void executeAction(Rule& r);

public:
  Reflex(Rule* ruleArray, int count, AudioFeedback* audioInstance, SensorCallback reader);
  void tick(); // execute all rules once per loop
};

#endif