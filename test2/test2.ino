

#include <IRremote.h>


int cnt =0;
int RECV_PIN = 2;

// --------------------------------------

IRrecv irrecv(RECV_PIN); // 적외선 수신 지울예정
decode_results results; // 리모컨

void sendData(){
  if(cnt==0)Serial.println("hello");
  cnt++;
  

 
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  attachInterrupt(digitalPinToInterrupt(RECV_PIN), sendData, FALLING);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(irrecv.decode(&results)){
    detachInterrupt(sendData);
    Serial.println(results.value, HEX);// 지울예정

    irrecv.resume();
  }
  delay(100);
   cnt=0;
}
