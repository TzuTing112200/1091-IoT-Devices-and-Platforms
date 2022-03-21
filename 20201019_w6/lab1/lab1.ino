#define echoPin 7
#define trigPin 8

const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

int maximumRange = 200;
int minimumRange = 0;
long duration, distance;
int red= 255;
int green = 255;
int blue = 255;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
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
    red= 255;
    green = 0;
    blue = 255;
    Serial.println("Safe");
  }
  else if (distance >= 30) {
    red= 0;
    green = 0;
    blue = 255;
    Serial.println("Be careful");
  }
  else {
    red= 0;
    green = 255;
    blue = 255;
    Serial.println("Dangerous");
  }

  // fade the red, green, and blue legs of the LED:
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);

  // 警報
  /*
  if (check > 0 && count > check) {
    tone(9, 1000, 125);
    count = 0;
  }
  else {
    count = count + 1;
  }
  */
  
  delay(50);
}
