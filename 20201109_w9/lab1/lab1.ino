int sensorPin = A1;
int ledPin_1 = 8;
int ledPin_2 = 12;
int ledPin_3 = 13;
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin_1, OUTPUT);
  pinMode(ledPin_2, OUTPUT);
  pinMode(ledPin_3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorValue);
//  digitalWrite(ledPin, HIGH);
//  delay(sensorValue);
//  digitalWrite(ledPin, LOW);
//  delay(sensorValue);
  if(sensorValue > 100)
    digitalWrite(ledPin_1, HIGH);
  if(sensorValue > 200)
    digitalWrite(ledPin_2, HIGH);
  if(sensorValue > 300)
    digitalWrite(ledPin_3, HIGH);
  Serial.println(sensorValue, DEC);
  delay(50);
}
