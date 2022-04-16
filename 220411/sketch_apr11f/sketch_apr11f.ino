#include <SoftwareSerial.h>

#define TX 2
#define RX 3

SoftwareSerial soft_Serial (TX,RX);

void setup() {
  // put your setup code here, to run once:
  soft_Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  soft_Serial.write("123");
  delay(1000);
  soft_Serial.write("12890");
  delay(1000);
}
