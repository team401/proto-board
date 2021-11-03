#include <Servo.h>

const int n = 4;
const int minVal = 1500;
const int maxVal = 2000;
const int midVal = minVal + (maxVal - minVal) / 2;
const int width = 25;

int pots[] = {A0, A1, A2, A3};
int pwms[] = {3, 5, 6, 9};
Servo outputs[n];

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(pots[i], INPUT);
    outputs[i].attach(pwms[i]);
  }
}

int deadband(int raw) {
  if (abs(raw - midVal) < width) {
    return 0;
  } else {
    if (raw < midVal) {
      return (midVal / (midVal - width)) * raw;
    } else {
      return (midVal / (midVal + width)) * raw;
    }
  }
}

void loop() {
  for (int i = 0; i < n; i++) {
    outputs[i].writeMicroseconds(deadband(minVal + analogRead(pots[i]) / 2));
  }
}
