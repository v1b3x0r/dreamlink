#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

class Movement {
public:
  Movement();
  void forward(int speed);    // speed: 0-255
  void backward(int speed);   // speed: 0-255
  void turnLeft(int speed);   // speed: 0-255 (pivot turn)
  void turnRight(int speed);  // speed: 0-255 (pivot turn)
  void stop();
};

#endif