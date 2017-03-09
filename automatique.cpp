/*
 * =====================================================================================
 *
 *       Filename: automatique.cpp
 *
 *    Description: classe représentant la fenêtre mode automatique
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "automatique.h"
#include "ui_automatique.h"
#include <unistd.h>

#include <QInputDialog>

/**
 * @brief Automatique::Automatique
 *        constructeur de la classe
 * @param e
 *        la représentation de l'ecluse
 */
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

/**
 * @brief Automatique::~Automatique
 *        destructeur de la classe
 */
Automatique::~Automatique()
{
    th->terminate();
    th->quit();
    thn->terminate();
    th->quit();
    tBP->terminate();
    th->quit();
    delete ui;
}

/**
 * @brief Automatique::on_boutonModeExp_released
 *        bouton permettant de passer en mode expert
 */
void Automatique::on_boutonModeExp_released()
{
    QString txt = QInputDialog::getText(this,"Password ?","Mot de passe ?",QLineEdit::Password);
        if(txt == "password"){
            Expert *w = new Expert(ecluse);
            w->show();
            this->close();
        }
}

/**
 * @brief Automatique::rien
 *        ne fait rien, sert pour la déclaration du thread gérant l'afficahge du niveau de l'eau
 *        cette fonction à pour vocation de n'être jamais déclenchée.
 */
void Automatique::rien(){
    //ne fais rien
}

/**
 * @brief Automatique::slotUpDate
 *        update l'afficahge du niveau de l'eau
 * @param nE
 *        valeur en % du niveau de l'eau
 */
void Automatique::slotUpDate(int nE){
    ui->barreNiveau->setValue(nE);
}

/**
 * @brief Automatique::on_startAlarme_released
 *        délcenche l'alarme et met les feux au rouge
 */
void Automatique::on_startAlarme_released()
{
    ecluse->putAlarm();
    ecluse->feuxSetRed();
}

/**
 * @brief Automatique::on_radBouAmAv_clicked
 *        permet de déclencher la séquence automatique
 *        en rendant accessible le bouton start
 */
void Automatique::on_radBouAmAv_clicked()
{
    ui->boutonStartPassage->setDisabled(false);
}

/**
 * @brief Automatique::on_radBouAvAm_clicked
 *        permet de déclencher la séquence automatique
 *        en rendant accessible le bouton start
 */
void Automatique::on_radBouAvAm_clicked()
{
    ui->boutonStartPassage->setDisabled(false);
}

/**
 * @brief Automatique::on_boutonStartPassage_released
 *        déclenche la séquence après click sur le bouton start
 */
void Automatique::on_boutonStartPassage_released()
{
    ecluse->feuxSetRed();
    ui->radBouAmAv->setDisabled(true);
    ui->radBouAvAm->setDisabled(true);
    ecluse->fermeValve(AMONT);
    ecluse->fermeValve(AVAL);
    //si la porte à l'opposé est ouverte on la ferme
    //un thread est lancé pour attendre la fin de la fermeture
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

/**
 * @brief Automatique::secondStart
 *        seconde partie de la séquence
 */
void Automatique::secondStart(){
    th->terminate();
    th->quit();
    //on vérifie que le niveau de l'eau soit bon sinon on ouvre la valve voulut
    //un thread est lancé pour attendre le changement de niveau
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

/**
 * @brief Automatique::troisiemeStart
 *        troisième partie de la séquence
 */
void Automatique::troisiemeStart(){
    thn->terminate();
    thn->quit();
    //on ouvre la porte
    //un thread est lancé pour attendre la fin de l'ouverture
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
/**
 * @brief Automatique::finStart
 *        quatrieme partie de la séquence
 */
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

/**
 * @brief Automatique::on_boutonProgression_released
 *        cinquième partie de la séquence se délchence après click sur le bouton progression
 */
void Automatique::on_boutonProgression_released()
{
    //fermeture de la porte
    //un thread est lancer pour attendre la fin de la fermeture
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

/**
 * @brief Automatique::secondProgression
 *        sixieme partie de la séquence
 */
void Automatique::secondProgression(){
    th->terminate();
    th->quit();
    //ouverture de l'éclsue
    //un thread est lancé pour attendre la fin du changement du niveau de l'eau
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

/**
 * @brief Automatique::troisiemeProgression
 *        septième partie de la séquence
 */
void Automatique::troisiemeProgression(){
    thn->terminate();
    thn->quit();
    //fermeture de l'ecluse et ouverture porte
    //un thread est lancé pour attendre la fin de l'ouverture
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

/**
 * @brief Automatique::finProgression
 *        huitième partie de la séquence
 */
void Automatique::finProgression(){
    th->terminate();
    th->quit();
    if(depart==AMONT){
        ecluse->switchFeu(AVAL);
    }
    else{
        ecluse->switchFeu(AMONT);
    }
    ui->boutonProgression->setDisabled(true);
    ui->boutonFinPassage->setDisabled(false);
}

/**
 * @brief Automatique::on_boutonFinPassage_released
 *        neuvième partie de la séquence déclenché après click sur le bouton fin
 */
void Automatique::on_boutonFinPassage_released()
{
    //la porte précédemment ouverte dans la partie précédente est fermée
    //un thread est lancé pour attendre la fermeture
    if(depart==AMONT){
        ecluse->pos = BAVAL;
        ecluse->switchFeu(AVAL);
        ecluse->fermePorte(AVAL);
        th = new ThreadAttPorte(ecluse->addPorteAval, FERME);
        th->start();
        connect(th,SIGNAL(finPorte()),this,SLOT(finTerminaison()));
    }
    else{
        ecluse->pos = BAMONT;
        ecluse->switchFeu(AMONT);
        ecluse->fermePorte(AMONT);
        th = new ThreadAttPorte(ecluse->addPorteAmont, FERME);
        th->start();
        connect(th,SIGNAL(finPorte()),this,SLOT(finTerminaison()));
    }
}

/**
 * @brief Automatique::finTerminaison
 *        dixième et dernière étape de la séquence automatique
 *        elle remet l'écluse dans un état initiale ainsi que l'IHM
 */
void Automatique::finTerminaison(){
    th->terminate();
    th->quit();
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
