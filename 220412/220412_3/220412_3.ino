#include <Servo.h>

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(11);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(A1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //int val = map(analogWrite(), 0, 255, 0, 180);
  //myServo.write(0);
  //for(int i = 0; i <180; i++)
  //{
  //  myServo.write(i);
  //  delay(100);
  //}
  int analog_IN = analogRead(A0); 
  Serial.println(analog_IN);
  int analog_OUT = map(analog_IN, 0, 1023, 0, 180);
  int analog_OUT2 = map(analog_IN, 0, 1023, 0, 255);
  Serial.println(analog_OUT);
  myServo.write(analog_OUT);
  analogWrite(A1,analog_OUT2);
  delay(10);
}
