#include <Servo.h>

const int n = 4;

const int minVal = 1000;
const int midVal = 1500;
const int maxVal = 2000;
const int width = 25;

int pots[] = {A0, A1, A2, A3};  // A0 A1
int pwms[] = {3, 9, 5, 6};      // 3 5
int mids[] = {512, 512, 512, 512};
bool hasStarted[] = {false, false, false, false};
Servo outputs[n];

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(pots[i], INPUT);
    outputs[i].attach(pwms[i]);
  }
}

int deadband(int potVal, int potID) {
  int inputMid = mids[potID];  // mid point for the specified potentiometer
  int slope =
      (midVal - minVal) /
      (inputMid -
       width);  // calculate the slope (change in output / change in input)

  // Check if we have reached deadband yet
  if (!hasStarted[potID]) {
    // if we're in the dead band then save that we've reached the deadband!
    if (abs(potVal - inputMid) < width) {
      hasStarted[potID] = true;
    }

    // return mid val (0% power) until we have reached the deadband at some
    // point
    return midVal;
  } else {
    // We HAVE reached the deadband at some point, use normal re-linearization
    // logic

    // check if currently in deadband
    if (abs(potVal - inputMid) < width) {
      return midVal;  // return 0% power if in deadband

    } else if (potVal < inputMid) {
      // check if we're to the left of the deadband
      return minVal +
             slope * potVal;  // return the relinearized ouput (y = b + mx)

    } else {
      // if we're not in the deadband or to the left of the deadband then we are
      // to the right of it
      return minVal +
             slope * (potVal - (width * 2));  // output relinearization but
                                              // account for 2x deadband width
    }
  }
}

void loop() {
  for (int i = 0; i < n; i++) {
    outputs[i].writeMicroseconds(deadband(analogRead(pots[i]), i));
  }
}
