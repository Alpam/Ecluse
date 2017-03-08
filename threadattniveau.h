#ifndef THREADATTNIVEAU_H
#define THREADATTNIVEAU_H

#include <QApplication>
#include <QThread>
#include "ecluse.h"

class ThreadAttNiveau : public QThread
{
    Q_OBJECT
    public:
        ThreadAttNiveau(Ecluse *e, int nA, int n);

    public slots :
        void run();

    signals :
        void fin();


    private :
        Ecluse *ecluse;
        int nivAtt;
        int num;
};

#endif // THREADATTNIVEAU_H
