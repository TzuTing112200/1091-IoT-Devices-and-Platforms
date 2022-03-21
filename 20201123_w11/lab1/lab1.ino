#include <Wire.h>

#include "I2Cdev.h"
#include "HMC5883L.h"
#include "BMP085.h"

HMC5883L mag;
BMP085 barometer;

int16_t mx, my, mz;

float temperature;
float pressure;
float seaLevelPressure = 101325;
float altitude;
int32_t lastMicros;

const int redPin = 3;
const int greenPin = 5;

unsigned long start, now;
unsigned long cycle = 5000;
unsigned long alarm = 3000;

String taskName[] = { "Task : Take 1 meter higher",
                      "Task : Heading to North" };
int task = 0;
int count = 1;

void setup() {
  Wire.begin();
  
  Serial.begin(9600);

  Serial.println();
  Serial.println("Initializing I2C devices...");
  mag.initialize();
  barometer.initialize();
  
  Serial.println("Testing device connections...");
  Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
  Serial.println(barometer.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  Serial.println();
}

float getAltitude()
{   
    // request temperature
    barometer.setControl(BMP085_MODE_TEMPERATURE);
    
    // wait appropriate time for conversion (4.5ms delay)
    lastMicros = micros();
    while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());

    // read calibrated temperature value in degrees Celsius
    temperature = barometer.getTemperatureC();

    // request pressure (3x oversampling mode, high detail, 23.5ms delay)
    barometer.setControl(BMP085_MODE_PRESSURE_3);
    while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());

    // read calibrated pressure value in Pascals (Pa)
    pressure = barometer.getPressure();

    // calculate absolute altitude in meters based on known pressure
    // (may pass a second "sea level pressure" parameter here,
    // otherwise uses the standard value of 101325 Pa)
    return(barometer.getAltitude(pressure, seaLevelPressure));
}

void loop() {
  start = millis();
  altitude = getAltitude();
  Serial.println(taskName[0]);
  
  while (true) 
  {
    now = millis();
    
    if (now - start > alarm)
    {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      if (count % 5 == 0)
      {
        tone(8, 600, 200);
        delay(20);
        noTone(8);
        
        count = 1;
      }
    }
    else
    {
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
    }

    if (now - start < cycle)
    {
      if (task == 0)
      {
        float temp = getAltitude();
        
        Serial.print("Altitude:\t");
        Serial.println(temp);
        
        if (temp - altitude > 1)
        {
          analogWrite(redPin, 0);
          analogWrite(greenPin, 0);
          Serial.print("Task finish!");

          delay(3000);  

          task = 1;
          start = millis();
          altitude = getAltitude();
          Serial.println(taskName[1]);
        }
      }
      else
      {
        mag.getHeading(&mx, &my, &mz);
        
        float heading = atan2(my, mx);
        if(heading < 0)
          heading += 2 * M_PI;

        heading = heading * 180/M_PI;
        Serial.print("heading:\t");
        Serial.println(heading);

        if (heading > 359 && heading < 1)
        {
          analogWrite(redPin, 0);
          analogWrite(greenPin, 0);
          Serial.print("Task finish!");

          delay(3000);

          task = 0;
          start = millis();
          altitude = getAltitude();
          Serial.println(taskName[0]);
        }
      }
    }
    delay(100);
    count ++;
  }
}
