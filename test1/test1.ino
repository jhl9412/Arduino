#include <IRremote.hpp>

#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <DHT.h>
#include <MsTimer2.h> //내부 인터럽트를 이용한 데이터 전송

// 변수 선언

#define TX 2
#define RX 3
String state = ""; //TempHum data
int RECV_PIN = 7;
int NUM[10] = {0};
int count = 0;  
int mode = 0; // manual = 1, auto =2;
int tem=0; // Temperature
int hum = 0; // Humidity
// --------------------------------------
DHT dht(8,DHT11);// (핀, dht종류) 


SoftwareSerial soft_Serial (TX, RX); // 시리얼 통신
LiquidCrystal_I2C lcd(0x27, 16, 2); // lcd 출력
//-------------------------------------------------
 //리모컨 함수
void putNum(int remoteNum); //리모컨 숫자 입력
void selectMenu(); // 홈화면
void modeManual(int nSpeed); // Manual 기능
// 인터럽트 서비스 함수
void sendData(){

//  delay(100);
  Serial.print("Temp : "); // 지울예정
  Serial.println(tem);// 지울예정
  Serial.print("Humidity : ");// 지울예정
  Serial.println(hum);// 지울예정
//  state = "temhum$"+(String)tem+"$"+(String)hum;
//  Serial.println(state);// 지울예정
//  int idx = 0;
//  while(state[idx]!='\0'){
//    soft_Serial.write(state[idx]);
//    idx++;
//  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);

  lcd.init();
  lcd.backlight();
  lcd.print("RemoteControl");
  soft_Serial.begin(9600);
  // 내부 인터럽트, 온습도 데이털
  dht.begin();
 // MsTimer2::set(10000, sendData);
  // MsTimer2::start();
}
/*
mode 1 : manual
mode 2 : home
mode 3 : auto
mode 4 : manual power 1
mode 5 : manual power 2
mode 6 : manual stop
mode 7 : manual timer
mode 8 : manual turn

*/
void loop() {
  // put your main code here, to run repeatedly:
//  tem = dht.readTemperature();
//  hum = dht.readHumidity();
  if(IrReceiver.decode()){
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);// 지울예정

    switch(IrReceiver.decodedIRData.decodedRawData){
      case 0xFFA25D:soft_Serial.write(1);  break;//ch- : manual
      case 0xFF629D:soft_Serial.write(2);break;//ch : home, all stop
      case 0xFFE21D:soft_Serial.write(3);break;// ch+ : auto
      case 0xFF22DD:soft_Serial.write(4);break; // prev : power1
      case 0xFF02FD:soft_Serial.write(5);break; // next : power2
      case 0xFFC23D:soft_Serial.write(6);break; // play/pause : stop
//      case 0xFFE01F:soft_Serial.write(7);break; // vol- : timer
//      case 0xFFC23D:soft_Serial.write(8);break; // vol+ : turn
      case 0xFF30CF: putNum(1);break; 
      case 0xFF18E7: putNum(2);break; 
      case 0xFF7A85: putNum(3);break;
      case 0xFF10EF: putNum(4);break;
      case 0xFF38C7: putNum(5);break;
      case 0xFF5AA5: putNum(6);break;
      case 0xFF42BD: putNum(7);break;
      case 0xFF4AB5: putNum(8);break;
      case 0xFF52AD: putNum(9);break;
      case 0xFF6897: putNum(0);break;
      case 0xFF906F:
        lcd.setCursor(0,1);lcd.print("                ");
        lcd.setCursor(0,1);
        for(int idx = 0; idx<count;idx++){
          lcd.print(NUM[idx]);
          soft_Serial.write(NUM[idx]);
        }
        count =0;
        default : break;
    }
  
    IrReceiver.resume();
  }
  delay(100);
   
}
// 리모컨 입력값 저장
void putNum(int remoteNum) {
  lcd.setCursor(count, 1); lcd.print(remoteNum); NUM[count] = remoteNum; count++;
}
// auto/manual 선택 화면 출력
void selectMenu() {
  lcd.setCursor(0, 0); lcd.print("Select Menu");
}
