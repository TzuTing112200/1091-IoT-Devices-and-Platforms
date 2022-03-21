#include <Servo.h>
#define sensorPower 7
#define sensorPin A0

Servo myservo;
int pos = 0; 
int next = 1;
int val = 0; 
int maxValue = 0;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
  delay(5000);
  maxValue = readSensor();  
  Serial.print("Max water level: ");
  Serial.println(maxValue);
  delay(5000);
}

int readSensor() {
  digitalWrite(sensorPower, HIGH); 
  delay(10); 
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}

void loop() {
  // put your main code here, to run repeatedly:
  int level = readSensor();
  
  Serial.print("Water level: ");
  Serial.print(level);

  level = map(level, 0, maxValue, 0, 100);
  
  Serial.print("\t\tpercentage: ");
  Serial.println(level);  

  if(level < 100)
  {
    pos += next;
    myservo.write(pos);
    if(pos >= 180 || pos <= 0)
    next = -next;
  }
  delay(15);
}
