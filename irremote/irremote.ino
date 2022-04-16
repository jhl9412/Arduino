//#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>
//
//// 변수 선언
//

//int TX= 2;
//int RX= 3;
int RECV_PIN = 7;
int NUM[10] = {0};
int count = 0;
int mode = 0; // manual = 1, auto =2;
//모터 변수
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;

int nSwitch = 0;
boolean bReverse = false;

int nSpeed = 150;
String sMeg = "Switch : ";

// --------------------------------------

IRrecv irrecv(RECV_PIN); // 적외선 수신
decode_results results; // 리모컨
//SoftwareSerial soft_Serial (TX, RX); // 시리얼 통신
LiquidCrystal_I2C lcd(0x27, 16, 2); // lcd 출력
//-------------------------------------------------
 //리모컨 함수
void putNum(int remoteNum); //리모컨 숫자 입력
void selectMenu(); // 홈화면
void modeManual(int nSpeed); // Manual 기능

// 모터 함수
void runMotor(int nSpeed);
void setMotor(int nSpeed, boolean bReverse);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  irrecv.enableIRIn();
//
//  lcd.init();
//  lcd.backlight();
//  lcd.print("RemoteControl");
//  soft_Serial.begin(9600);
  //모터 setup
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}
/*
mode 1 : manual
mode 2 : home
mode 3 : auto
mode 4 : manual power 1
mode 5 : manual power 2
mode 6 : manual stop
mode 7 : manual timer
mode 8 : 

*/
void loop() {
  // put your main code here, to run repeatedly:

//    if(irrecv.decode(&results)){
//      Serial.println(results.value, HEX);
//  
//      switch(results.value){
//        //case 0xFFA25D:soft_Serial.write("manual");mode = 1;Serial.print(mode);break;//ch- : manual
//
//        case 0xFF629D:selectMenu();break;//ch : home, all stop
//        //case 0xFFE21D:soft_Serial.write("auto");mode = 2;break;// ch+ : auto
//        case 0xFF22DD:  break; // prev - power1
//        case 0xFF02FD: break; // next - power2
//        case 0xFFC23D: break; // play/pause - stop
//        case 0xFF30CF: putNum(1); break; //1
//        case 0xFF18E7: putNum(2);break; //2
//        case 0xFF7A85: putNum(3);break;
//        case 0xFF10EF: putNum(4);break;
//        case 0xFF38C7: putNum(5);break;
//        case 0xFF5AA5: putNum(6);break;
//        case 0xFF42BD: putNum(7);break;
//        case 0xFF4AB5: putNum(8);break;
//        case 0xFF52AD: putNum(9);break;
//        case 0xFF6897: putNum(0);break;
//        case 0xFF906F:
//  
//        lcd.setCursor(0,1);lcd.print("                ");
//        lcd.setCursor(0,1);
//        for(int idx = 0; idx<count;idx++){
//          lcd.print(NUM[idx]);
////          soft_Serial.write(NUM[idx]);
//        }
//        count =0;
//        default : break;
//      }
//  
//      irrecv.resume();
//    }
  modeManual(nSpeed);
 // runMotor(nSpeed);
  delay(100);
}
// 리모컨 입력값 저장
//void putNum(int remoteNum) {
//  lcd.setCursor(count, 1); lcd.print(remoteNum); NUM[count] = remoteNum; count++;
//}
// auto/manual 선택 화면 출력
//void selectMenu() {
//  lcd.setCursor(0, 0); lcd.print("Select Menu");
//}

//motor
void modeManual(){
  if( mode ==1) runMotor(nSpeed);
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
