const int duration = 1000;
unsigned long pre_time = 0;
unsigned long cur_time = 0;
volatile byte state = HIGH;

void isr()
{
  cur_time = millis();
  Serial.println(pre_time);
  if(cur_time - pre_time >= duration)
  {
    Serial.println("인터럽트 발생");
    pre_time = cur_time;
    digitalWrite(13, state);
    state = !state;
    Serial.println(state);
    Serial.println(pre_time);
  }
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  attachInterrupt(0,isr,FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:

}
