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
  

  if (az > 14000) {
    Serial.println("Direction: Flat");
    Serial.write("Flat", 5);
  }
  else if (ax >= 6000) {
    Serial.println("Direction: Left");
    Serial.write("Left", 5);
  }
  else if (ax < -5000) {
    Serial.println("Direction: Right");
    Serial.write("Rght", 5);
  }
  else if (ay < -5000) {
    Serial.println("Direction: Forward");  
    Serial.write("Forw", 5);
  }
  else if (ay > 6400 || az > 13000) {
    Serial.println("Direction: Backward");  
    Serial.write("Back", 5);
  }
  else {
    Serial.println("Direction: Unable to Detect");
    Serial.write("Cont", 5);
    Serial.print("x: "); Serial.println(ax);
    Serial.print("y: "); Serial.println(ay);
    Serial.print("z: "); Serial.println(az);
  }

  delay(5000);
}
