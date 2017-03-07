#ifndef AUTOMATIQUE_H
#define AUTOMATIQUE_H

#include <QWidget>
#include "expert.h"
#include "ecluse.h"
#include "threadbarrepro.h"

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

private:
    Ui::Automatique *ui;
    ThreadBarrePro *tBP;

};

#endif // AUTOMATIQUE_H
