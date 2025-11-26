#ifndef MOTOR_HPP
#define MOTOR_HPP

class Motor {
private:
#ifndef MOTOR_HPP
#define MOTOR_HPP

class Motor {
private:
  int pwmPin;
  int in1Pin;
  int in2Pin;
  int pwmChannel;

public:
  Motor(int pwm, int in1, int in2, int channel);
  void begin();              // Initialize hardware (pinMode, ledc)
  void forward(int speed);   // speed: 0-255
  void backward(int speed);  // speed: 0-255
  void stop();
};

#endif