#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QApplication>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT

    public:
        MyThread(int n, int a);

    public slots :
        void run();

    signals :
        void signalTerminal(int num, int act);

    public :
        int num;
        int act;
};

#endif
