#ifndef GEAR_H
#define GEAR_H


class Gear // classe abstraite
{
public:
    Gear();
    virtual ~Gear();
    virtual void switchLightColor() = 0;
    virtual bool getAlarm();
    virtual int getState();
    virtual void switchState(int newState);

private:
    int state;
    bool alarm;
};


#endif // GEAR_H
