
#include <SparkFun_TB6612.h>

/*
 * Using Arduino Nano and TB6612FNG Motor Driver
 * 9 --> STBY
 * 8/7, 4/5 --> A/BIN1/2
 * 6/5 --> PWMA/B
 * 3v3 --> Vcc
 * Gnd --> Gnd
 * 
 * Nano --> Uno
 * RX(0) --> TX(1)
 * TX(1) --> RX(0)
 * Gnd --> Gnd
 * 5V --> Vin
*/

#define AIN1 8
#define BIN1 4
#define AIN2 7
#define BIN2 3
#define PWMA 6
#define PWMB 5
#define STBY 9

const int offsetA = 1;
const int offsetB = 1;

Motor m1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor m2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

char direct[5];
char pastDirect[5] = "Stop";

void setup() {
  Serial.begin(38400);
}

void loop() {
  //Read input from accelerometer
  Serial.readBytes(direct, 4);

  //Continue
//  if (strcmp(direct, "Cont") == 0) {
//      direct[0] = pastDirect[0];
//  }

  //S = stop, L = Left, R = Right
  //F = Forward, B = Back
  if (strcmp(direct, "Stop") == 0) {
      brake(m1, m2);
  }
  else if (strcmp(direct, "Left") == 0) {
      //left(m1, m2, 100);
      m1.drive(255);
      m2.drive(-127);
  }
  else if (strcmp(direct, "Rght") == 0) {
      //right(m1, m2, 100);
      m1.drive(-127);
      m2.drive(255);
  }
  else if (strcmp(direct, "Forw") == 0) {
      forward(m1, m2, 150);
  }
  else if (strcmp(direct, "Back") == 0) {
      back(m1, m2, -150);
  }

  //record current direction
//  for (int i = 0; i< 5; i++){
//    pastDirect[i] = direct[i];
//  }
  delay(1000);
}
