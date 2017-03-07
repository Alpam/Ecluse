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

