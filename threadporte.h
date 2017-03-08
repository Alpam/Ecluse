#ifndef THREADPORTE_H
#define THREADPORTE_H

#include <QApplication>
#include <QThread>

class ThreadPorte : public QThread
{
    Q_OBJECT

    public:
        ThreadPorte(int n, int a);

    public slots :
        void run();

    signals :
        void signalTerminal(int num, int act);

    public :
        int num;
        int act;
};

#endif
