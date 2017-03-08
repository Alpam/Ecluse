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

#ifndef VALVE_H
#define VALVE_H

#include "gear.h"


class Valve : public Gear
{
public:
    Valve();
    void sendSignal(int signal, int num);
};

#endif // VALVE_H
