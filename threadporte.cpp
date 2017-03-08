#include "threadporte.h"
#include <unistd.h>

ThreadPorte::ThreadPorte(int n, int a)
{
    num=n;
    act=a;
}

void ThreadPorte::run()
{
    sleep(10);
    emit signalTerminal(num,act);
}
