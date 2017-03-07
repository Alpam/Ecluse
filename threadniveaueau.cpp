#include "threadniveaueau.h"
#include <unistd.h>

ThreadNiveauEau::ThreadNiveauEau(int *ne, int n)
{
    num = n;
    niveauEau = ne;
}

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
