#include <ArduinoJson.h>

#define SENSOR_PIN 12
#define BUFFER_SIZE 3
#define END_OF_MESSAGE_SUFFIX "!%"

struct Reading {
  String DeviceId;
  float Value;
};

Reading* readingsBuffer = new Reading[BUFFER_SIZE];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  
  // read all the values and store them in an array
  readingsBuffer[0] = 
  {
    "device1",
    11.1
  };

  readingsBuffer[1] = 
  {
    "device2",
    22.22
  };

  readingsBuffer[2] = 
  {
    "device3",
    333.3
  };

  // Serialize the array to a json string
  String message = CreatePayload(readingsBuffer) + END_OF_MESSAGE_SUFFIX;

  // Send the json string via serial
  Serial.print(message);
}

String CreatePayload(Reading* readings)
{
    DynamicJsonBuffer JSONbuffer;
    JsonObject& root = JSONbuffer.createObject();
    JsonArray& readingsJsonArray = JSONbuffer.createArray();

    for(int i = 0; i < BUFFER_SIZE; i++)
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
