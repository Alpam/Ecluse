/*
 * =====================================================================================
 *
 *       Filename: threadbarrepro.cpp
 *
 *    Description: ce thread met la barre de progression du niveau de l'eau à jour toutes
 *                 les secondes
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "threadbarrepro.h"
#include <unistd.h>

/**
 * @brief ThreadBarrePro::ThreadBarrePro
 *        constructeur
 * @param nE
 *        adresse du niveau de l'eau
 */
ThreadBarrePro::ThreadBarrePro(int *nE)
{
    niveauEcluse = nE;
}

/**
 * @brief ThreadBarrePro::run
 *        attente une seconde puis met le niveau à jour
 */
void ThreadBarrePro::run(){
    while(1){
        sleep(1);
        emit timeToUpdate(*niveauEcluse);
    }
    emit fin();
}

