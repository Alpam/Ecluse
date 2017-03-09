/*
 * =====================================================================================
 *
 *       Filename:expert.h
 *
 *    Description: fichier header de expert
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef EXPERT_H
#define EXPERT_H

#include <QWidget>
#include "automatique.h"
#include "ecluse.h"
#include "threadbarrepro.h"

namespace Ui {
class Expert;
}

class Expert : public QWidget{
    Q_OBJECT

    public:
        Expert(Ecluse *e);
        ~Expert();
        Ecluse *ecluse;

    private slots:
        void on_boutonModeAuto_released();
        void rien();
        void slotUpDate(int nE);
        void on_boutonStartAlarme_released();
        void on_boutonFeuAmont_released();
        void on_boutonFeuAval_released();
        void on_pAmOnOff_released();
        void on_pAvOnOff_released();
        void on_pAvOff_2_released();
        void on_pAvOff_released();
        void on_boutonReparePorteAm_released();
        void on_boutonReparePorteAv_released();
        void on_boutonStopAlarme_released();
        void on_vAvOn_released();
        void on_vAvOff_released();
        void on_vAmOn_released();
        void on_vAmOff_released();
        void on_boutonRepareValveAm_released();
        void on_boutonRepareValveAv_released();

    private:
        Ui::Expert *ui;
        ThreadBarrePro *tBP;//thread réservé à l'affichage du niveau de l'eau
        bool feuAm;
        bool feuAv;
};

#endif // EXPERT_H
