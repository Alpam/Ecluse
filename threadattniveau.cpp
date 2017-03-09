/*
 * =====================================================================================
 *
 *       Filename: threadattniveau.cpp
 *
 *    Description: chaque second ce thread regardera le niveau de l'eau, une foi le niveau
 *                 voulut atteint il s'arrête
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */


#include "threadattniveau.h"

/**
 * @brief ThreadAttNiveau::ThreadAttNiveau
 *        constructeur
 * @param nE
 *        addresse du niveau de l'eau de l'écluse
 * @param c
 *        niveau à atteindre
 */
ThreadAttNiveau::ThreadAttNiveau(int *nE, int c)
{
    niveauEau = nE;
    cst = c;
}

/**
 * @brief ThreadAttNiveau::run
 *        attend que le niveau soit le bon
 */
void ThreadAttNiveau::run(){
    while(*niveauEau!=cst){
        sleep(1);
    }
    emit finNiv();
}
