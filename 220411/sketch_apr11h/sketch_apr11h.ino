void setup() {
  // put your setup code here, to run once:
  pinMode(7,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(7));
  int data = digitalRead(7);
  if( data == 1) digitalWrite(13,HIGH);
  else if (data ==0) digitalWrite(13,LOW);
}
