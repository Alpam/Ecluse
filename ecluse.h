/*
 * =====================================================================================
 *
 *       Filename: ecluse.h
 *
 *    Description: fichier header d'écluse
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef ECLUSE_H
#define ECLUSE_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include "threadniveaueau.h"
#include "threadporte.h"
#include "porte.h"
#include "valve.h"
#include "signallumineux.h"

#define BAMONT 0
#define BECAMONT 1
#define BECMID 2
#define BECAVAL 3
#define BAVAL 4

namespace Ui {
    class Ecluse;
}

class Ecluse : public QWidget{

    Q_OBJECT

    public:
        explicit Ecluse(QWidget *parent = 0);
        void update();
        void ouvrePorte(int num);
        void fermePorte(int num);
        void ouvreValve(int num);
        void fermeValve(int num);
        void putAlarm();
        void disableAlarm();
        void miseAlArret();
        void resolvePanneP(int num);
        void resolvePanneV(int num);
        bool porteOuvrable(int num);
        bool valveOuvrable();
        bool getAlarm();
        void feuxSetRed();
        void switchFeu(int num);
        bool isOpen(int num);
        bool isClose(int num);
        int niveauEcluse; //en pourcentage entre la hauteur de l'amont 100% et l'aval 0%
        int *addPorteAmont;//état de la porte amont
        int *addPorteAval; //état de la porte aval
        int pos;//position du bateau dans la représentation graphique
        ~Ecluse();

    private:
        Ui::Ecluse *ui;
        void setAlarm(bool a);
        int nbrVavleOp;
        //compte le nombre de valve ouverte
        int nbrPorteOp;
        //compte le nombre de porte ouverte
        bool alarmeGenerale;
        Porte *listePortes[2];
        Valve *listeValves[2];
        SignalLumineux *listeFeux[2];
        //par convention l'indice 0 représente l'AMONT, l'indice 1 représente l'AVAL
        QTimer *timer; //thread réservé à un timer
        ThreadPorte *thread; //thread réservé à l'ouverture d'une porte, représente
        ThreadNiveauEau *theau; //thread réservé à la monter de l'eau

    public slots :
            void valideAction(int num,int act);
            void finChangementNiveau();
            void timerAmont();
            void timerAval();
            void slotUpdate();
    private slots:
            void on_pannePorteAm_released();
            void on_pannePorteAv_released();
            void on_panneValveAv_released();
            void on_panneValveAm_released();
};

#endif // ECLUSE_H
