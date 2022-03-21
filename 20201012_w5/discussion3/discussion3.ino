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
  
  float T_dp = DHT.temperature - ((100 - DHT.humidity) / 5);

  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("% ");
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.print("C ");
  Serial.print("Dew point temperature = ");
  Serial.print(T_dp);
  Serial.println("C");
  delay(1000);
}
