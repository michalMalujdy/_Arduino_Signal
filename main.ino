#include <ArduinoJson.h>

#define POLOLU_GPY_PIN 12
#define SENSORS_NUMBER 1
#define END_OF_MESSAGE_SUFFIX "!%"

struct Sensor {
  String Id;
  int Pin;
};

Sensor* sensors = new Sensor[SENSORS_NUMBER];

struct Reading {
  String DeviceId;
  float Value;
};

Reading* readings = new Reading[SENSORS_NUMBER];

void setup() {
  Serial.begin(9600);

  sensors[0] = { "pololu_gp2y0d815z0f", 12 };
  
  SetupInputPins();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  
  // read all the values and store them in an array
  ReadAllInputs();

  // Serialize the array to a json string
  String message = CreatePayload(readings) + END_OF_MESSAGE_SUFFIX;

  // Send the json string via serial
  Serial.print(message);
}

void SetupInputPins()
{
  for (int i = 0; i < SENSORS_NUMBER; i++)
  {
    pinMode(sensors[i].Pin, INPUT);
  }
}

Reading* ReadAllInputs()
{
  for (int i = 0; i < SENSORS_NUMBER; i++)
  {
    readings[i].DeviceId = sensors[i].Id;
    readings[i].Value = digitalRead(sensors[i].Pin);
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
