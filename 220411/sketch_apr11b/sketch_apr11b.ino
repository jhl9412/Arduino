#include <MsTimer2.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void isr()
{
    static int analog_IN = analogRead(A0);
    Serial.println(analog_IN);
    
  
}

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
  Serial.begin(9600);
  MsTimer2::set(500, isr);
  MsTimer2::start();  
// 반복문을 안하고 있는데 계속 호출되고 있음. 인터럽트는 우선순위가 높기 때문에
// 타이머가 우선순위를 가지고 있음. 
}

void loop() {
  // put your main code here, to run repeatedly:
    lcd.setCursor(4,1);
    lcd.print(analog_IN);
    lcd.print(" ");
    //if (analog_IN<400)
    //{
    //  digitalWrite(7,HIGH);
    //  lcd.setCursor(12,1);
    //  lcd.print(" ON");
    //}
    //else
    //{
    //  digitalWrite(7,LOW);
    //  lcd.setCursor(12,1);
    //  lcd.print("OFF");
    //}

}
