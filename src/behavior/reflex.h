#ifndef REFLEX_H
#define REFLEX_H

#include "types.h"

class Reflex {
private:
  Rule* rules;
  int ruleCount;

  bool checkCondition(Rule& r);
  int readSensor(SensorType type);
  void executeAction(Rule& r);

public:
  Reflex(Rule* ruleArray, int count);
  void tick(); // execute all rules once per loop
};

#endif