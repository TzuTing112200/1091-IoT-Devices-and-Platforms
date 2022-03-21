#define echoPin 7
#define trigPin 8

int maximumRange = 200;
int minimumRange = 0;
long duration, distance;
int check = -1;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58.2;

  // 決定警報頻率
  if (distance > 100) {
    check = -1;
    Serial.println("Safe");
  }
  else if (distance >= 30) {
    check = 10;
    Serial.println("Be careful");
  }
  else {
    check = 5;
    Serial.println("Dangerous");
  }

  // 警報
  if (check > 0 && count > check) {
    tone(9, 1000, 125);
    count = 0;
  }
  else {
    count = count + 1;
  }
  
  delay(50);
}
