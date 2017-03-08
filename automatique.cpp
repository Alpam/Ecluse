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
    th->terminate();
    delete th;
    thn->terminate();
    delete thn;
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
        depart = AMONT;
        if(!(ecluse->isClose(AVAL))){
            ecluse->fermePorte(AVAL);
        }
       th = new ThreadAttPorte(ecluse->addPorteAval,FERME);
       th->start();
       connect(th,SIGNAL(finPorte()),this,SLOT(secondStart()));
    }
    if (ui->radBouAvAm->isChecked()){
        depart = AVAL;
        if(!(ecluse->isClose(AMONT))){
            ecluse->fermePorte(AMONT);
        }
       th = new ThreadAttPorte(ecluse->addPorteAmont,FERME);
       th->start();
       connect(th,SIGNAL(finPorte()),this,SLOT(secondStart()));
    }
}

void Automatique::on_radBouAmAv_clicked()
{
    ui->boutonStartPassage->setDisabled(false);
}

void Automatique::secondStart(){
    th->terminate();
    delete th;
    if(depart==AMONT){
        ecluse->ouvreValve(AMONT);
        thn = new ThreadAttNiveau(&ecluse->niveauEcluse,100);
        thn->start();
        connect(thn,SIGNAL(finNiv()),this,SLOT(troisiemeStart()));
    }
    else{
        ecluse->ouvreValve(AVAL);
        thn = new ThreadAttNiveau(&ecluse->niveauEcluse,0);
        thn->start();
        connect(thn,SIGNAL(finNiv()),this,SLOT(troisiemeStart()));
    }
}

void Automatique::troisiemeStart(){
    thn->terminate();
    delete thn;
    if(depart==AMONT){
        ecluse->fermeValve(AMONT);
        ecluse->ouvrePorte(AMONT);
        th = new ThreadAttPorte(ecluse->addPorteAmont, OUVRE);
        th->start();
        connect(th,SIGNAL(finPorte()),this,SLOT(finStart()));
    }
    else{
        ecluse->fermeValve(AVAL);
        ecluse->ouvrePorte(AVAL);
        th = new ThreadAttPorte(ecluse->addPorteAval,OUVRE);
        th->start();
        connect(th,SIGNAL(finPorte()),this,SLOT(finStart()));
    }
}

void Automatique::finStart(){
    th->terminate();
    delete th;
    if(depart==AMONT){
        feuAm = true;
    }
    else{
        feuAv = true;
    }
    ui->boutonStartPassage->setDisabled(true);
    ui->boutonProgression->setDisabled(false);
}
