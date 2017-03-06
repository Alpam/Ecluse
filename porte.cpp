#include "porte.h"
#include "gear.h"
#include <iostream>

Porte::Porte()
    : Gear::Gear()
{}

void Porte::sendSignal(int signal, int num)
{
    switch(signal){
        case OUVRE : std::cout << "Ouvre Porte" << num;
                      break;
        case FERME  : std::cout << "Ferme Porte" << num;
                      break;
        case STOP   : std::cout << "Stop Porte" << num;
                      break;
    }

}

void Porte::ask_open() {
    if (getAlarm() != ON) switchState(EN_OUVERTURE);
}

void Porte::ask_close() {
    if (getAlarm() != ON) switchState(EN_FERMETURE);
}

