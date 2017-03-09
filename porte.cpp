/*
 * =====================================================================================
 *
 *       Filename: porte.cpp
 *
 *    Description: représente une porte de l'écluse, hérite de gear
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "porte.h"
#include "gear.h"
#include <iostream>

/**
 * @brief Porte::Porte
 *        constructeur
 */
Porte::Porte()
    : Gear::Gear()
{}

/**
 * @brief Porte::ask_open
 *        regarde si il est possible de commencer à ouvrir une porte
 *        si oui la met EN_OUVERTURE
 * @return
 *        si possible renvoie vrai sinon faux
 */
bool Porte::ask_open() {
    if ((getAlarm() != ON) && ((getState() == FERME)||(getState() == EN_ARRET))) {
        switchState(EN_OUVERTURE);
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief Porte::ask_close
 *        regarde si il est possible de commencer à fermer une porte
 *        si oui la met EN_FERMETURE
 * @return
 *        si possible renvoie vrai sinon faux
 */
bool Porte::ask_close() {
    if ((getAlarm() != ON) && ((getState() == OUVRE)||(getState() == EN_ARRET))){
        switchState(EN_FERMETURE);
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief Porte::arret
 *        met une porte en arret
 */
void Porte::arret(){
    switchState(EN_ARRET);
}

