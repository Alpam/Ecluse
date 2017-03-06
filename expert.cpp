#include "expert.h"
#include "ui_expert.h"

Expert::Expert(Ecluse *e) :
    QWidget(0),
    ui(new Ui::Expert)
{
    ui->setupUi(this);
    ecluse = e;
}

Expert::~Expert()
{
    delete ui;
}


void Expert::on_boutonModeAuto_released()
{
    Automatique *w = new Automatique(ecluse);
    w->show();
    this->close();
}
