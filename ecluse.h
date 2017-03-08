#ifndef ECLUSE_H
#define ECLUSE_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include "threadniveaueau.h"
#include "mythread.h"
#include "porte.h"
#include "valve.h"
#include "signallumineux.h"

namespace Ui {
class Ecluse;
}

class Ecluse : public QWidget
{
    Q_OBJECT

public:
    explicit Ecluse(QWidget *parent = 0);
    void update();
    void ouvrePorte(int num);
    void fermePorte(int num);
    void ouvreValve(int num);
    void fermeValve(int num);
    void putAlarm();
    void disableAlarm();
    void miseAlArret();
    void resolvePanneP(int num);
    void resolvePanneV(int num);
    bool porteOuvrable(int num);
    bool valveOuvrable();
    bool getAlarm();
    void switchFeu(int num);
    bool isOpen(int num);
    bool isClose(int num);
    int niveauEcluse; //en pourcentage entre la hauteur de l'amont 100% et l'aval 0%
    int addPorteAmont;
    int addPorteAval;
    ~Ecluse();

private:
    Ui::Ecluse *ui;
    bool unlocked;
    int nbrVavleOp;
    int nbrPorteOp;
    bool alarmeGenerale;
    //par convention l'indice 0 représente l'AMONT, l'indice 1 représente l'AVAL
    Porte *listePortes[2];
    Valve *listeValves[2];
    SignalLumineux *listeFeux[2];
    void setAlarm(bool a);
    QTimer *timer;
    MyThread *thread;
    ThreadNiveauEau *theau;

public slots :
        void valideAction(int num,int act);
        void finChangementNiveau();
        void timerAmont();
        void timerAval();
        void slotUpdate();
};

#endif // ECLUSE_H
