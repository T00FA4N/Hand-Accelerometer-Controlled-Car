
#include <SparkFun_TB6612.h>
#include <RH_ASK.h>
#include <SPI.h>

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

RH_ASK receiver;

char direct[5];
char message[5];
int len = sizeof(message);

void setup() {
  Serial.begin(38400);
  if (!receiver.init()){
    Serial.println("init failed");
  }
}

void loop() {
  //if message from uno is correct length
  if (receiver.recv(message, &len)){

    //copy direction to corresponding array
    for (i = 0; i < 4; i++){
      direct[i] = message[i];
    }
    direct[4] = '\0';

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
  }
  delay(1000);
}
