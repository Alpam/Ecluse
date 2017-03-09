/*
 * =====================================================================================
 *
 *       Filename: automatique.h
 *
 *    Description: fichier header d'automatique
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef AUTOMATIQUE_H
#define AUTOMATIQUE_H

#include <QWidget>
#include "expert.h"
#include "ecluse.h"
#include "threadbarrepro.h"
#include "threadattporte.h"
#include "threadattniveau.h"

namespace Ui {
class Automatique;
}

class Automatique : public QWidget{
    Q_OBJECT

    public:
        Automatique(Ecluse *e);
        ~Automatique();
        Ecluse *ecluse;

    private slots:
        void on_boutonModeExp_released();
        void rien();
        void slotUpDate(int nE);
        void on_startAlarme_released();
        void on_boutonStartPassage_released();
        void on_radBouAmAv_clicked();
        void on_boutonProgression_released();
        void on_boutonFinPassage_released();
        void on_radBouAvAm_clicked();

    public slots :
        void secondStart();
        void troisiemeStart();
        void finStart();
        void secondProgression();
        void troisiemeProgression();
        void finProgression();
        void finTerminaison();

    private:
        Ui::Automatique *ui;
        ThreadBarrePro *tBP;
        //emplacement mémoire réserver au thread gérant le niveau de l'eau dans l'interface
        ThreadAttPorte *th;
        //emplacement mémoire réserver au thread qui attende la ouverture/fermeture d'une porte
        ThreadAttNiveau *thn;
        //emplacement mémoire attendant la fin de la monter/descente de l'eau
        int depart;
        //enregistre le sens avalant ou montant suivie pour le mode automatique
};

#endif // AUTOMATIQUE_H
