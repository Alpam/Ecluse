#ifndef VALVE_H
#define VALVE_H

#include "gear.h"


class Valve : public Gear
{
public:
    Valve();
    void sendSignal(int signal, int num);
};

#endif // VALVE_H
