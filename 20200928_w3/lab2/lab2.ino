const int buttonPin = 2;

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;
int lock = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long restartDelay = 5000;


int tone_id = 0;

int melody[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void impl_tone(){
  for (int thisNote = 0; thisNote < 10; thisNote++) {
    int noteDuration = 2000 / 4;
    tone(8, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(8);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);
  int sensorValue = analogRead(A0);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  unsigned long temp = millis() - lastDebounceTime;
  if (temp > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      // If press button and lock is LOW, reccord the frequency
      if (buttonState == LOW) {
        if (lock == HIGH) {
          lock = LOW;
        }
        else{
          sensorValue = map(sensorValue, 0, 1023, 60, 2000);
          melody[tone_id] = sensorValue;
          tone_id = (++tone_id) % 10;
          
          Serial.print("melody ： ");
          Serial.print(melody[0]);
          for (int i = 1; i < 10; ++i) {
            Serial.print(", ");
            Serial.print(melody[i]);
          }
          Serial.println();
        }
      }
    }
    else {
      // If press button for 5 mins, replay the melody
      if (buttonState == HIGH && lock == LOW) {
        if (temp > restartDelay){
          Serial.println("Replay the melody ...");
          impl_tone();
          lock = HIGH;
        }
      }
    }
  }
  
  lastButtonState = reading;
}
