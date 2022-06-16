#include "I2Cdev.h"
#include "MPU6050.h"
#include <RH_ASK.h>
#include <SPI.h>

/*
 * Using Arduino Uno and 433MHz Transmitter
 * 
 * Uno --> Transmitter
 * 12 --> 1
 * 5V --> 2
 * Gnd --> 3
 * 
*/

#define button 13

#define fBound -16000
#define sBound 1
#define bBound 16000
#define lBound 16000
#define rBound -15800

#define minimum 100
#define maximum 255

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

RH_ASK trans;
char vals[3];
char *s;
char message[9];


int servo = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  pinMode(button, INPUT);

  mpu.initialize();
  if (!trans.init()) {
    Serial.println("init failed");
  }
}

//takes in read val and boundary to find speed
void calcSpeed(int r, int b){
  int spd = (255.0*r/b);
  Serial.print(spd);Serial.print(",");

  //set speed to min/max value if too small/large
  if (spd < minimum){
    spd = minimum;
  }
  else if (spd > maximum){
    spd = maximum;
  }

  //checks for spd <10 (doesn't happen as of right now - need higher voltage)
  // 10<= spd <100 (also doesn't happen yet)
  //spd > 100
  if (spd/10 == 0){
      //#, dest, base
      itoa(0, message+4, 10);
      itoa(0, message+5, 10);
      itoa(spd, message+6, 10);
  }
  else if (spd/100 == 0){
      itoa(0, message+4, 10);
      itoa((spd/10), message+5, 10);
      itoa((spd%10), message+6, 10);
  }
  else {
      itoa((spd/100), message+4, 10);
      itoa((spd/10)%10, message+5, 10);
      itoa((spd%10), message+6, 10);
  }
  itoa(servo, message+7, 10);
  message[8] = '\0';
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if (digitalRead(button) == HIGH){
    servo = 1-servo;
  }
  
//  Serial.write(millis() + '\n');
  Serial.println(millis()/1000);
//S = stop, L = Left, R = Right
//F = Forward, B = Back, C = Continue
  if (az > 14000) {
    Serial.write("Stop,");
    Serial.write("0,");
    if (servo){
      strcpy(message, "Stop0001\0");
    }
    else {
      strcpy(message, "Stop0000\0");
    }
  }
  else if (ax >= 6000) {
    Serial.write("Left,");
    strcpy(message, "Left");
    calcSpeed(ax, lBound);
  }
  else if (ax < -5000) {
    Serial.write("Right,");
    strcpy(message, "Rght");
    calcSpeed(ax, rBound);
  }
  else if (ay < -5000) {
    Serial.write("Forward,");
    strcpy(message, "Forw");
    calcSpeed(ay, fBound);
  }
  else if (ay > 6400 || az > 13000) {
    Serial.write("Back,");
    strcpy(message, "Back");
    if (ay > 6400) {
      calcSpeed(ay, bBound);
    }
    else {
      calcSpeed(az, bBound);
    }
  }

  Serial.print(ax);Serial.print(",");
  Serial.print(ay);Serial.print(",");
  Serial.print(az);Serial.print(",");
  Serial.print(gx);Serial.print(",");
  Serial.print(gy);Serial.print(",");
  Serial.print(gz);Serial.print("\0");
  trans.send((uint8_t *)message, strlen(message));
  trans.waitPacketSent(); 
  delay(250);
}
