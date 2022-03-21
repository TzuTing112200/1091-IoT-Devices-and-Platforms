int led = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void showSignal(int i, int t){
  if(i == 1){
    digitalWrite(led, HIGH);
    delay(500 * t);
  }
  else{
    digitalWrite(led, LOW);
    delay(500 * t);
  }
}

void loop() {
  // S
  showSignal(1, 1);
  showSignal(0, 1);
  showSignal(1, 1);
  showSignal(0, 1);
  showSignal(1, 1);
  
  showSignal(0, 3);
  
  // O
  showSignal(1, 3);
  showSignal(0, 1);
  showSignal(1, 3);
  showSignal(0, 1);
  showSignal(1, 3);
  
  showSignal(0, 3);
  
  // S
  showSignal(1, 1);
  showSignal(0, 1);
  showSignal(1, 1);
  showSignal(0, 1);
  showSignal(1, 1);
  
  showSignal(0, 7);
}
