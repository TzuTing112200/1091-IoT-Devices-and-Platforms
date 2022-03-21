#include <dht.h>
#define dht_dpin A0
#define echoPin 7
#define trigPin 8
#define LEDPin 13

dht DHT;

int maximumRange = 200;
int minimumRange = 0;
long duration, distance;

void printDistance(float C_air) {
  float soundSpeed = 20000 / C_air;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration / soundSpeed;

  if (distance >= maximumRange || distance <= minimumRange) {
    Serial.println("-1");
    digitalWrite(LEDPin, HIGH);
  }
  else {
    Serial.println(distance);
    digitalWrite(LEDPin, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  delay(300);
  Serial.println("Humidity and temperature\n\n");
  delay(700);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_dpin);

  
  float T = DHT.temperature;
  float C_air = 331.3 + 0.606 * T;
  Serial.print(C_air);
  Serial.print("\t");

  printDistance(C_air);
  
  delay(50);
}
