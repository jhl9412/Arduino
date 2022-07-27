

#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <DHT.h>
 
 

// 변수 선언

#define TX 4
#define RX 3
int sendCount =0; //데이터 전송 조건
String state = ""; //온도, 습도 데이터 변수 선언
int RECV_PIN = 2; // 적외선 수신기 핀 + 인터럽트 발생 핀
int tem=0; // 온도 변수
int hum = 0; // 습도 변수
int interruptCount =1; //외부 인터럽트 발생 조건
// --------------------------------------
DHT dht(8,DHT11);// 온습도 센서(핀, dht종류) 
IRrecv irrecv(RECV_PIN); // 적외선 수신기
decode_results results; // 수신 신호 디코딩 값
SoftwareSerial soft_Serial (TX, RX); // 시리얼 통신

//-------------------------------------------------

// 인터럽트 서비스 함수
void sendData(){
  if(interruptCount==0){
    sendCount = 1;
    interruptCount++;
  }
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  irrecv.enableIRIn(); // IR 시작
  soft_Serial.begin(9600); // 시리얼 통신 시작
  dht.begin(); // 온습도 센서 시작
  attachInterrupt(digitalPinToInterrupt(RECV_PIN), sendData, RISING); // 인터럽트 발생 조건

}
/*
  <Button>     <Mode>
1. Btn CH-   : manual
2. Btn CH    : home
3. Btn CH+   : auto
4. Btn PREV  : 약풍
5. Btn NEXT  : 강풍
6. Btn PL/PS : auto 정지
7. Btn VOL-  : manual 정지
8. Btn VOL+  : manual 회전
9. Btn EQ    : manual 회전 정지
*/
void loop() {
  // 온습도 데이터 수집. state 변수에 데이터 결합.
  tem = dht.readTemperature();
  hum = dht.readHumidity();
  state = (String)tem+", "+(String)hum; 
  // auto 모드에 진입하면 필요한 온습도 데이터 보내기
  if (sendCount==1){
    int idx=0;
    while(state[idx]!='\0')
    {
      soft_Serial.write(state[idx]);
      idx++;
    }
    Serial.println(state);
  }
  delay(2500);
  if(irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);// 지울예정
    switch(results.value)
    {
      case 0xFFA25D:soft_Serial.write("manual");break;//ch- : manual
      case 0xFF629D:soft_Serial.write("home");break;//ch : home, 기능 구현 x
      case 0xFFE21D:delay(1000);soft_Serial.write("auto_ON\n");interruptCount=0;break;// ch+ : auto
      case 0xFF22DD:soft_Serial.write("1");break; // prev : 약풍
      case 0xFF02FD:soft_Serial.write("2");break; // next : 강풍
      case 0xFFC23D:delay(1000);soft_Serial.write("auto_OFF\n");sendCount=0;break; // play/pause : stop
      case 0xFFE01F:soft_Serial.write("3");break; // vol- : stop / go menu
      case 0xFFA857:soft_Serial.write("4");break; // vol+ : turn
      
      case 0xFF906F: soft_Serial.write("5");break; // EQ : turn stop
      default : break;
    }
  
    irrecv.resume();
  }
  

   
}
