#include "mythread.h"

MyThread::MyThread(int n)
{
    num=n;
}

void MyThread::run()
{
    emit valueChanged(num);
}
