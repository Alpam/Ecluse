/*
 * =====================================================================================
 *
 *       Filename: threadporte.cpp
 *
 *    Description: ce thread effectue l'action voulue pour une porte en 10 secondes et
 *                 émet un signal à la fin de l'action
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "threadporte.h"
#include <unistd.h>

/**
 * @brief ThreadPorte::ThreadPorte
 *        constructeur
 * @param n
 *        porte à actionner
 * @param a
 *        action à effectuer
 */
ThreadPorte::ThreadPorte(int n, int a)
{
    num=n;
    act=a;
}

/**
 * @brief ThreadPorte::run
 *        attend 10 seconde
 */
void ThreadPorte::run()
{
    sleep(10);
    emit signalTerminal(num,act);
}
