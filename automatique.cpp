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
    ui->boutonFinPassage->setDisabled(true);
    tBP = new ThreadBarrePro(&e->niveauEcluse);
    tBP->start();
    connect(tBP, SIGNAL(fin()), this, SLOT(rien()));
    connect(tBP, SIGNAL(timeToUpdate(int)), this, SLOT(slotUpDate(int)));
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
    if (ui->radBouAmAv->isChecked()){
        depart=AMONT;
        ThreadAttNiveau thread = new ThreadAttNiveau(ecluse, 100, );
        connect(thread, SIGNAL(fin(int)), this, SLOT(signalFinStart(int)));
        }
    }
   /* if (ui->radBouAvAm->isChecked()){
        if (ecluse->niveauEcluse != 0) {
            ecluse->ouvreValve(AVAL);
            while(ecluse->niveauEcluse != 0) {
                sleep(1);
            }
            ecluse->ouvrePorte(AVAL);
        }
    }*/
}

void Automatique::on_radBouAmAv_clicked()
{
    ui->boutonStartPassage->setDisabled(false);
}

void Automatique::signalFinStart(int n){
    ui->boutonStartPassage->setDisabled(true);
    ui->boutonProgression->setDisabled(false);
}
