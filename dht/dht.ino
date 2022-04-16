#include <DHT.h>
#include <MsTimer2.h> //내부 인터럽트를 이용한 데이터 전송

#include <SoftwareSerial.h>
#define TX 2
#define RX 3
String str = "";
DHT dht(8,DHT11);// (핀, dht종류)
SoftwareSerial soft_Serial (TX,RX);
int tem=0;
int hum = 0;
void sendData(){

  Serial.print("Temp : ");
  Serial.println(tem);
  Serial.print("Humidity : ");
  Serial.println(hum);
  str = "temhum$"+(String)tem+"$"+(String)hum;
  Serial.println(str);
  int idx = 0;
  while(str[idx]!='\0'){
    soft_Serial.write(str[idx]);
    idx++;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  soft_Serial.begin(9600);
  dht.begin();
  MsTimer2::set(1000, sendData);
  MsTimer2::start(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  tem = dht.readTemperature();
  hum = dht.readHumidity();

}
