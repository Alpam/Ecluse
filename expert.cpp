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

void Expert::on_boutonStartAlarme_released()
{
    ecluse->putAlarm();
}

void Expert::on_boutonFeuAmont_released()
{
    ecluse->switchFeu(AMONT);
}

void Expert::on_boutonFeuAval_released()
{
    ecluse->switchFeu(AVAL);
}

void Expert::on_pAmOnOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->ouvrePorte(AMONT);
}

void Expert::on_pAvOnOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->ouvrePorte(AVAL);
}

void Expert::on_pAvOff_2_released()
{
    if (!ecluse->getAlarm())
        ecluse->fermePorte(AMONT);
}

void Expert::on_pAvOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->fermePorte(AVAL);
}

void Expert::on_boutonReparePorteAm_released()
{
    ecluse->resolvePanneP(AMONT);
}

void Expert::on_boutonReparePorteAv_released()
{
    ecluse->resolvePanneP(AMONT);
}

void Expert::on_boutonStopAlarme_released()
{
    ecluse->disableAlarm();
}

void Expert::on_vAvOn_released()
{
    if (!ecluse->getAlarm())
        ecluse->ouvreValve(AMONT);
}

void Expert::on_vAvOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->fermeValve(AMONT);
}

void Expert::on_vAmOn_released()
{
    if (!ecluse->getAlarm())
        ecluse->ouvreValve(AVAL);
}

void Expert::on_vAmOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->fermeValve(AVAL);
}

void Expert::on_boutonRepareValveAm_released()
{
    ecluse->resolvePanneV(AMONT);
}

void Expert::on_boutonRepareValveAv_released()
{
     ecluse->resolvePanneV(AVAL);
}
