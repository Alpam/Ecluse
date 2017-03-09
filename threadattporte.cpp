/*
 * =====================================================================================
 *
 *       Filename: threadattporte.cpp
 *
 *    Description: ce thread attend qu'une porte soit dans l'état voulu puis se termine
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "threadattporte.h"

/**
 * @brief ThreadAttPorte::ThreadAttPorte
 *        constructeur
 * @param sP
 *        adresse de l'état de la porte
 * @param s
 *        état à atteindre
 */
ThreadAttPorte::ThreadAttPorte( int *sP, int s)
{
    stateP = sP;
    state = s;
}

/**
 * @brief ThreadAttPorte::run
 *        attent que l'état de la porte soit le bon
 */
void ThreadAttPorte::run(){
    while(*stateP!=state){
        sleep(1);
    }
    emit finPorte();
}
