char message[4] = "Left";

void setup() {a
  Serial.begin(9600);
}

void loop() {
  //Serial.write(message, 5);
  Serial.write(message, 4);
  delay(1000);
}
