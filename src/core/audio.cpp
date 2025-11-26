#include "audio.h"

AudioFeedback::AudioFeedback() : pin(-1), pwmChannel(-1) {
}

void AudioFeedback::begin(int buzzerPin, int channel) {
  pin = buzzerPin;
  pwmChannel = channel;

  if (pin != -1) {
    pinMode(pin, OUTPUT);
    ledcSetup(pwmChannel, 2000, 8); // 2kHz, 8-bit
    ledcAttachPin(pin, pwmChannel);
  }
}

void AudioFeedback::beep(int durationMs, int freq) {
  if (pin == -1) return;

  ledcWriteTone(pwmChannel, freq);
  delay(durationMs);
  ledcWriteTone(pwmChannel, 0); // Stop tone
}

void AudioFeedback::mute() {
  if (pin == -1) return;
  ledcWriteTone(pwmChannel, 0);
}
