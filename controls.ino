int pots[4] = [ A0, A1, A2, A3 ];
int pwms[4] = [ 3, 5, 6, 9 ];

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(pots[i], INPUT);
    pinMode(pwms[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    analogWrite(pwms[i], analogRead(pots[i]) / 4);
  }
}