#ifndef PORTE_H
#define PORTE_H

#include "gear.h"

class Porte : public Gear
{
public:
    Porte();
    bool ask_open();
    bool ask_close();
};

#endif // PORTE_H
