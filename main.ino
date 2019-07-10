#include "libs/irs05b.h"
#include "libs/Sensor.h"
#include "libs/irs09a.h"

#include <ArduinoJson.h>

#define END_OF_MESSAGE_SUFFIX "!%"
#define SENSORS_NUMBER 2

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
  sensors[1] = new Irs09a();

  for (int i = 0; i < SENSORS_NUMBER; i++)
  {
    sensors[i]->Init();
  }
}

void ReadAllInputs()
{
  for (int i = 0; i < SENSORS_NUMBER; i++)
  {
    readings[i].DeviceId = sensors[i]->GetId();
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
