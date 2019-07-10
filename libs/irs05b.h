#ifndef IRS05B
#define IRS05B

#include "Sensor.h"

class Irs05b : public Sensor
{
    public:

    String GetId()
    {
        return _id;
    }

    void Init()
    {
        pinMode(_pinNumber, INPUT);
    };   

    int Read()
    {
        return digitalRead(_pinNumber);
    };

    private:
    String _id = "pololu_irs05b";
    int _pinNumber = 12;
};

#endif