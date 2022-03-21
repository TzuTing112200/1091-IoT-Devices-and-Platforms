/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int pos = 90;

// flase -> - ； true -> +
bool turn = 0;
int lastVal = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  //val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  Serial.println(val);
  if (val < 1000) {
    if (lastVal > val) {
      turn = !turn;
    }
    
    if (turn) {
      if (pos < 180) {
        pos = pos + 5;
      }
    }
    else {
      if (pos > 0) {
        pos = pos - 5;
      }
    }
    lastVal = val;
  }
    
  myservo.write(pos);
  
  //myservo.write(val);                  // sets the servo position according to the scaled value
  delay(50);                           // waits for the servo to get there
}
