#include <MsTimer2.h>

int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;

int nSwitch = 0;
boolean bReverse = false;

int nSpeed = 150;
String sMeg = "Switch : ";

void runMotor(int nSpeed);
void setMotor(int nSpeed, boolean bReverse);

void setup()
{
  Serial.begin(9600);
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}
 
void loop()
{
  
  runMotor(nSpeed);
}
void runMotor(int nSpeed){
    if(Serial.available())
  {
    nSwitch = Serial.read();
  }
  
  if( nSwitch == '1')bReverse = true;
  else bReverse = false;
 
  setMotor(nSpeed, bReverse);
  Serial.println(sMeg + int(nSwitch) + ", Speed : " + int(nSpeed));
  delay(1000);
}
void setMotor(int nSpeed, boolean bReverse)
{
  analogWrite(enablePin, nSpeed);
  digitalWrite(in1Pin, ! bReverse);
  digitalWrite(in2Pin, bReverse);
}
