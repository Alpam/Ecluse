/*
 * =====================================================================================
 *
 *       Filename: gear.cpp
 *
 *    Description: classe abstraite représentant les méchanismes de l'écluse : porte, valve
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "gear.h"

/**
 * @brief Gear::Gear
 *        constructeur
 */
Gear::Gear()
{
    state = FERME;
    alarm = OFF;
    panne = false;
}

/**
 * @brief Gear::~Gear
 *        destructeur
 */
Gear::~Gear()
{

}

/**
 * @brief Gear::switchState
 *        change l'état
 * @param newState
 *        le nouvelle état
 */
void Gear::switchState(int newState) {
   state = newState;
}

/**
 * @brief Gear::getAlarm
 * @return
 *        retourne si en alarme
 */
bool Gear::getAlarm() {
   return alarm;
}

/**
 * @brief Gear::getPanne
 * @return
 *        retourne si en panne
 */
bool Gear::getPanne() {
   return panne;
}

/**
 * @brief Gear::getState
 * @return
 *        retourne l'état
 */
int Gear::getState() {
   return state;
}

/**
 * @brief Gear::setAlarm
 *        change l'alarme
 * @param a
 *        nouvelle alarme
 */
void Gear::setAlarm(bool a) {
    alarm = a;
}

/**
 * @brief Gear::setPanne
 *        set une panne
 * @param a
 *        nouvelle panne
 */
void Gear::setPanne(bool a) {
    panne = a;
    if(a) setAlarm(ON);
}

/**
 * @brief Gear::open
 *        si possible ouvre
 * @return
 *        si possible renvoie vrai, sinon faux
 */
bool Gear::open() {
    if((getAlarm() != ON) && (getState() != OUVRE)){
        switchState(OUVRE);
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief Gear::close
 *        si possible ferme
 * @return
 *        si possible renvoie vraie, sinon faux
 */
bool Gear::close() {
    if ((getAlarm() != ON) && (getState() != FERME)){
        switchState(FERME);
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief Gear::putAlarm
 */
void Gear::putAlarm(){
    if (getAlarm() != ON) setAlarm(ON);
}

/**
 * @brief Gear::disableAlarm
 */
void Gear::disableAlarm() {
    if ((getAlarm() != OFF) && (getPanne() != true)) setAlarm(OFF);
}

/**
 * @brief Gear::declarePanne
 */
void Gear::declarePanne(){
    putAlarm();
    setPanne(true);
}

/**
 * @brief Gear::resolvedPanne
 *        met fin à une panne, et ferme
 */
void Gear::resolvedPanne(){
    setPanne(false);
    switchState(FERME);
}

/**
 * @brief Gear::arret
 *        met dans l'état arret
 */
void Gear::arret(){
    switchState(EN_ARRET);
}
