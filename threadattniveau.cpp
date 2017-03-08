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
