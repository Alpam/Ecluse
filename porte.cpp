#include "porte.h"
#include "gear.h"

Porte::Porte()
    : Gear::Gear()
{}

void Porte::sendSignal(int signal, int num)
{
    str
    switch(signal){
        case OUVERT : cout << "Ouvert Porte";
                      break;
        case FERME  : cout << "Ferme Porte";
                      break;
        default     : cout << "Stop Porte";
    }
}
