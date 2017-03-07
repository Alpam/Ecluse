#include "mythread.h"
#include <unistd.h>

MyThread::MyThread(int n, int a)
{
    num=n;
    act=a;
}

void MyThread::run()
{
    sleep(10);
    emit signalTerminal(num,act);
}
