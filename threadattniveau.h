#ifndef THREADATTNIVEAU_H
#define THREADATTNIVEAU_H

#include <QApplication>
#include <QThread>

class ThreadAttNiveau : public QThread
{
    Q_OBJECT
public:
    ThreadAttNiveau(int *nE, int c);
public slots :
    void run();

signals :
    void finNiv();
private :

    int *niveauEau;
    int cst;
};

#endif // THREADATTNIVEAU_H
