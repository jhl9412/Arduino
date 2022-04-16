#include <MsTimer2.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.print("LJH");
  lcd.setCursor(0,1);
  lcd.print("CDS:");
  lcd.setCursor(8,1);
  lcd.print("LED:");
  pinMode(A0,INPUT);
  pinMode(7,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
   int analog_IN = analogRead(A0);
    lcd.setCursor(4,1);
    lcd.print(analog_IN);
    lcd.print(" ");
    if (analog_IN<400)
    {
      digitalWrite(7,HIGH);
      lcd.setCursor(12,1);
      lcd.print(" ON");
    }
    else
    {
      digitalWrite(7,LOW);
      lcd.setCursor(12,1);
      lcd.print("OFF");
    }
    
    delay(1000);
    // lcd.write(analog_IN);
  
}
