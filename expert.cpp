#include "expert.h"
#include "ui_expert.h"

Expert::Expert(Ecluse *e) :
    QWidget(0),
    ui(new Ui::Expert)
{
    ui->setupUi(this);
    ecluse = e;
    tBP = new ThreadBarrePro(&e->niveauEcluse);
    tBP->start();
    connect(tBP, SIGNAL(fin()), this, SLOT(rien()));
    connect(tBP, SIGNAL(timeToUpdate(int)), this, SLOT(slotUpDate(int)));
}

Expert::~Expert()
{
    tBP->terminate();
    delete tBP;
    delete ui;
}


void Expert::on_boutonModeAuto_released()
{
    Automatique *w = new Automatique(ecluse);
    w->show();
    this->close();
}


void Expert::rien(){
    //ne fais rien
}

void Expert::slotUpDate(int nE){
    ui->barreNiveau->setValue(nE);
}
