#define led 13

char message[10];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.readBytes(message, 4);
  if (strcmp(message, "Left") == 0) {
      Serial.println(message);
      digitalWrite(led, HIGH);
      delay(1000);
  }
  delay(1000);
}
