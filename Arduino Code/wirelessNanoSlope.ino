#include <SparkFun_TB6612.h>
#include <RH_ASK.h>
#include <SPI.h>

/*
 * Using Arduino Nano and TB6612FNG Motor Driver
 * 
 * Nano --> Motor Driver
 * 3.3V --> Vcc
 * D9 --> STBY
 * D8/7 --> AIN1/2
 * D6/5 --> PWMA/B
 * D4/3 --> BIN1/2
 * Gnd --> Gnd
 * 
 * Nano --> Receiver
 * 5V --> 1
 * D11 --> 3
 * Gnd --> 4
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
char spdArr[4];

void setup() {
  Serial.begin(38400);
  if (!receiver.init()){
    Serial.println("init failed");
  }
}

void loop() {
  uint8_t message[8];
  uint8_t len = sizeof(message);
  
  //if message from uno is correct length
  if (receiver.recv(message, &len)){
    int i, j, k, spd;
    //copy direction to corresponding array
    for (i = 0; i < 4; i++){
      direct[i] = message[i];
    }
    direct[4] = '\0';

    //get speed values
    for (j = 0; j < 3; j++){
      spdArr[j] = message[4 + j];
    }
    spdArr[3] = '\0';]

    //convert speed to integer
    spd = ((int)spdArr[0] - 48)*100 + ((int)spdArr[1] - 48)*10 + ((int)spdArr[2] - 48);

    //determine direction to go at speed defined
    if (strcmp(direct, "Stop") == 0) {
       brake(m1, m2);
    }
    else if (strcmp(direct, "Left") == 0) {
        m1.drive(spd);
        m2.drive(-1*spd);
    }
    else if (strcmp(direct, "Rght") == 0) {
        m1.drive(-1*spd);
        m2.drive(spd);
    }
    else if (strcmp(direct, "Forw") == 0) {
        back(m1, m2, -1*spd);
    }
    else if (strcmp(direct, "Back") == 0) {
        forward(m1, m2, spd);
    }
  }
  delay(1000);
}
