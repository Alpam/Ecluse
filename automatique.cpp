#include "automatique.h"
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
