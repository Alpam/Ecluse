#ifndef PORTE_H
#define PORTE_H

#include "gear.h"

class Porte : public Gear
{
public:
    Porte();
    void sendSignal(int signal, int num);
    void ask_open();
    void ask_close();
};

#endif // PORTE_H
