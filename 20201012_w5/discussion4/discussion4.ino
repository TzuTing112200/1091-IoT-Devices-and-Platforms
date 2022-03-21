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

  float e = DHT.humidity / 100 * 6.105 * exp((17.27 + DHT.temperature)/(237.7 + DHT.temperature));
  float AT = 1.04 * DHT.temperature + 0.2 * e - 0.65 * 2.7 - 2.7;

  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("% ");
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.print("C ");
  Serial.print("Apparent temperature = ");
  Serial.print(AT);
  Serial.println("C");
  delay(1000);
}
