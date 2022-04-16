#include <SPI.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc(SS_PIN, RST_PIN);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc.PCD_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!mfrc.PICC_IsNewCardPresent())
    return;
  if(!mfrc.PICC_ReadCardSerial())
    return;

  if(mfrc.uid.uidByte[0] == 19 &&
  mfrc.uid.uidByte[1] == 99 &&
  mfrc.uid.uidByte[2] == 169 &&
  mfrc.uid.uidByte[3] == 163)
  {
    Serial.println("Authorized access");    
    delay(500);
  }else{
    Serial.println("Access denied");
    delay(500);
  }
  Serial.print("Card UID:");
  for(byte i=0; i<4 ; i++)
  {
    Serial.print(mfrc.uid.uidByte[i]);
    Serial.print(" ");
    
  }
  Serial.println();
}
