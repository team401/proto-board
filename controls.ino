#include <Servo.h>

const int n = 4;
const int minVal = 1000;
const int maxVal = 2000;
const int midVal = (maxVal + minVal) / 2;

const int inputMid = 512;
const int width = 25;

const int slope = (midVal - minVal) / (inputMid - width);

int pots[] = {A0, A1, A2, A3};
int pwms[] = {3, 5, 6, 9};
Servo outputs[n];

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(pots[i], INPUT);
    outputs[i].attach(pwms[i]);
  }
}

int deadband(int rawVal) {
  if (abs(rawVal - inputMid) < width) {
    return midVal;
  } else if (rawVal < inputMid) {
    return minVal + slope * rawVal;
  } else {
    return minVal + slope * (rawVal - (width * 2));
  }
}

void loop() {
  for (int i = 0; i < n; i++) {
    outputs[i].writeMicroseconds(deadband(analogRead(pots[i])));
  }
}
