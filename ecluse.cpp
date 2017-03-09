/*
 * =====================================================================================
 *
 *       Filename: ecluse.cpp
 *
 *    Description: la classe ecluse manage la représentation d'une écluse à tout moment
 *                 et répond au interraction avec l'IHM.
 *                 Elle est également utilisée pour la simulation.
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "ecluse.h"
#include "threadniveaueau.h"
#include "threadporte.h"
#include "ui_ecluse.h"
#include <unistd.h>
#include <iostream>

#include <QInputDialog>

/**
 * @brief Ecluse::Ecluse
 *        constructeur de la classe
 * @param parent
 */
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
    ui->bateauAm->setVisible(false);
    ui->bateauAv->setVisible(false);
    ui->bateauEcAm->setVisible(false);
    ui->bateauEcAv->setVisible(false);
    nbrVavleOp = 0;
    nbrPorteOp = 0;
    niveauEcluse = 0;
    alarmeGenerale = OFF;
    addPorteAmont = &listePortes[0]->state;
    addPorteAval = &listePortes[1]->state;
    theau=NULL;
}

/**
 * @brief Ecluse::~Ecluse
 *        destructeur de la classe
 */
Ecluse::~Ecluse()
{
    delete ui;
}

/**
 * @brief Ecluse::update
 *        Update l'affichage des états de l'écluse
 */
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
            break;
        case 50 : ui->eauEcAm->setVisible(false); ui->eauEcMid->setVisible(true);
            break;
        case 0 : ; ui->eauEcAm->setVisible(false); ui->eauEcMid->setVisible(false);
            break;
    }
    switch (pos) {
        case BAVAL : ui->bateauAv->setVisible(true);
        ui->bateauAm->setVisible(false);
        ui->bateauEcAv->setVisible(false);
        ui->bateauEcAm->setVisible(false);
            break;
        case BECAVAL : ui->bateauEcAv->setVisible(true);
        ui->bateauAv->setVisible(false);
        ui->bateauAm->setVisible(false);
        ui->bateauEcAm->setVisible(false);
            break;
        case BECAMONT : ui->bateauEcAm->setVisible(true);
        ui->bateauAv->setVisible(false);
        ui->bateauEcAv->setVisible(false);
        ui->bateauAm->setVisible(false);
            break;
        case BAMONT : ui->bateauAm->setVisible(true);
        ui->bateauAv->setVisible(false);
        ui->bateauEcAv->setVisible(false);
        ui->bateauEcAm->setVisible(false);
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
                      + "\n\nSIGNAL LUMINEUX AV\t\t" + listeFeux[AVAL]->getColor()
                      + "\n\nSIGNAL LUMINEUX AM\t\t" + listeFeux[AMONT]->getColor()
                      + "\n\nNIVEAU EAU\t" + nE);
}

/**
 * @brief Ecluse::ouvrePorte
 *        Provoque l'ouverture d'une porte
 * @param num
 *        définit si il s'agit de l'aval ou de l'amont
 */
void Ecluse::ouvrePorte(int num){
    if(porteOuvrable(num)){
        if(!(listePortes[num]->ask_open())){
            return;
        }
        nbrPorteOp++;
        update();
        thread = new ThreadPorte(num,EN_OUVERTURE);
        thread->start();
        timer = new QTimer();
        //si le timer se termine avant le thread, il
        //met la porte en arret et en panne puis déclenche une alarme
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

/**
 * @brief Ecluse::fermePorte
 *        Provoque la fermeture d'une porte
 * @param num
 *        définit si il s'agit de l'aval ou l'amont
 */
void Ecluse::fermePorte(int num){
    if(!(listePortes[num]->ask_close())){
        return;
    }
    update();
    thread = new ThreadPorte(num,EN_FERMETURE);
    thread->start();
    timer = new QTimer();
    //si le timer se termine avant le thread, il
    //met la porte en arret et en panne puis déclenche une alarme
    if(num==AMONT){
        connect(timer, SIGNAL(timeout()), this, SLOT(timerAmont()));
    }
    else{
        connect(timer, SIGNAL(timeout()), this, SLOT(timerAval()));
    }
    connect(thread, SIGNAL(signalTerminal(int,int)), this,SLOT(valideAction(int,int)));
    timer->start(12000);
}

/**
 * @brief Ecluse::ouvreValve
 *        déclenche l'ouvertue d'une valve ainsi que le changement du niveau de l'eau
 * @param num
 *        définit si il s'agit de l'aval ou l'amont
 */
void Ecluse::ouvreValve(int num){
    if(valveOuvrable()){
    if(listeValves[num]->open()){
        nbrVavleOp++;
        update();
        if(nbrVavleOp==2){
            //si les 2 valves sont ouvertes et qu'un thread modifiant le niveau
            //de l'eau est ouvert il est fermé
            if(theau!=NULL){
                theau->terminate();
                theau->quit();
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
    }
}

/**
 * @brief Ecluse::fermeValve
 *        déclenche la fermeture d'une valve ainsi que le changement du niveau de l'eau
 * @param num
 *        définit si il s'agit de l'aval ou l'amont
 */
void Ecluse::fermeValve(int num){
    if(listeValves[num]->close()){
        update();
        if(theau!=NULL){
            theau->terminate();
            theau->quit();
            theau=NULL;
        }
        nbrVavleOp--;
        if(nbrVavleOp==1){
            //si il ne reste qu'une valve d'ouverte, le niveau de l'eau est mofifiée
            int tmp;
            num==AMONT?tmp=AVAL:tmp=AMONT;
            theau = new ThreadNiveauEau(&niveauEcluse, tmp);
            theau->start();
            connect(theau, SIGNAL(finish()), this,SLOT(finChangementNiveau()));
            connect(theau, SIGNAL(timeToUpdate()), this, SLOT(slotUpdate()));
        }
    }
}

/**
 * @brief Ecluse::putAlarm
 *        déclenche une alarme sur toute l'écluse,
 *        ferme les valves et met en arret les portes
 */
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

/**
 * @brief Ecluse::disableAlarm
 *        arrete l'alarme
 */
void Ecluse::disableAlarm(){
    listePortes[AVAL]->disableAlarm();
    listePortes[AMONT]->disableAlarm();
    listeValves[AVAL]->disableAlarm();
    listeValves[AMONT]->disableAlarm();
    setAlarm(false);
    update();
}

/**
 * @brief Ecluse::miseAlArret
 *        si une porte est en ouverture ou fermeture elle mise en arret
 */
void Ecluse::miseAlArret(){
    for(int i=0;i<2;i++){
        if((listePortes[i]->getState()==EN_OUVERTURE)||(listePortes[i]->getState()==EN_FERMETURE)){
            timer->stop();
            thread->terminate();
            thread->quit();
            delete timer;
            listePortes[i]->arret();
        }
    }
}

/**
 * @brief Ecluse::resolvePanneP
 *        stop la panne d'une porte
 * @param num
 *        définit si il s'agit de l'amont ou de l'aval
 */
void Ecluse::resolvePanneP(int num){
    listePortes[num]->resolvedPanne();
}

/**
 * @brief Ecluse::resolvePanneV
 *        stop la panne d'une valve
 * @param num
 *        définit si il s'agit de l'amont ou de l'aval
 */
void Ecluse::resolvePanneV(int num){
    listeValves[num]->resolvedPanne();
}

/**
 * @brief Ecluse::porteOuvrable
 *        déinit si une porte est ouvrable
 * @param num
 *        définit si il s'agit de l'amont ou de l'aval
 * @return
 *        si vrai ou faux
 */
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

/**
 * @brief Ecluse::valveOuvrable
 *        définit si une valve est ouvrable
 * @return
 *        si vrai ou faux
 */
bool Ecluse::valveOuvrable(){
    if((nbrPorteOp)==0){
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief Ecluse::getAlarm
 *        retourne l'état de l'alarme
 * @return
 *        si vrai ou faux
 */
bool Ecluse::getAlarm(){
    return alarmeGenerale;
}

/**
 * @brief Ecluse::feuxSetRed
 *        met les 2 feux au rouge
 */
void Ecluse::feuxSetRed(){
    listeFeux[AVAL]->setRed();
    listeFeux[AMONT]->setRed();
}

/**
 * @brief Ecluse::switchFeu
 *        change un feu de couleur
 * @param num
 *        définit si il s'agit de l'amont ou de l'aval
 */
void Ecluse::switchFeu(int num){
    if(listeFeux[num]->getColor()=='R'){
        listeFeux[num]->setGreen();
    }
    else{
        listeFeux[num]->setRed();
    }
    update();
}

/**
 * @brief Ecluse::valideAction
 *        s'active quand le thread gérant la porte se termine
 * @param num
 *        définit si il s'agit de l'amont ou de l'aval
 * @param act
 *        l'action à effectuer
 */
void Ecluse::valideAction(int num, int act){
    if(listePortes[num]->getPanne()){
        listePortes[num]->putAlarm();
        listePortes[num]->arret();
    }
    else{
        if(act==EN_OUVERTURE){
            if(!(listePortes[num]->open())){
            }
        }
        else if(act==EN_FERMETURE){
            if((listePortes[num]->close())){
                nbrPorteOp--;
            }
        }
    }
    update();
    timer->stop();
    delete timer;
}

/**
 * @brief Ecluse::finChangementNiveau
 *        met à jour l'affichage et ferme le thread
 */
void Ecluse::finChangementNiveau(){
    update();
    theau->quit();
    theau=NULL;
}

/**
 * @brief Ecluse::timerAmont
 *        gère le timer pour la porte en amont
 */
void Ecluse::timerAmont(){
    listePortes[AMONT]->declarePanne();
    listePortes[AMONT]->arret();
    update();
    thread->terminate();
    thread->quit();
    timer->stop();
    delete timer;
}

/**
 * @brief Ecluse::timerAval
 *        gère le timer pour la porte en aval
 */
void Ecluse::timerAval(){
    listePortes[AVAL]->declarePanne();
    listePortes[AVAL]->arret();
    update();
    thread->terminate();
    thread->quit();
    timer->stop();
    delete timer;
}

void Ecluse::slotUpdate(){
    update();
}

/**
 * @brief Ecluse::setAlarm
 *        set l'état de l'alarme
 * @param a
 *        booléen représentant l'état
 */
void Ecluse::setAlarm(bool a) {
    alarmeGenerale = a;
}

/**
 * @brief Ecluse::isOpen
 *        renvoie si une porte est ouverte
 * @param num
 *        définit si il s'agit de l'amont ou de l'aval
 * @return
 *        vrai ou faux
 */
bool Ecluse::isOpen(int num){
    return listePortes[num]->getState()==OUVRE;
}

/**
 * @brief Ecluse::isClose
 *        renvoie si une porte est fermée
 * @param num
 *        définit si il s'agit de l'amont ou de l'aval
 * @return
 *        vrai ou faux
 */
bool Ecluse::isClose(int num){
    return listePortes[num]->getState()==FERME;
}

/**
 * @brief Ecluse::on_pannePorteAm_released
 *        met la porte amont à l'arrêt et en panne
 *        la déclaration de panne déclenche une alarme
 */
void Ecluse::on_pannePorteAm_released()
{
    miseAlArret();
    listePortes[AMONT]->declarePanne();

    update();
}

/**
 * @brief Ecluse::on_pannePorteAv_released
 *        met la porte aval à l'arrêt et en panne
 *        la déclaration de panne déclenche une alarme
 */
void Ecluse::on_pannePorteAv_released()
{
    miseAlArret();
    listePortes[AVAL]->declarePanne();
    update();
}

/**
 * @brief Ecluse::on_panneValveAv_released
 *        met la valve aval en panne,
 *        la déclaration de panne déclenche une alarme
 *        la valve est alors fermée (on considère qu'il y a un
 *        système de sécurité fermant la valve)
 */
void Ecluse::on_panneValveAv_released()
{
    fermeValve(AVAL);
    listeValves[AVAL]->declarePanne();
    update();
}

/**
 * @brief Ecluse::on_panneValveAm_released
 *        met la valve amont en panne,
 *        la déclaration de panne déclenche une alarme
 *        la valve est alors fermée (on considère qu'il y a un
 *        système de sécurité fermant la valve)
 */
void Ecluse::on_panneValveAm_released()
{
    fermeValve(AMONT);
    listeValves[AMONT]->declarePanne();
    update();
}
