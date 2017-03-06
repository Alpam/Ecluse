#include "gear.h"

Gear::Gear()
{
    state = 0;
    alarm = false;
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

int Gear::getState() {
   return state;
}
