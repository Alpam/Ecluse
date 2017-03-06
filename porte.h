#ifndef PORTE_H
#define PORTE_H

#include "gear.h"

class Porte : public Gear
{
public:
    Porte();
    void sendSignal(int signal, int zone);
};

#endif // PORTE_H
