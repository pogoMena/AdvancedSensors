// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

DeviceAddress address;

boolean sensorFound = false;

void setup()
{

  Serial.begin(115200);
  if (DS18B20.getAddress(address, 0))
  {

    sensorFound = true;

    for (uint8_t i = 0; i < 8; i++)
    {
      Serial.print(address[i], HEX);
    }

    DS18B20.begin();
  }
  else
  {
    Serial.println("Device sensor not found");
  }
}

void loop()
{
  float answer;

  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();

  answer = DS18B20.getTempCByIndex(0);

  String feels = "";

  if (answer < 10)
  {
    feels += "Too cold!";
  }
  else if (answer < 15)
  {
    feels += "Cool";
  }
  else if (answer < 20)
  {
    feels += "Perfect";
  }
  else if (answer < 25)
  {
    feels += "Warm";
  }
  else if (answer < 30)
  {
    feels += "Hot";
  }
  else
  {
    feels += "Too Hot!";
  }

  Serial.println("The temperature is " + (String)answer + " which is " + feels);
  delay(2000);
}
