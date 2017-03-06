#ifndef EXPERT_H
#define EXPERT_H

#include <QWidget>
#include "automatique.h"
#include "ecluse.h"

namespace Ui {
class Expert;
}

class Expert : public QWidget
{
    Q_OBJECT

public:
    Expert(Ecluse *e);
    ~Expert();
    Ecluse *ecluse;

private slots:
    void on_boutonModeAuto_released();

private:
    Ui::Expert *ui;
};

#endif // EXPERT_H
