
#include <SparkFun_TB6612.h>
#include <RH_ASK.h>
#include <SPI.h>

/*
 * Using Arduino Nano and TB6612FNG Motor Driver
 * 
 * Nano --> Motor Driver
 * 5V --> Vcc
 * D9 --> STBY
 * D8/7 --> AIN1/2
 * D6/5 --> PWMA/B
 * D4/3 --> BIN1/2
 * Gnd --> Gnd
 * 
 * Battery +/- --> VM/Gnd
 * Motor 1 +/- --> A01/2
 * Motor 2 +/- --> B01/2
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

void setup() {
  Serial.begin(38400);
  if (!receiver.init()){
    Serial.println("init failed");
  }
}

void loop() {
  uint8_t message[5];
  uint8_t len = sizeof(message);
  //if message from uno is correct length
  if (receiver.recv(message, &len)){
    int i;

    //copy direction to corresponding array
    for (i = 0; i < 4; i++){
      direct[i] = message[i];
    }
    direct[4] = '\0';

    if (strcmp(direct, "Stop") == 0) {
        brake(m1, m2);
    }
    else if (strcmp(direct, "Left") == 0) {
        m1.drive(255);
        m2.drive(-255);
    }
    else if (strcmp(direct, "Rght") == 0) {
        m1.drive(-255);
        m2.drive(255);
    }
    else if (strcmp(direct, "Forw") == 0) {
        back(m1, m2, -255);
    }
    else if (strcmp(direct, "Back") == 0) {
        forward(m1, m2, 255);
    }
  }
  delay(1000);
}
