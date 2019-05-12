#include <ArduinoJson.h>

#define SENSOR_PIN 12

struct Reading {
  String DeviceId;
  float Value;
};

Reading* readings = new Reading[10];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  
  // read all the values and store them in an array
  readings[0] = 
  {
    "device1",
    11.1
  };

  readings[1] = 
  {
    "device2",
    22.22
  };

  readings[2] = 
  {
    "device3",
    333.3
  };

  // Serialize the array to a json string
  String payload = CreatePayload(readings);

  // Send the json string via serial
  Serial.print(payload);
  Serial.println();
}

String CreatePayload(Reading* readingsToSend)
{
    DynamicJsonBuffer JSONbuffer;
    JsonObject& root = JSONbuffer.createObject();
    JsonArray& arr = JSONbuffer.createArray();
    
    JsonObject& obj1 = JSONbuffer.createObject();
    obj1["DeviceId"] = "device1";
    obj1["Value"] = 12.2;
    
    JsonObject& obj2 = JSONbuffer.createObject();
    obj2["DeviceId"] = "device2";
    obj2["Value"] = 1;
    
    arr.add(obj1);
    arr.add(obj2);

    root["Readings"] = arr;

    String json;
    root.printTo(json);

    return json;
}
