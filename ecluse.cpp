#include "ecluse.h"
#include "threadniveaueau.h"
#include "mythread.h"
#include "ui_ecluse.h"
#include <unistd.h>
#include <iostream>

Ecluse::Ecluse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ecluse)
{
    ui->setupUi(this);
    listePortes[0]=new Porte;
    listePortes[1]=new Porte;
    listeValves[0]=new Valve;
    listeValves[1]=new Valve;
    listeFeux[0]=new SignalLumineux;
    listeFeux[1]=new SignalLumineux;
    ui->bateauAm->setVisible(true);
    ui->bateauAv->setVisible(false);
    ui->bateauEcAm->setVisible(false);
    ui->bateauEcMid->setVisible(false);
    ui->bateauEcAv->setVisible(false);
    nbrVavleOp = 0;
    nbrPorteOp = 0;
    niveauEcluse = 0;
    alarmeGenerale = OFF;
    addPorteAmont = &listePortes[0]->state;
    addPorteAval = &listePortes[1]->state;
    theau=NULL;
}

Ecluse::~Ecluse()
{
    delete ui;
}

void Ecluse::update()
{
    QString etatPorteAval, etatPorteAmont, etatValveAval, etatValveAmont,
            alarmePorteAval, alarmePorteAmont, alarmeValveAval, alarmeValveAmont,
            pannePorteAval, pannePorteAmont, alarmeG, panneValveAval, panneValveAmont;
    switch (listePortes[AMONT]->getState()) {
        case OUVRE : etatPorteAmont = "Ouverte"; ui->porteAmFct->setVisible(false);
            break;
        case EN_OUVERTURE : etatPorteAmont = "Ouverture"; ui->porteAmFct->setVisible(true);ui->porteAm->setVisible(false);
            break;
        case FERME : etatPorteAmont = "Fermee"; ui->porteAmFct->setVisible(false);ui->porteAm->setVisible(true);
            break;
        case EN_FERMETURE : etatPorteAmont = "Fermeture"; ui->porteAmFct->setVisible(true);ui->porteAm->setVisible(false);
            break;
        case EN_ARRET : etatPorteAmont = "Arretee";
            break;
    }
    switch (listePortes[AVAL]->getState()) {
        case OUVRE : etatPorteAval = "Ouverte"; ui->porteAvFct->setVisible(false);
            break;
        case EN_OUVERTURE : etatPorteAval = "Ouverture"; ui->porteAvFct->setVisible(true);ui->porteAv->setVisible(false);
            break;
        case FERME : etatPorteAval = "Fermee"; ui->porteAvFct->setVisible(false);ui->porteAv->setVisible(true);
            break;
        case EN_FERMETURE : etatPorteAval = "Fermeture"; ui->porteAvFct->setVisible(true);ui->porteAv->setVisible(false);
            break;
        case EN_ARRET : etatPorteAval = "Arretee";
            break;
    }
    switch (listeValves[AVAL]->getState()) {
        case OUVRE : etatValveAval = "Ouverte"; ui->valveAvOp->setVisible(true);ui->valveAv->setVisible(false);
            break;
        case FERME : etatValveAval = "Fermee"; ui->valveAvOp->setVisible(false);ui->valveAv->setVisible(true);
            break;
    }
    switch (listeValves[AMONT]->getState()) {
        case OUVRE : etatValveAmont = "Ouverte"; ui->valveAmOp->setVisible(true);ui->valveAm->setVisible(false);
            break;
        case FERME : etatValveAmont = "Fermee"; ui->valveAmOp->setVisible(false);ui->valveAm->setVisible(true);
            break;
    }

    switch (niveauEcluse) {
        case 100 : ui->eauEcAm->setVisible(true);
            if (ui->bateauAm->isVisible() || ui->bateauAv->isVisible()) {
                ui->bateauEcMid->setVisible(false);
                ui->bateauEcAm->setVisible(false);
                ui->bateauEcAv->setVisible(false);
            } else {
                ui->bateauEcAm->setVisible(false);
            }
            break;
        case 50 : ui->eauEcAm->setVisible(false); ui->eauEcMid->setVisible(true);
            if (ui->bateauAm->isVisible() || ui->bateauAv->isVisible()) {
                ui->bateauEcMid->setVisible(false);
                ui->bateauEcAm->setVisible(false);
                ui->bateauEcAv->setVisible(false);
            } else {
                ui->bateauEcMid->setVisible(true);
            }
            break;
        case 0 : ; ui->eauEcAm->setVisible(false); ui->eauEcMid->setVisible(false);
            if (ui->bateauAm->isVisible() || ui->bateauAv->isVisible()) {
                ui->bateauEcMid->setVisible(false);
                ui->bateauEcAm->setVisible(false);
                ui->bateauEcAv->setVisible(false);
            } else {
                ui->bateauEcAv->setVisible(true);
            }
            break;
    }
    if (listePortes[AVAL]->getPanne()) {
        pannePorteAval = "En Panne";ui->porteAvP->setVisible(true);
    } else {
        pannePorteAval = "Fonctionnel";ui->porteAvP->setVisible(false);
    } if (listePortes[AMONT]->getPanne()) {
        pannePorteAmont = "En Panne";ui->porteAmP->setVisible(true);
    } else {
        pannePorteAmont = "Fonctionnel";ui->porteAmP->setVisible(false);
    } if (listeValves[AVAL]->getPanne()) {
        panneValveAval = "En Panne";ui->valveAvP->setVisible(true);
    } else {
        panneValveAval = "Fonctionnel";ui->valveAvP->setVisible(false);
    } if (listeValves[AMONT]->getPanne()) {
        panneValveAmont = "En Panne";ui->valveAmP->setVisible(true);
    } else {
        panneValveAmont = "Fonctionnel";ui->valveAmP->setVisible(false);
    } if (listePortes[AVAL]->getAlarm()) {
        alarmePorteAval = "En Alarme";ui->porteAvA->setVisible(true);
    } else {
        alarmePorteAval = "Pas en Alarme";ui->porteAvA->setVisible(false);
    } if (listePortes[AMONT]->getAlarm()) {
        alarmePorteAmont = "En Alarme";ui->porteAmA->setVisible(true);
    } else {
        alarmePorteAmont = "Pas en Alarme";ui->porteAmA->setVisible(false);
    } if (listeValves[AVAL]->getAlarm()) {
        alarmeValveAval = "En Alarme";ui->valveAvA->setVisible(true);
    } else {
        alarmeValveAval = "Pas en Alarme";ui->valveAvA->setVisible(false);
    } if (listeValves[AMONT]->getAlarm()) {
        alarmeValveAmont = "En Alarme";ui->valveAmA->setVisible(true);
    } else {
        alarmeValveAmont = "Pas en Alarme";ui->valveAmA->setVisible(false);
    }
    if (alarmeGenerale) {
        alarmeG = "\tECLUSE EN ALARME\n";
        ui->alarmGen->setVisible(true);
    } else {
        ui->alarmGen->setVisible(false);
    }
    if (listeFeux[AVAL]->getColor() == 'R') {
        ui->feuAvR->setVisible(true);
        ui->feuAvV->setVisible(false);
    } else {
        ui->feuAvR->setVisible(false);
        ui->feuAvV->setVisible(true);
    }
    if (listeFeux[AMONT]->getColor() == 'R') {
        ui->feuAmR->setVisible(true);
        ui->feuAmV->setVisible(false);
    } else {
        ui->feuAmR->setVisible(false);
        ui->feuAmV->setVisible(true);
    }

    QString nE = QString::number(niveauEcluse);
    ui->etat->setText(alarmeG + "PORTE AMONT\n\tEtat : " + etatPorteAmont + "\n\t" + alarmePorteAmont + "\n\t" + pannePorteAmont
                      + "\n\nPORTE AVAL\n\tEtat : " + etatPorteAval + "\n\t" + alarmePorteAval + "\n\t" + pannePorteAval
                      + "\n\nVALVE AMONT\n\tEtat : " + etatValveAmont + "\n\t" + alarmeValveAmont + "\n\t" + panneValveAmont
                      + "\n\nVALVE AVAL\n\tEtat : " + etatValveAval + "\n\t" + alarmeValveAval + "\n\t" + panneValveAval
                      + "\n\nSIGNAL LUMINEUX AVAL\t" + listeFeux[AVAL]->getColor()
                      + "\n\nSIGNAL LUMINEUX AMONT\t" + listeFeux[AMONT]->getColor()
                      + "\n\nNIVEAU EAU\t" + nE);
}

void Ecluse::ouvrePorte(int num){
    if(porteOuvrable(num)){
        if(!(listePortes[num]->ask_open())){
            //ça plante
            return;
        }
        nbrPorteOp++;
        update();
        thread = new MyThread(num,EN_OUVERTURE);
        thread->start();
        timer = new QTimer();
        if(num==AMONT){
            connect(timer, SIGNAL(timeout()), this, SLOT(timerAmont()));
        }
        else{
            connect(timer, SIGNAL(timeout()), this, SLOT(timerAval()));
        }
        connect(thread, SIGNAL(signalTerminal(int,int)), this,SLOT(valideAction(int,int)));
        timer->start(12000);
    }
}

void Ecluse::fermePorte(int num){
    if(!(listePortes[num]->ask_close())){
        //ça plante
        return;
    }
    update();
    thread = new MyThread(num,EN_FERMETURE);
    thread->start();
    timer = new QTimer();
    if(num==AMONT){
        connect(timer, SIGNAL(timeout()), this, SLOT(timerAmont()));
    }
    else{
        connect(timer, SIGNAL(timeout()), this, SLOT(timerAval()));
    }
    connect(thread, SIGNAL(signalTerminal(int,int)), this,SLOT(valideAction(int,int)));
    timer->start(12000);
}

void Ecluse::ouvreValve(int num){
    if(valveOuvrable()){
    if(listeValves[num]->open()){
        nbrVavleOp++;
        update();
        if(nbrVavleOp==2){
            if(theau!=NULL){
                theau->terminate();
               // delete theau;
                theau=NULL;
            }
            niveauEcluse = 50;
            update();
        }
        else{
            theau = new ThreadNiveauEau(&niveauEcluse, num);
            theau->start();
            connect(theau, SIGNAL(finish()), this,SLOT(finChangementNiveau()));
            connect(theau, SIGNAL(timeToUpdate()), this, SLOT(slotUpdate()));
        }
    }
    else{
        //popupmarche pas
    }
    }
}

void Ecluse::fermeValve(int num){
    if(listeValves[num]->close()){
        update();
        if(theau!=NULL){
            theau->terminate();
            delete theau;
            theau=NULL;
        }
        nbrVavleOp--;
        if(nbrVavleOp==1){
            int tmp;
            num==AMONT?tmp=AVAL:tmp=AMONT;
            theau = new ThreadNiveauEau(&niveauEcluse, tmp);
            theau->start();
            connect(theau, SIGNAL(finish()), this,SLOT(finChangementNiveau()));
            connect(theau, SIGNAL(timeToUpdate()), this, SLOT(slotUpdate()));
        }
    }
    else{
        //popupmarche pas
    }
}

void Ecluse::putAlarm() {
    listePortes[AVAL]->putAlarm();
    listePortes[AMONT]->putAlarm();
    listeValves[AVAL]->putAlarm();
    listeValves[AMONT]->putAlarm();
    fermeValve(AVAL);
    fermeValve(AMONT);
    miseAlArret();
    setAlarm(true);
    update();
}

void Ecluse::disableAlarm(){
    listePortes[AVAL]->disableAlarm();
    listePortes[AMONT]->disableAlarm();
    listeValves[AVAL]->disableAlarm();
    listeValves[AMONT]->disableAlarm();
    setAlarm(false);
    update();
}

void Ecluse::miseAlArret(){
    for(int i=0;i<2;i++){
        if((listePortes[i]->getState()==EN_OUVERTURE)||(listePortes[i]->getState()==EN_FERMETURE)){
            timer->stop();
            thread->terminate();
            delete timer;
            delete thread;
            listePortes[i]->arret();
        }
    }
}

void Ecluse::resolvePanneP(int num){
    listePortes[num]->resolvedPanne();
}

void Ecluse::resolvePanneV(int num){
    listeValves[num]->resolvedPanne();
}

bool Ecluse::porteOuvrable(int num){
    if((nbrPorteOp+nbrVavleOp)==0){
        if(num==AMONT){
            return niveauEcluse==100?true:false;
        }
        else{
            return niveauEcluse==0?true:false;
        }
    }
    else{
        return false;
    }
}

bool Ecluse::valveOuvrable(){
    if((nbrPorteOp)==0){
        return true;
    }
    else{
        return false;
    }
}

bool Ecluse::getAlarm(){
    return alarmeGenerale;
}

void Ecluse::feuxSetRed(){
    listeFeux[AVAL]->setRed();
    listeFeux[AMONT]->setRed();
}

void Ecluse::switchFeu(int num){
    if(listeFeux[num]->getColor()=='R'){
        listeFeux[num]->setGreen();
    }
    else{
        listeFeux[num]->setRed();
    }
    update();
}

void Ecluse::valideAction(int num, int act){
    if(listePortes[num]->getPanne()){
        listePortes[num]->putAlarm();
        listePortes[num]->arret();
    }
    else{
        if(act==EN_OUVERTURE){
            if(!(listePortes[num]->open())){
                //pop-up pas possible
            }
        }
        else if(act==EN_FERMETURE){
            if(!(listePortes[num]->close())){
                //pop-up pas possible
            }
            nbrPorteOp--;
        }
    }
    update();
    timer->stop();
    delete timer;
    delete thread;
}

void Ecluse::finChangementNiveau(){
    update();
    delete theau;
    theau=NULL;
}

void Ecluse::timerAmont(){
    listePortes[AMONT]->declarePanne();
    listePortes[AMONT]->arret();
    update();
    thread->terminate();
    delete thread;
    timer->stop();
    delete timer;
}

void Ecluse::timerAval(){
    listePortes[AVAL]->declarePanne();
    listePortes[AVAL]->arret();
    update();
    thread->terminate();
    delete thread;
    timer->stop();
    delete timer;
}

void Ecluse::slotUpdate(){
    update();
}

void Ecluse::setAlarm(bool a) {
    alarmeGenerale = a;
}

bool Ecluse::isOpen(int num){
    return listePortes[num]->getState()==OUVRE;
}

bool Ecluse::isClose(int num){
    return listePortes[num]->getState()==FERME;
}

void Ecluse::on_pannePorteAm_released()
{
    listePortes[AMONT]->declarePanne();
    update();
}

void Ecluse::on_pannePorteAv_released()
{
    listePortes[AVAL]->declarePanne();
    update();
}

void Ecluse::on_panneValveAv_released()
{
    listeValves[AVAL]->declarePanne();
    update();
}

void Ecluse::on_panneValveAm_released()
{
    listeValves[AMONT]->declarePanne();
    update();
}
