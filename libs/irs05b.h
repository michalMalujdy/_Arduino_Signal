#ifndef IRS05B
#define IRS05B

#include "Sensor.h"

#define PIN_NR 12

class Irs05b : public Sensor
{
    public:

    Irs05b()
    {

    };

    void Init(String id)
    {
        Id = id;
        _pinNumber = PIN_NR;
        pinMode(_pinNumber, INPUT);
    };   

    int Read()
    {
        return digitalRead(_pinNumber);
    };

    private:
    int _pinNumber;
};

#endif