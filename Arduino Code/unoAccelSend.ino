#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  mpu.initialize();
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
    Serial.write("Stop\0");  
  }
  else if (ax >= 6000) {
    Serial.write("Left\0");
  }
  else if (ax < -5000) {
    Serial.write("Rght\0");  
  }
  else if (ay < -5000) {
    Serial.write("Forw\0");  
  }
  else if (ay > 6400 || az > 13000) {
    Serial.write("Back\0");  
  }
//  else {
//    Serial.write("Cont\0");
////    Serial.print("x: "); Serial.println(ax);
////    Serial.print("y: "); Serial.println(ay);
////    Serial.print("z: "); Serial.println(az);
//  }

  
  delay(1000);
}
