#ifndef AUTOMATIQUE_H
#define AUTOMATIQUE_H

#include <QWidget>
#include "expert.h"
#include "ecluse.h"

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

private:
    Ui::Automatique *ui;
};

#endif // AUTOMATIQUE_H
