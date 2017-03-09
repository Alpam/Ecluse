/*
 * =====================================================================================
 *
 *       Filename: expert.cpp
 *
 *    Description: classe définissant la fenêtre mode expert
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "expert.h"
#include "ui_expert.h"

/**
 * @brief Expert::Expert
 *        constructeur de la classe
 * @param e
 *        représentation de l'écluse
 */
Expert::Expert(Ecluse *e) :
    QWidget(0),
    ui(new Ui::Expert)
{
    ui->setupUi(this);
    ecluse = e;
    feuAm = false;
    feuAv = false;
    ui->feuAval->setStyleSheet("background-image: url(./../Ecluse/FeuRouge.png); background-position: center; ");
    ui->feuAmont->setStyleSheet("background-image: url(./../Ecluse/FeuRouge.png); background-position: center; ");
    ui->barreNiveau->setValue(0);
    tBP = new ThreadBarrePro(&e->niveauEcluse);
    tBP->start();
    connect(tBP, SIGNAL(fin()), this, SLOT(rien()));
    connect(tBP, SIGNAL(timeToUpdate(int)), this, SLOT(slotUpDate(int)));
    ecluse->feuxSetRed();
    ecluse->update();
}

/**
 * @brief Expert::~Expert
 *        destructeur de la classe
 */
Expert::~Expert()
{
    tBP->terminate();
    //delete tBP;
    delete ui;
}

/**
 * @brief Expert::on_boutonModeAuto_released
 *        bouton pour passer en mode automatique
 */
void Expert::on_boutonModeAuto_released()
{
    Automatique *w = new Automatique(ecluse);
    w->show();
    this->close();
}

/**
 * @brief Expert::rien
 *        ne fait rien, sert pour la déclaration du thread gérant l'afficahge du niveau de l'eau
 *        cette fonction à pour vocation de n'être jamais déclenchée.
 */
void Expert::rien(){
    //ne fais rien
}

/**
 * @brief Expert::slotUpDate
 *        update l'afficahge du niveau de l'eau
 * @param nE
 *        valeur en % du niveau de l'eau
 */
void Expert::slotUpDate(int nE){
    ui->barreNiveau->setValue(nE);
}

/**
 * @brief Expert::on_boutonStartAlarme_released
 *        bouton déclenchant l'alarme
 */
void Expert::on_boutonStartAlarme_released()
{
    ecluse->putAlarm();
}

/**
 * @brief Expert::on_boutonFeuAmont_released
 *        bouton changeant la couleur du feu amont
 */
void Expert::on_boutonFeuAmont_released()
{
    ecluse->switchFeu(AMONT);
    if (feuAm) {
        ui->feuAmont->setStyleSheet("background-image: url(./../Ecluse/FeuRouge.png); background-position: center; ");
        feuAm = false;
    } else {
        ui->feuAmont->setStyleSheet("background-image: url(./../Ecluse/FeuVert.png); background-position: center; ");
        feuAm = true;
    }
}

/**
 * @brief Expert::on_boutonFeuAval_released
 *        bouton changeant la couleur du feu aval
 */
void Expert::on_boutonFeuAval_released()
{
    ecluse->switchFeu(AVAL);
    if (feuAv) {
        ui->feuAval->setStyleSheet("background-image: url(./../Ecluse/FeuRouge.png); background-position: center; ");
        feuAv = false;
    } else {
        ui->feuAval->setStyleSheet("background-image: url(./../Ecluse/FeuVert.png); background-position: center; ");
        feuAv = true;
    }
}

/**
 * @brief Expert::on_pAmOnOff_released
 *        bouton ouvrant la porte amont
 */
void Expert::on_pAmOnOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->ouvrePorte(AMONT);
}

/**
 * @brief Expert::on_pAvOnOff_released
 *        bouton ouvrant la porte aval
 */
void Expert::on_pAvOnOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->ouvrePorte(AVAL);
}

/**
 * @brief Expert::on_pAvOff_2_released
 *        bouton fermant la porte amont
 */
void Expert::on_pAvOff_2_released()
{
    if (!ecluse->getAlarm())
        ecluse->fermePorte(AMONT);
}

/**
 * @brief Expert::on_pAvOff_released
 *        bouton fermant la porte aval
 */
void Expert::on_pAvOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->fermePorte(AVAL);
}

/**
 * @brief Expert::on_boutonReparePorteAm_released
 *        bouton déclarant la répration de la porte amont
 */
void Expert::on_boutonReparePorteAm_released()
{
    ecluse->resolvePanneP(AMONT);
    ecluse->update();
}

/**
 * @brief Expert::on_boutonReparePorteAv_released
 *        bouton déclarant la répration de la porte aval
 */
void Expert::on_boutonReparePorteAv_released()
{
    ecluse->resolvePanneP(AVAL);
    ecluse->update();
}

/**
 * @brief Expert::on_boutonStopAlarme_released
 *        bouton stopant les alarmes
 */
void Expert::on_boutonStopAlarme_released()
{
    ecluse->disableAlarm();
}

/**
 * @brief Expert::on_vAvOn_released
 *        bouton ouvrant la valve amont
 */
void Expert::on_vAvOn_released()
{
    if (!ecluse->getAlarm())
        ecluse->ouvreValve(AMONT);
}

/**
 * @brief Expert::on_vAvOff_released
 *        bouton fermant la valve amont
 */
void Expert::on_vAvOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->fermeValve(AMONT);
}

/**
 * @brief Expert::on_vAmOn_released
 *        bouton ouvrant la valve aval
 */
void Expert::on_vAmOn_released()
{
    if (!ecluse->getAlarm())
        ecluse->ouvreValve(AVAL);
}

/**
 * @brief Expert::on_vAmOff_released
 *        bouton fermant la valve aval
 */
void Expert::on_vAmOff_released()
{
    if (!ecluse->getAlarm())
        ecluse->fermeValve(AVAL);
}

/**
 * @brief Expert::on_boutonRepareValveAm_released
 *        bouton déclarant la réparation effectuer pour la valve amont
 */
void Expert::on_boutonRepareValveAm_released()
{
    ecluse->resolvePanneV(AMONT);
    ecluse->update();
}

/**
 * @brief Expert::on_boutonRepareValveAv_released
 *        bouton déclarant la réparation effectuer pour la valve aval
 */
void Expert::on_boutonRepareValveAv_released()
{
     ecluse->resolvePanneV(AVAL);
     ecluse->update();
}
