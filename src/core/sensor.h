#ifndef SENSOR_H
#define SENSOR_H

class DistanceSensor {
public:
  DistanceSensor();
  int readCM(); // returns distance in centimeters (0-400cm)
};

class BatterySensor {
public:
  BatterySensor();
  int readPercent(); // returns battery level (0-100%)
};

// Future sensors can be added here:
// class LightSensor { ... };
// class HumiditySensor { ... };

#endif