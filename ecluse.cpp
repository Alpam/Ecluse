#include "ecluse.h"
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
    unlocked=true;
    niveauEcluse = 0;
    alarmeGenerale = OFF;
    panneGenerale = false;

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

    ui->etat->setText("PORTE AMONT\n\tEtat : " + etatPorteAmont + "\n\t" + alarmePorteAmont + "\n\t" + pannePorteAmont
                      + "\n\nPORTE AVAL\n\tEtat : " + etatPorteAval + "\n\t" + alarmePorteAval + "\n\t" + pannePorteAval
                      + "\n\nVALVE AMONT\n\tEtat : " + etatValveAmont + "\n\t" + alarmeValveAmont + "\n\t" + panneValveAmont
                      + "\n\nVALVE AVAL\n\tEtat : " + etatValveAval + "\n\t" + alarmeValveAval + "\n\t" + panneValveAval
                      + "\n\nSIGNAL LUMINEUX AVAL\t" + listeFeux[AVAL]->getColor()
                      + "\n\nSIGNAL LUMINEUX AMONT\t" + listeFeux[AMONT]->getColor());
}

void Ecluse::ouvrePorte(int num){
    if(unlocked && (alarmeGenerale != ON)){
        if(!(listePortes[num]->ask_open())){
            //ça plante
            return;
        }
        update();
        /*if(!(listePortes[num]->ask_open())){
        {
            QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
            timer.start(10000);

        }*/
    }
}

void Ecluse::timer_timeout(){
    ui->etat->setText("Bouh");
}
