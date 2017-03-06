#include "expert.h"
#include "automatique.h"
#include "ui_expert.h"

Expert::Expert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Expert)
{
    ui->setupUi(this);
}

Expert::~Expert()
{
    delete ui;
}


void Expert::on_boutonModeAuto_released()
{
    Automatique *w = new Automatique;
    w->show();
    this->close();
}
