#ifndef THREADATTPORTE_H
#define THREADATTPORTE_H

#include <QApplication>
#include <QThread>

class ThreadAttPorte : public QThread
{
    Q_OBJECT
    public:
        ThreadAttPorte(int *sP, int s);

    public slots:
        void run();

    signals :
        void finPorte();

    private :
        int *stateP;
        int state;
    };

#endif // THREADATTPORTE_H
