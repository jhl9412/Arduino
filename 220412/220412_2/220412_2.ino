void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analog_IN = analogRead(A0);
  int analog_OUT = map(analog_IN, 0, 950, 0, 255);
  
  analogWrite(11, analog_OUT);
  Serial.println(analog_IN);
  Serial.print("\t");
  Serial.println(analog_OUT);
  delay(100);
}
