/*
  Calibration

  Demonstrates one technique for calibrating sensor input. The sensor readings
  during the first five seconds of the sketch execution define the minimum and
  maximum of expected values attached to the sensor pin.

  The sensor minimum and maximum initial values may seem backwards. Initially,
  you set the minimum high and listen for anything lower, saving it as the new
  minimum. Likewise, you set the maximum low and listen for anything higher as
  the new maximum.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0
  - LED attached from digital pin 9 to ground

  created 29 Oct 2008
  by David A Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Calibration
*/
#define PIROUT 2
// These constants won't change:
const int sensorPin = A0;    // pin that the sensor is attached to
const int ledPin = 9;        // pin that the LED is attached to
int inputPin = A0;

// Calibration variables:
int sensorValue = 0;         // the sensor value


void setup() {
  // turn on LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(PIROUT, INPUT);
  
  // initialize serial communication with computer:
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  sensorValue = analogRead(sensorPin);

  // fade the LED using the calibrated value:
  if (sensorValue > 950)
    digitalWrite(ledPin, LOW);
  else
  {
    if(digitalRead(PIROUT) == HIGH)
    {
      Serial.println("Some body is here");
      digitalWrite(ledPin, HIGH);
    }
    else
    {
      Serial.println("Nothing Detected by PIR Sensor");
      digitalWrite(ledPin, LOW);
    }
  }

  delay(500);
}
