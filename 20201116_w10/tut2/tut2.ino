#define PIROUT 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIROUT, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(PIROUT) == HIGH)
    Serial.println("Some body is here");
  else
    Serial.println("Nothing Detected by PIR Sensor");
  delay(1000);
} 
