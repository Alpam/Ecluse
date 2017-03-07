#include "gear.h"

Gear::Gear()
{
    state = FERME;
    alarm = OFF;
    panne = false;
}

Gear::~Gear()
{

}

void Gear::switchState(int newState) {
   state = newState;
}

bool Gear::getAlarm() {
   return alarm;
}

bool Gear::getPanne() {
   return panne;
}

int Gear::getState() {
   return state;
}

void Gear::setAlarm(bool a) {
    alarm = a;
}

void Gear::setPanne(bool a) {
    panne = a;
    if(a) setAlarm(ON);
}

bool Gear::open() {
    if((getAlarm() != ON) && (getState() != OUVRE)){
        switchState(OUVRE);
        return true;
    }
    else{
        return false;
    }
}

bool Gear::close() {
    if ((getAlarm() != ON) && (getState() != FERME)){
        switchState(FERME);
        return true;
    }
    else{
        return false;
    }
}

void Gear::putAlarm(){
    if (getAlarm() != ON) setAlarm(ON);
}

void Gear::disableAlarm() {
    if ((getAlarm() != OFF) && (getPanne() != true)) setAlarm(OFF);
}

void Gear::declarePanne(){
    putAlarm();
    setPanne(true);
}

void Gear::resolvedPanne(){
    setPanne(false);
    switchState(FERME);
}
