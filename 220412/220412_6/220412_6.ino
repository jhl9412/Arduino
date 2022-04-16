int trig = 2;
int echo = 3;
#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 
int notes[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C }; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int dis = pulseIn(echo,HIGH)*340/2/10000;
  Serial.println(dis);

    for(int idx=0; idx<12; idx++)
    {
      tone(6, notes[idx],500);
      
    }
  
    for (int i = 12; i < 25; i++) { 
    tone (6, notes[i],500); 
   
    } 


  
 
}
