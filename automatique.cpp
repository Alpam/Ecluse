#include "automatique.h"
#include "ui_automatique.h"
#include <unistd.h>

#include <QInputDialog>


Automatique::Automatique(Ecluse *e) :
    QWidget(0),
    ui(new Ui::Automatique)
{
    ui->setupUi(this);
    ecluse = e;
    ui->barreNiveau->setValue(0);
    ui->boutonFinPassage->setDisabled(true);
    ui->boutonStartPassage->setDisabled(true);
    ui->boutonProgression->setDisabled(true);
    tBP = new ThreadBarrePro(&e->niveauEcluse);
    tBP->start();
    connect(tBP, SIGNAL(fin()), this, SLOT(rien()));
    connect(tBP, SIGNAL(timeToUpdate(int)), this, SLOT(slotUpDate(int)));
    bool feuAm=false;
    bool feuAv=false;
}

Automatique::~Automatique()
{
    tBP->terminate();
    delete tBP;
    delete ui;
}

void Automatique::on_boutonModeExp_released()
{
    QString txt = QInputDialog::getText(this,"Password ?","Mot de passe ?",QLineEdit::Password);
        if(txt == "password"){
            Expert *w = new Expert(ecluse);
            w->show();
            this->close();
        }
}

void Automatique::rien(){
    //ne fais rien
}

void Automatique::slotUpDate(int nE){
    ui->barreNiveau->setValue(nE);
}

void Automatique::on_startAlarme_released()
{
    ecluse->putAlarm();
}

void Automatique::on_boutonStartPassage_released()
{
    feuAm = false;
    feuAv = false;
    ecluse->fermeValve(AMONT);
    ecluse->fermeValve(AVAL);
    if (ui->radBouAmAv->isChecked()){
        if(!(ecluse->isClose(AVAL))){
            ecluse->fermePorte(AVAL);
        }
       // ThreadAttPort th = new ThreadAttPort(AVAL,);
    }
    if (ui->radBouAvAm->isChecked()){
    }
}

void Automatique::on_radBouAmAv_clicked()
{
    ui->boutonStartPassage->setDisabled(false);
}

void Automatique::signalFinStart(){
    depart==AMONT?feuAm=true:feuAv=true;
    ui->boutonStartPassage->setDisabled(true);
    ui->boutonProgression->setDisabled(false);
}
