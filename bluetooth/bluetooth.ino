#include <SoftwareSerial.h>

SoftwareSerial ble(2,3); //SoftwareSerial [name](TX,RX);

String myStr="";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ble.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(ble.available()){
   
   Serial.write(ble.read());
//    char mychar = ble.read();
//    Serial.println(mychar);
//    myStr += mychar;
//    delay(5);
  }
//  if(!myStr.equals("")){
//    if(myStr =="ledon\r\n"){//리턴이랑 개행이 포함됨
//    digitalWrite(13,HIGH);
//    myStr="";
//    } else if(myStr="ledoff\r\n"){
//      digitalWrite(13,LOW);
//      myStr="";
//    }
//  }
  if(Serial.available())
    ble.write(Serial.read());
}
