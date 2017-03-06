#include "valve.h"

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
