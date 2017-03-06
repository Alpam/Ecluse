#include "signallumineux.h"

SignalLumineux::SignalLumineux()
{
    color = 'R';
}

void SignalLumineux::setGreen()
{
    if (color != 'V') color = 'V';
}

void SignalLumineux::setRed() {
    if (color != 'R') color = 'R';
}

char SignalLumineux::getColor() {
    return color;
}

