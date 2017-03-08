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
    ecluse->feuxSetRed();
    connect(tBP, SIGNAL(fin()), this, SLOT(rien()));
    connect(tBP, SIGNAL(timeToUpdate(int)), this, SLOT(slotUpDate(int)));

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

void Automatique::on_radBouAmAv_clicked()
{
    ui->boutonStartPassage->setDisabled(false);
}

void Automatique::on_radBouAvAm_clicked()
{
    ui->boutonStartPassage->setDisabled(false);
}


void Automatique::on_boutonStartPassage_released()
{
    ecluse->feuxSetRed();
    ui->radBouAmAv->setDisabled(true);
    ui->radBouAvAm->setDisabled(true);
    ecluse->fermeValve(AMONT);
    ecluse->fermeValve(AVAL);
    if (ui->radBouAmAv->isChecked()){
        ecluse->pos = BAMONT;
        depart = AMONT;
        if(!(ecluse->isClose(AVAL))){
            ecluse->fermePorte(AVAL);
        }
       th = new ThreadAttPorte(ecluse->addPorteAval,FERME);
       th->start();
       connect(th,SIGNAL(finPorte()),this,SLOT(secondStart()));
    }
    if (ui->radBouAvAm->isChecked()){
        ecluse->pos = BAVAL;
        depart = AVAL;
        if(!(ecluse->isClose(AMONT))){
            ecluse->fermePorte(AMONT);
        }
       th = new ThreadAttPorte(ecluse->addPorteAmont,FERME);
       th->start();
       connect(th,SIGNAL(finPorte()),this,SLOT(secondStart()));
    }
}

void Automatique::secondStart(){
    th->terminate();
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
    if(depart==AMONT){
        ecluse->switchFeu(AMONT);
        ecluse->pos = BECAMONT;
    }
    else{
        ecluse->switchFeu(AVAL);
        ecluse->pos = BECAVAL;
    }
    ui->boutonStartPassage->setDisabled(true);
    ui->boutonProgression->setDisabled(false);
    th->terminate();
    thn->terminate();
}

void Automatique::on_boutonProgression_released()
{
    if(depart==AMONT){
        ecluse->switchFeu(AMONT);
        ecluse->fermePorte(AMONT);
        th = new ThreadAttPorte(ecluse->addPorteAmont, FERME);
        th->start();
        connect(th,SIGNAL(finPorte()),this,SLOT(secondProgression()));
    }
    else{
        ecluse->switchFeu(AVAL);
        ecluse->fermePorte(AVAL);
        th = new ThreadAttPorte(ecluse->addPorteAval, FERME);
        th->start();
        connect(th,SIGNAL(finPorte()),this,SLOT(secondProgression()));

    }
}

void Automatique::secondProgression(){
    th->terminate();
    if(depart==AMONT){
        ecluse->ouvreValve(AVAL);
        thn = new ThreadAttNiveau(&ecluse->niveauEcluse,0);
        thn->start();
        connect(thn,SIGNAL(finNiv()),this,SLOT(troisiemeProgression()));
    }
    else{
        ecluse->ouvreValve(AMONT);
        thn = new ThreadAttNiveau(&ecluse->niveauEcluse,100);
        thn->start();
        connect(thn,SIGNAL(finNiv()),this,SLOT(troisiemeProgression()));
    }
}

void Automatique::troisiemeProgression(){
    thn->terminate();
    if(depart==AMONT){
        ecluse->fermeValve(AVAL);
        ecluse->pos = BECAVAL;
        ecluse->ouvrePorte(AVAL);
        th = new ThreadAttPorte(ecluse->addPorteAval, OUVRE);
        th->start();
        connect(th,SIGNAL(finPorte()),this,SLOT(finProgression()));
    }
    else{
        ecluse->fermeValve(AMONT);
        ecluse->pos = BECAMONT;
        ecluse->ouvrePorte(AMONT);
        th = new ThreadAttPorte(ecluse->addPorteAmont, OUVRE);
        th->start();
        connect(th,SIGNAL(finPorte()),this,SLOT(finProgression()));
    }
}

void Automatique::finProgression(){
    th->terminate();
    if(depart==AMONT){
        ecluse->switchFeu(AVAL);
    }
    else{
        ecluse->switchFeu(AMONT);
    }
    ui->boutonProgression->setDisabled(true);
    ui->boutonFinPassage->setDisabled(false);
}

void Automatique::on_boutonFinPassage_released()
{
    if(depart==AMONT){
        ecluse->pos = BAVAL;
        ecluse->switchFeu(AVAL);
        //ecluse->fermePorte(AVAL);
    }
    else{
        ecluse->pos = BAMONT;
        ecluse->switchFeu(AMONT);
        //ecluse->fermePorte(AMONT);
    }
    ecluse->feuxSetRed();
    ui->boutonStartPassage->setDisabled(true);
    ui->boutonFinPassage->setDisabled(true);
    ui->radBouAmAv->setAutoExclusive(false);
    ui->radBouAvAm->setAutoExclusive(false);
    ui->radBouAmAv->setChecked(false);
    ui->radBouAvAm->setChecked(false);
    ui->radBouAmAv->setAutoExclusive(true);
    ui->radBouAvAm->setAutoExclusive(true);
    ui->radBouAmAv->setDisabled(false);
    ui->radBouAvAm->setDisabled(false);
}
