#ifndef IRS09A
#define IRS09A

#include "Sensor.h"
#include "VL6180X.h"
#include <Wire.h>

class Irs09a : public Sensor
{
    public:

    String GetId()
    {
        return _id;
    }

    void Init()
    {
        Wire.begin();  
        sensor.init();
        sensor.configureDefault();
        sensor.setTimeout(500);
    };   

    int Read()
    {
        return sensor.readRangeSingleMillimeters();
    };

    private:
    String _id = "pololu_irs09a";
    VL6180X sensor;
};

#endif