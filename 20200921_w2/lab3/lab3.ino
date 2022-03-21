int led = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void showSignal(int i, int t){
  float brightness = getBrightness();
  if(i == 1){
    analogWrite(led, brightness);
    delay(500 * t);
  }
  else{
    analogWrite(led, 0);
    delay(500 * t);
  }
}

float getBrightness(){
  int sensorValue = analogRead(A0);
  float brightness = sensorValue * (255.0 / 1023.0);
  Serial.println(brightness);
  return brightness;
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
