#include "porte.h"
#include "gear.h"
#include <iostream>

Porte::Porte()
    : Gear::Gear()
{}

bool Porte::ask_open() {
    if (getAlarm() != ON) {
        switchState(EN_OUVERTURE);
        return true;
    }
    else{
        return false;
    }
}

bool Porte::ask_close() {
    if (getAlarm() != ON){
        switchState(EN_FERMETURE);
        return true;
    }
    else{
        return false;
    }
}

