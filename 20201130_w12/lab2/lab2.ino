#include <SoftwareSerial.h>

#include <dht.h>
#define dht_dpin A0

dht DHT;

unsigned long BAUD_RATE = 9600;

const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;

const int READ_TIME = 500; //ms

unsigned long prevMillis;

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

void setup() {
  // Start serial communications.
  // The baud rate must be the same for both the serial and the bluetooth.
  Serial.begin(BAUD_RATE);
  bluetooth.begin(BAUD_RATE);
  Serial.println("Setup Complete");
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    String str = "";
    Serial.print("Input: ");
    
    prevMillis = millis();
    while (millis() - prevMillis < READ_TIME) {
      if (Serial.available()) {
        char c = Serial.read();
        if (c != 10 && c != 13) { // Don't send line end characters to HM10.
          str += c;
        }
      }
    }
    
    bluetooth.print(str);
    Serial.println(str);
  }

  if (bluetooth.available()) {
    String str = "";
    Serial.print("Slave_5006:");
    
    prevMillis = millis();
    while (millis() - prevMillis < READ_TIME) {
      if (bluetooth.available()) {
        str += (char) bluetooth.read();
      }
    }
    Serial.println(str);
    if (str == "request temperature and humidity")
    {
      DHT.read11(dht_dpin);
      str = "Temperature is " + (String)DHT.temperature + " C, and humidity = " + (String)DHT.humidity + " %";
      bluetooth.print(str);
    }
  }
}
