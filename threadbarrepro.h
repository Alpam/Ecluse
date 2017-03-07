#ifndef THREADBARREPRO_H
#define THREADBARREPRO_H

#include <QApplication>
#include <QThread>

class ThreadBarrePro : public QThread
{
    Q_OBJECT
    public:
        ThreadBarrePro(int *nE);

    public slots:
        void run();

    signals :
        void fin();
        void timeToUpdate(int nE);

    private :
        int *niveauEcluse;
};

#endif // THREADBARREPRO_H
