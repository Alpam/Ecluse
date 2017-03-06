#include "signallumineux.h"

SignalLumineux::SignalLumineux()
{
    color = 'R';
}
void SignalLumineux::sendSignal(char signal, int num) {
    switch(signal) {
        case 'R' : cout << "Signal Rouge";
            break;
        case 'V'  : cout << "Signal Vert";
            break;
    }
}

void SignalLumineux::setGreen() {
    if (color != 'V') color = 'V';
}

void SignalLumineux::setRed() {
    if (color != 'R') color = 'R';
}

char SignalLumineux::getColor() {
    return color;
}

