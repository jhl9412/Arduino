// 서보
#include <Servo.h>
Servo myServo;
int servoPin =9;

//// 변수 선언
int mode = 3; // manual = 1, auto =2;
//모터 변수
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;

int nSwitch = 0;
boolean bReverse = false;

int nSpeed = 0;
String sMeg = "Switch : ";

// --------------------------------------
#include <LiquidCrystal_I2C.h>


#define interruptPin 2
LiquidCrystal_I2C lcd(0x27, 16, 2);

//타이머
unsigned long currentTime = 0;
unsigned long prev_Time = 0;
int second, minute, hour;
int timeLimit=15;
boolean state=false;
#include <IRremote.h>
int interruptCount =1;

//-------------------------------------------------
 //리모컨 함수

void modeFunction(); // Manual 기능

// 모터 함수
void runMotor(int nSpeed);
void setMotor(int nSpeed, boolean bReverse);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //모터 setup
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  //LCD출력
  lcd.init();
  lcd.backlight();
  lcd.scrollDisplayRight();
  lcd.setCursor(0,0);
  lcd.print("TimeCountDown");
  
  //인터럽트 발생
  attachInterrupt(digitalPinToInterrupt(interruptPin), switchFn, RISING);

  // 서보
  myServo.attach(servoPin);
}

void loop() {
  modeFunction();
 
}
/*
mode 1 : manual
mode 2 : home
mode 3 : auto
mode 4 : manual power 1
mode 5 : manual power 2
mode 6 : manual stop
mode 7 : manual turn
mode 8 : manual timer

*/
void modeFunction(){
  switch(mode){
    case 1:break;
    case 2:break;
    case 3:break;
    case 4:nSpeed=150;runMotor(nSpeed);break;
    case 5:nSpeed=255;runMotor(nSpeed);break;
    case 6:nSpeed=0;runMotor(nSpeed);break;
    case 7:break;
    case 8:timerFn();runMotor(nSpeed);break;
    default:break;
  }
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
void switchFn(){
 
    state=!state;
    prev_Time=millis();
    timeLimit = 15; 
    mode =8;
 

}
//타이머
void timerFn() {

  if(state==true)
  {
  currentTime = (millis()-prev_Time)/1000;//인터럽트 발생시 시간과 비교해 시간을 카운트.

  second = (timeLimit-currentTime)%60; //초
  if((timeLimit-currentTime)/60 < 0) minute = 0;
  else minute = ((timeLimit-currentTime)/60)%60; //분
  if((timeLimit-currentTime)/3600 < 0) hour = 0;
  else hour = ((timeLimit-currentTime)/3600)%60; //시
  
 
  lcd.setCursor(0,1);
   if(hour<10){
    lcd.print("0");
    lcd.setCursor(1,1);
  }
  lcd.print(hour);
  
  lcd.print(":");
  lcd.setCursor(3,1);
  if(minute<10){
    lcd.print("0");
    lcd.setCursor(4,1);
  }
  lcd.print(minute);
  
  lcd.print(":");
  lcd.setCursor(6,1);
  if(second<10){
  lcd.print("0");
  lcd.setCursor(7,1);
  }
  lcd.print(second);

    if(second==0&&minute==0&&hour==0)
    {
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("TimeCountDown");
      lcd.setCursor(0,1);
      lcd.print("done");
      state = false;
      mode = 6;

    }
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("done");  
  }
  
}

void servoFn(){
  int idx=1, jdx=0;
  while(idx>jdx){
    myServo.write(idx++);
    jdx++;
    if (idx==180) break;
  }
  idx=179;
  jdx=180;
  while(jdx>idx){
    myServo.wirte(idx--);
    if (idx==0) break;
  }
}
