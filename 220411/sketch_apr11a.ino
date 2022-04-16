void setup() {
  Serial.begin(9600);  
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() {

  if(Serial.available()>0)
  {
  
   int data = Serial.read();
   if(data == '1') digitalWrite(13, HIGH);
   else if(data == '2') digitalWrite(12,HIGH);
   else if(data =='3') digitalWrite(11, HIGH); 
    else if(data == '4') 
   {
    for(int idx = 0; idx<10; idx++)
    {
    digitalWrite(10, HIGH);
    delay(200);
    digitalWrite(10, LOW);
    delay(200);
    }
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
   
   }
   else if(data == '0')
   {
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
   }
   Serial.print(data); 
  }
} 
