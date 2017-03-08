#include "threadattporte.h"

ThreadAttPorte::ThreadAttPorte( int *sP, int s)
{
    stateP = sP;
    state = s;
}

void ThreadAttPorte::run(){
    while(*stateP!=state){
        sleep(1);
    }
    emit finPorte();
}
