/*
 * =====================================================================================
 *
 *       Filename:
 *
 *    Description:
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

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

