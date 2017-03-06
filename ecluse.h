#ifndef ECLUSE_H
#define ECLUSE_H

#include <QObject>
#include <QTimer>
#include <QWidget>

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
    void ouvrePorte(int num);
    void fermePorte(int num);
    void ouvreValve(int num);
    void fermeValve(int num);
    void putAlarm();
    void disableAlarm();
    void declarePanne();
    void resolvePanne();
    void update();
    ~Ecluse();

private:
    Ui::Ecluse *ui;
    bool unlocked;
    int niveauEcluse; //en pourcentage entre la hauteur de l'amont 100% et l'aval 0%
    bool alarmeGenerale;
    bool panneGenerale;
    //par convention l'indice 0 représente l'AMONT, l'indice 1 représente l'AVAL
    Porte *listePortes[2];
    Valve *listeValves[2];
    SignalLumineux *listeFeux[2];
    void setAlarm(bool a);
    void setPanne(bool a);
    void setUnLock(bool a);
    void timer_timeout(int num, char act);
};

#endif // ECLUSE_H
