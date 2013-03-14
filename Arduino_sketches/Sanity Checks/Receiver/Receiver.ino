
void setup() {
  
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
  
}


void loop() {
  
  digitalWrite(13, digitalRead(8));
  
  
}
