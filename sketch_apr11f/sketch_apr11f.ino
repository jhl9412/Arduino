#include <SoftwareSerial.h>

#define TX 6
#define RX 7

SoftwareSerial soft_Serial (TX,RX);

void setup() {
  // put your setup code here, to run once:
  sort_Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(sovt_Serial.available()>0)
  int data = soft_Serial();
}
