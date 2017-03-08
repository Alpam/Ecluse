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


#include "threadattniveau.h"

ThreadAttNiveau::ThreadAttNiveau(int *nE, int c)
{
    niveauEau = nE;
    cst = c;
}

void ThreadAttNiveau::run(){
    while(*niveauEau!=cst){
        sleep(1);
    }
    emit finNiv();
}
