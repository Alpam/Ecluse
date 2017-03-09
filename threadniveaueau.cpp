/*
 * =====================================================================================
 *
 *       Filename: threadniveaueau.cpp
 *
 *    Description: ce thread change le niveau d'eau
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "threadniveaueau.h"
#include <unistd.h>

/**
 * @brief ThreadNiveauEau::ThreadNiveauEau
 *        constructeur
 * @param ne
 *        adresse du niveau de l'eau
 * @param n
 *        la valve ouverte
 */
ThreadNiveauEau::ThreadNiveauEau(int *ne, int n)
{
    num = n;
    niveauEau = ne;
}

/**
 * @brief ThreadNiveauEau::run
 *        change le niveau de l'eau et met la représentaion de l'écluse à jour
 */
void ThreadNiveauEau::run()
{
    if(!(num)){//valve amont est ouverte
        while(*niveauEau<100){
            *niveauEau=*niveauEau+10;
            sleep(2);
            emit timeToUpdate();
        }
    }
    else{//valve aval est ouverte
        while(*niveauEau>0){
            *niveauEau=*niveauEau-10;
            sleep(2);
            emit timeToUpdate();
        }
    }
    emit finish();
}
