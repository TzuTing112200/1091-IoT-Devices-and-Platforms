#define sensorPower 7
#define sensorPin A0
int val = 0; 

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
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
  Serial.println(level);
  delay(1000);
}
