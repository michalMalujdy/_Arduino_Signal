#ifndef SENSOR
#define SENSOR

class Sensor
{
    public:

    virtual String GetId() = 0;
    virtual void Init() = 0;
    virtual int Read() = 0;
};

#endif