#include "pitches.h"

// 12345-643-2-1--- 5435432- 5435432- 12345-643-2-1---
int melody_1[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
};
int melody_2[] = {
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4
};

// 12345-643-2-1--- 5435432- 5435432- 12345-643-2-1---
int noteDurations_1[] = {
  8, 8, 8, 8, 4, 8, 8, 4, 4, 2
};
int noteDurations_2[] = {
  6, 16, 8, 8, 8, 8, 4
};

void impl_tone(int part){
  if(part == 1) {
    for (int thisNote = 0; thisNote < 10; thisNote++) {
      int noteDuration = 2000 / noteDurations_1[thisNote];
      tone(8, melody_1[thisNote], noteDuration);
  
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      noTone(8);
    }
  }
  else if(part == 2) {
    for (int thisNote = 0; thisNote < 7; thisNote++) {
  
      int noteDuration = 2000 / noteDurations_2[thisNote];
      tone(8, melody_2[thisNote], noteDuration);
      
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      noTone(8);
    }
  }
}

void setup() {
  impl_tone(1);
  impl_tone(2);
  impl_tone(2);
  impl_tone(1);
}

void loop() {
  // no need to repeat the melody.
}
