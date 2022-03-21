const int  buttonPin = 2;
const int redPin = 3;
int buttonState = 0;
int ans = 0;
int num = -1;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  analogWrite(redPin, 255);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  if (buttonState == 1){
    Serial.println("--請輸入0~1023之間的數字--");
    ans = constrain(analogRead(A0), 0, 1023);
  }
  else {
    while (Serial.available() > 0) {
      int num = Serial.parseInt();
      if (num == ans) {
        Serial.print(num);
        Serial.println(" Yes");
        analogWrite(redPin, 0);
        while (true)
          delay(1000);
      }
      else if (num > ans) {
        Serial.print(num);
        Serial.println(" too large");
      }
      else {
        Serial.print(num);
        Serial.println(" too small");
      }
        
      if (Serial.read() == '\n')
        break;
    }
  }
  delay(1000);
}
