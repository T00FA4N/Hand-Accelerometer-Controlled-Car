#include "I2Cdev.h"
#include "MPU6050.h"
#include <RH_ASK.h>
#include <SPI.h>

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

RH_ASK d;
char *msg = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  mpu.initialize();
  
  if (!d.init()) {
    Serial.println("init failed");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

//  Serial.print("x: "); Serial.println(ax);
//  Serial.print("y: "); Serial.println(ay);
//  Serial.print("z: "); Serial.println(az);
  

//S = stop, L = Left, R = Right
//F = Forward, B = Back, C = Continue
  if (az > 14000) {
    msg = "Stop\0";
    d.send((uint8_t *)msg, strlen(msg));
    d.waitPacketSent(); 
  }
  else if (ax >= 6000) {
    msg = "Left\0";
    d.send((uint8_t *)msg, strlen(msg));
    d.waitPacketSent(); 
  }
  else if (ax < -5000) {
    msg = "Rght\0";
    d.send((uint8_t *)msg, strlen(msg));
    d.waitPacketSent();  
  }
  else if (ay < -5000) {
    msg = "Forw\0";
    d.send((uint8_t *)msg, strlen(msg));
    d.waitPacketSent(); 
  }
  else if (ay > 6400 || az > 13000) {
    msg = "Back\0";
    d.send((uint8_t *)msg, strlen(msg));
    d.waitPacketSent(); 
  }
//  else {
//    Serial.write("Cont\0");
////    Serial.print("x: "); Serial.println(ax);
////    Serial.print("y: "); Serial.println(ay);
////    Serial.print("z: "); Serial.println(az);
//  }

  
  delay(1000);
}
