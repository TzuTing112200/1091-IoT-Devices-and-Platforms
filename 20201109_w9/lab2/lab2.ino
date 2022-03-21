const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 5000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8,INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  starttime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) >= sampletime_ms)
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; 
    Serial.print("concentration = ");
    Serial.print(concentration);
    Serial.println(" pcs/0.01cf");
    Serial.println("\n");
    lowpulseoccupancy = 0;
    starttime = millis();
    
    int red = 0;
    int green = 0;
    int blue = 0;

    if(concentration < 500)
      green = 255;
    else if(concentration < 1000)
    {
      red = 255;
      green = 255;
    }
    else
      red = 255;
    
    red = 255 - constrain(red, 0, 255);
    green = 255 - constrain(green, 0, 255);
    blue = 255 - constrain(blue, 0, 255);
    
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);

  }
}
