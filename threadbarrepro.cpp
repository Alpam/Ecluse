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

#include "threadbarrepro.h"
#include <unistd.h>

ThreadBarrePro::ThreadBarrePro(int *nE)
{
    niveauEcluse = nE;
}

void ThreadBarrePro::run(){
    while(1){
        sleep(1);
        emit timeToUpdate(*niveauEcluse);
    }
    emit fin();
}

