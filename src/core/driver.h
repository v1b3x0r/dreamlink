#ifndef DRIVER_H
#define DRIVER_H

#include <Arduino.h>
#include <functional>

// ========================================
// SENSOR DRIVER INTERFACE
// ========================================
class ISensorDriver {
public:
  virtual int read() = 0;
  virtual ~ISensorDriver() {}
};

// ========================================
// LAMBDA DRIVER - The Magic Wrapper
// ========================================
class LambdaDriver : public ISensorDriver {
private:
  std::function<int()> reader;

public:
  LambdaDriver(std::function<int()> func) : reader(func) {}
  
  int read() override {
    if (reader) {
      return reader();
    }
    return 0;
  }
};

// ========================================
// MAGIC MACRO
// ========================================
// Usage: INSTALL_SENSOR_DRIVER(probe, DISTANCE, mySensor.read());
#define INSTALL_SENSOR_DRIVER(dreamlinkObj, sensorType, expression) \
  dreamlinkObj.useDriver(sensorType, new LambdaDriver([&]() -> int { return (expression); }))

#endif
