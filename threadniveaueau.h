#ifndef THREADNIVEAUEAU_H
#define THREADNIVEAUEAU_H

#include <QApplication>
#include <QThread>

class ThreadNiveauEau : public QThread
{
    Q_OBJECT
    public:
        ThreadNiveauEau(int *ne, int n);

    public slots :
        void run();

    signals :
        void finish();
        void timeToUpdate();

    private :
        int num;
        int *niveauEau;
};

#endif // THREADNIVEAUEAU_H
