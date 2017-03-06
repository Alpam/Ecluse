#ifndef VALVE_H
#define VALVE_H

#include "gear.h"


class Valve : public Gear
{
public:
    Valve();
    void open();
    void close();
    void putAlarm();
    void disableAlarm();
};

#endif // VALVE_H
