#include "automatique.h"
#include "expert.h"
#include "ui_automatique.h"

Automatique::Automatique(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Automatique)
{
    ui->setupUi(this);
}

Automatique::~Automatique()
{
    delete ui;
}

void Automatique::on_boutonModeExp_released()
{
    Expert *w = new Expert;
    w->show();
    this->close();
}
