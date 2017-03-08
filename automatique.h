#ifndef AUTOMATIQUE_H
#define AUTOMATIQUE_H

#include <QWidget>
#include "expert.h"
#include "ecluse.h"
#include "threadbarrepro.h"
#include "threadattporte.h"
#include "threadattniveau.h"

namespace Ui {
class Automatique;
}

class Automatique : public QWidget
{
    Q_OBJECT

public:
    Automatique(Ecluse *e);
    ~Automatique();
    Ecluse *ecluse;

private slots:
    void on_boutonModeExp_released();
    void rien();
    void slotUpDate(int nE);

    void on_startAlarme_released();

    void on_boutonStartPassage_released();

    void on_radBouAmAv_clicked();

public slots :
    void secondStart();
    void troisiemeStart();
    void finStart();

private:
    Ui::Automatique *ui;
    ThreadBarrePro *tBP;
    ThreadAttPorte *th;
    ThreadAttNiveau *thn;
    int depart;
    bool feuAm;
    bool feuAv;


};

#endif // AUTOMATIQUE_H
