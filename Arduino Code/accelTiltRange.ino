#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  Serial.println("Initializing I2C devices...");
  mpu.initialize();

  Serial.println("Testing device connections...");
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

//  Serial.print("x: "); Serial.println(ax);
//  Serial.print("y: "); Serial.println(ay);
//  Serial.print("z: "); Serial.println(az);
  

  if (az > 14000) {
    Serial.println("Direction: Flat");  
  }
  else if (ax >= 6000) {
    Serial.println("Direction: Left");
  }
  else if (ax < -5000) {
    Serial.println("Direction: Right");  
  }
  else if (ay < -5000) {
    Serial.println("Direction: Forward");  
  }
  else if (ay > 6400 || az > 13000) {
    Serial.println("Direction: Backward");  
  }
  else {
    Serial.println("Direction: Unable to Detect");
    Serial.print("x: "); Serial.println(ax);
    Serial.print("y: "); Serial.println(ay);
    Serial.print("z: "); Serial.println(az);
  }

  delay(5000);
}
