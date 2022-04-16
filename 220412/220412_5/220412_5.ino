int trig = 2;
int echo = 3;

 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int dis = pulseIn(echo,HIGH)*340/2/10000;
  Serial.println(dis);
  if (dis<100)
  {
    digitalWrite(7,HIGH);
     delay(dis);
     digitalWrite(7,LOW);
     delay(dis);
  }
  
   else if(dis <2) digitalWrite(7,LOW);
  
 
}
