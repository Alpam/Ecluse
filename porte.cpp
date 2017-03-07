#include "porte.h"
#include "gear.h"
#include <iostream>

Porte::Porte()
    : Gear::Gear()
{}

bool Porte::ask_open() {
    if ((getAlarm() != ON) && (getState() != OUVRE)) {
        switchState(EN_OUVERTURE);
        return true;
    }
    else{
        return false;
    }
}

bool Porte::ask_close() {
    if ((getAlarm() != ON) && (getState() != FERME)){
        switchState(EN_FERMETURE);
        return true;
    }
    else{
        return false;
    }
}

void Porte::arret(){
    switchState(EN_ARRET);
}

