#ifndef SDS01A
#define SDS01A

#include "Sensor.h"

class Sds01a : public Sensor
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
    String _id = "pololu_sds01a";
    int _pinNumber = 11;
};

#endif