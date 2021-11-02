#include <Servo.h>

const int n = 4;
int pots[] = {A0, A1, A2, A3};
int pwms[] = {3, 5, 6, 9};
Servo outputs[n];

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(pots[i], INPUT);
    outputs[i].attach(pwms[i]);
  }
}

void loop() {
  for (int i = 0; i < n; i++) {
    outputs[i].writeMicroseconds(1500 + analogRead(pots[i]) / 2);
  }
}
