#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int interruptPin = 2;

unsigned long currentTime = 0;
unsigned long prev_Time = 0;
int second, minute, hour;
int timeLimit=0;
boolean state=false;



void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.scrollDisplayRight();
  lcd.setCursor(0,0);
  lcd.print("TimeCountDown");
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), switchFn, FALLING);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(state==true)
  {
  currentTime = (millis()-prev_Time)/1000;//인터럽트 발생시 시간과 비교해 시간을 카운트.
  Serial.print(currentTime);
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
      lcd.setCursor(1,1);
      lcd.print("done");
      state = false;
      delay(1000);
    }
  }
  else{
    lcd.setCursor(1,1);
    lcd.print("nothing");  
  }
}

void switchFn(){
  state=!state;
  prev_Time=millis();
  timeLimit = 3600;
}
