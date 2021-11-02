#include <Servo.h>

int n = 4;
int pots[n] = {A0, A1, A2, A3};
int pwms[n] = {3, 5, 6, 9};
Servo outputs[n];

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(pots[i], INPUT);
    outputs[i].attach(pwms[i]);
  }
}

void loop() {
  for (int i = 0; i < n; i++) {
    controllers[i].writeMicroseconds(1500 + analogRead(pots[i]) / 2);
  }
}
