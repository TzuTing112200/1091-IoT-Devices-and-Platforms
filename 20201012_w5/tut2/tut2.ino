#include <dht.h>
#define dht_dpin A0

dht DHT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(300);
  Serial.println("Humidity and temperature\n\n");
  delay(700);
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_dpin);

  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("% ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C");
  delay(1000);
}
