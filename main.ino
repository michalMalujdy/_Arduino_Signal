#include "libs/irs05b.h"
#include "libs/Sensor.h"

#include <ArduinoJson.h>

#define END_OF_MESSAGE_SUFFIX "!%"
#define SENSORS_NUMBER 1

Sensor** sensors = new Sensor*[SENSORS_NUMBER];

struct Reading {
  String DeviceId;
  float Value;
};

Reading* readings = new Reading[SENSORS_NUMBER];

void setup() {
  Serial.begin(9600);

  SetupSensors();
}

void loop() 
{
  delay(200);
  
  // read all the values and store them in an array
  ReadAllInputs();

  // Serialize the array to a json string
  String message = CreatePayload(readings) + END_OF_MESSAGE_SUFFIX;

  // Send the json string via serial
  Serial.print(message);
}

void SetupSensors()
{
  sensors[0] = new Irs05b();

  for (int i = 0; i < SENSORS_NUMBER; i++)
  {
    sensors[i]->Init(String("pololu_irs05b"));
  }
}

void ReadAllInputs()
{
  for (int i = 0; i < SENSORS_NUMBER; i++)
  {
    readings[i].DeviceId = sensors[i]->Id;
    readings[i].Value = sensors[i]->Read();
  }
}

String CreatePayload(Reading* readings)
{
    DynamicJsonBuffer JSONbuffer;
    JsonObject& root = JSONbuffer.createObject();
    JsonArray& readingsJsonArray = JSONbuffer.createArray();

    for(int i = 0; i < SENSORS_NUMBER; i++)
    {
      JsonObject& readingJsonObj = JSONbuffer.createObject();

      readingJsonObj["DeviceId"] = readings[i].DeviceId;
      readingJsonObj["Value"] = readings[i].Value;

      readingsJsonArray.add(readingJsonObj);
    }

    root["Readings"] = readingsJsonArray;

    String json;
    root.printTo(json);

    return json;
}
