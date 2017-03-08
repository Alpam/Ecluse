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

#ifndef SIGNALLUMINEUX_H
#define SIGNALLUMINEUX_H

#include "gear.h"
#include <iostream>

class SignalLumineux
{
public:
    SignalLumineux();
    void sendSignal(char signal, int num);
    void setGreen();
    void setRed();
    char getColor();

private:
    char color;
};

#endif // SIGNALLUMINEUX_H
