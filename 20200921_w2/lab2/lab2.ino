int led = 12;
int pushButton = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT);
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

void showSOS() {
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

void loop() {
  int buttonState = digitalRead(pushButton);
  if(buttonState == 1) {
    showSOS();
  }
  delay(1);
}
