#include "valve.h"
#include <iostream>

Valve::Valve()
    : Gear::Gear()
{}

void Valve::sendSignal(int signal,int num)
{
    switch(signal) {
        case OUVRE : std::cout << "Ouvert Valve";
            break;
        case FERME  : std::cout << "Ferme Valve";
            break;
        default     : std::cout << "Stop Valve";
    }
}

