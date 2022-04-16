#include <SoftwareSerial.h>

#define TX 3
#define RX 4

SoftwareSerial soft_Serial(RX,TX);

void setup() {
  // put your setup code here, to run once:
  soft_Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  soft_Serial.print(1);
  digitalWrite(13,HIGH);
  delay(1000);
  soft_Serial.print(2);
  digitalWrite(13,LOW);
  delay(1000);
  soft_Serial.print(3);
  delay(1000);
}
