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

#include "porte.h"
#include "gear.h"
#include <iostream>

Porte::Porte()
    : Gear::Gear()
{}

bool Porte::ask_open() {
    if ((getAlarm() != ON) && ((getState() == FERME)||(getState() == EN_ARRET))) {
        switchState(EN_OUVERTURE);
        return true;
    }
    else{
        return false;
    }
}

bool Porte::ask_close() {
    if ((getAlarm() != ON) && ((getState() == OUVRE)||(getState() == EN_ARRET))){
        switchState(EN_FERMETURE);
        return true;
    }
    else{
        return false;
    }
}

void Porte::arret(){
    switchState(EN_ARRET);
}

