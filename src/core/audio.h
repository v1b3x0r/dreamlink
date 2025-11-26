#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>

class AudioFeedback {
private:
  int pin;
  int pwmChannel;

public:
  AudioFeedback();
  void begin(int buzzerPin, int channel = 2); // Channel 0,1 used by motors
  void beep(int durationMs, int freq = 1000);
  void mute();
};

#endif
