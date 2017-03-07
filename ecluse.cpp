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
    nbrVavleOp = 0;
    nbrPorteOp = 0;
    niveauEcluse = 0;
    alarmeGenerale = OFF;
    panneGenerale = false;
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
            pannePorteAval, pannePorteAmont, panneValveAval, panneValveAmont;
    switch (listePortes[AMONT]->getState()) {
        case OUVRE : etatPorteAmont = "Ouverte";
            break;
        case EN_OUVERTURE : etatPorteAmont = "Ouverture";
            break;
        case FERME : etatPorteAmont = "Fermee";
            break;
        case EN_FERMETURE : etatPorteAmont = "Fermeture";
            break;
        case EN_ARRET : etatPorteAmont = "Arretee";
            break;
    }
    switch (listePortes[AVAL]->getState()) {
        case OUVRE : etatPorteAval = "Ouverte";
            break;
        case EN_OUVERTURE : etatPorteAval = "Ouverture";
            break;
        case FERME : etatPorteAval = "Fermee";
            break;
        case EN_FERMETURE : etatPorteAval = "Fermeture";
            break;
        case EN_ARRET : etatPorteAval = "Arretee";
            break;
    }
    switch (listeValves[AVAL]->getState()) {
        case OUVRE : etatValveAval = "Ouverte";
            break;
        case FERME : etatValveAval = "Fermee";
            break;
    }
    switch (listeValves[AMONT]->getState()) {
        case OUVRE : etatValveAmont = "Ouverte";
            break;
        case FERME : etatValveAmont = "Fermee";
            break;
    }
    if (listePortes[AVAL]->getPanne())
        pannePorteAval = "En Panne";
    else
        pannePorteAval = "Fonctionnel";
    if (listePortes[AMONT]->getPanne())
        pannePorteAmont = "En Panne";
    else
        pannePorteAmont = "Fonctionnel";
    if (listeValves[AVAL]->getPanne())
        panneValveAval = "En Panne";
    else
        panneValveAval = "Fonctionnel";
    if (listeValves[AMONT]->getPanne())
        panneValveAmont = "En Panne";
    else
        panneValveAmont = "Fonctionnel";
    if (listePortes[AVAL]->getAlarm())
        alarmePorteAval = "En Alarme";
    else
        alarmePorteAval = "Pas en Alarme";
    if (listePortes[AMONT]->getAlarm())
        alarmePorteAmont = "En Alarme";
    else
        alarmePorteAmont = "Pas en Alarme";
    if (listeValves[AVAL]->getAlarm())
        alarmeValveAval = "En Alarme";
    else
        alarmeValveAval = "Pas en Alarme";
    if (listeValves[AMONT]->getAlarm())
        alarmeValveAmont = "En Alarme";
    else
        alarmeValveAmont = "Pas en Alarme";

    QString nE = QString::number(niveauEcluse);
    ui->etat->setText("PORTE AMONT\n\tEtat : " + etatPorteAmont + "\n\t" + alarmePorteAmont + "\n\t" + pannePorteAmont
                      + "\n\nPORTE AVAL\n\tEtat : " + etatPorteAval + "\n\t" + alarmePorteAval + "\n\t" + pannePorteAval
                      + "\n\nVALVE AMONT\n\tEtat : " + etatValveAmont + "\n\t" + alarmeValveAmont + "\n\t" + panneValveAmont
                      + "\n\nVALVE AVAL\n\tEtat : " + etatValveAval + "\n\t" + alarmeValveAval + "\n\t" + panneValveAval
                      + "\n\nSIGNAL LUMINEUX AVAL\t" + listeFeux[AVAL]->getColor()
                      + "\n\nSIGNAL LUMINEUX AMONT\t" + listeFeux[AMONT]->getColor()
                      + "\n\nNIVEAU EAU\t" + nE);
}

void Ecluse::ouvrePorte(int num){
    if(porteOuvrable()){
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
                delete theau;
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

void Ecluse::slotUpdate(){
    update();
}

bool Ecluse::porteOuvrable(){
    if((nbrPorteOp+nbrVavleOp)==0){
        return true;
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
