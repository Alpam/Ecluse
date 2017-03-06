#include "porte.h"
#include "gear.h"
#include <string>
#include <iostream>

Porte::Porte()
    : Gear::Gear()
{}

void Porte::sendSignal(int signal, int num)
{
    switch(signal){
        case OUVERT : std::cout << "Ouvert Porte" << num;
                      break;
        case FERME  : std::cout << "Ferme Porte" << num;
                      break;
        default     : std::cout << "Stop Porte" << num;
    }
}
