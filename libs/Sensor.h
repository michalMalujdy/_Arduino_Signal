#ifndef SENSOR
#define SENSOR

class Sensor
{
    public:
    String Id;

    Sensor(){};

    virtual void Init(String id) = 0;
    virtual int Read() = 0;
};

#endif