#include "I2Cdev.h"
#include "MPU6050.h"
#include <RH_ASK.h>
#include <SPI.h>

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

RH_ASK trans;
char *msg = "";

void setup() {
  Serial.begin(38400);
  mpu.initialize();
  
  if (!trans.init()) {
    Serial.println("init failed");
  }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

//S = stop, L = Left, R = Right
//F = Forward, B = Back, C = Continue
  if (az > 14000) {
    msg = "Stop\0";
    trans.send((uint8_t *)msg, strlen(msg));
    trans.waitPacketSent(); 
  }
  else if (ax >= 6000) {
    msg = "Left\0";
    trans.send((uint8_t *)msg, strlen(msg));
    trans.waitPacketSent(); 
  }
  else if (ax < -5000) {
    msg = "Rght\0";
    trans.send((uint8_t *)msg, strlen(msg));
    trans.waitPacketSent();  
  }
  else if (ay < -5000) {
    msg = "Forw\0";
    trans.send((uint8_t *)msg, strlen(msg));
    trans.waitPacketSent(); 
  }
  else if (ay > 6400 || az > 13000) {
    msg = "Back\0";
    trans.send((uint8_t *)msg, strlen(msg));
    trans.waitPacketSent(); 
  }

  delay(1000);
}
