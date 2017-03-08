#include "threadattniveau.h"
#include <unistd.h>

ThreadAttNiveau::ThreadAttNiveau(Ecluse *e, int nA, int n)
{
    nivAtt = nA;
    ecluse = e;
    num = n;
}

void ThreadAttNiveau::run()
{
    ecluse->fermeValve(AMONT);
    ecluse->fermeValve(AVAL);
    if(ecluse->niveauEcluse!=nivAtt){
        ecluse->fermePorte(num==AMONT?AVAL:AMONT);
        while(!(ecluse->isClose(num==AMONT?AVAL:AMONT))){
            sleep(1);
        }
        ecluse->ouvreValve(num);
        while(ecluse->niveauEcluse!=nivAtt){
            sleep(1);
        }
        ecluse->fermeValve(num);
    }
    ecluse->ouvrePorte(num);
    while(!(ecluse->isOpen(num))){
        sleep(1);
    }
    emit fin(num);
}
