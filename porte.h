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

#ifndef PORTE_H
#define PORTE_H

#include "gear.h"

class Porte : public Gear
{
public:
    Porte();
    bool ask_open();
    bool ask_close();
    void arret();
};

#endif // PORTE_H
