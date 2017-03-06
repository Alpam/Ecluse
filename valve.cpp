#include "valve.h"
#include <iostream>

Valve::Valve()
    : Gear::Gear()
{}

void Valve::open() {
    if (getAlarm() != ON) switchState(OUVERT);
}

void Valve::close() {
    if (getAlarm() != ON) switchState(FERME);
}

void Valve::putAlarm() {
    if (getAlarm() != ON) setAlarm(ON);
}

void Valve::disableAlarm() {
    if (getAlarm() != OFF) setAlarm(OFF);
}

void Valve::sendSignal(int signal,int num)
{
    switch(signal) {
        case OUVERT : std::cout << "Ouvert Valve";
            break;
        case FERME  : std::cout << "Ferme Valve";
            break;
        default     : std::cout << "Stop Valve";
    }
}

