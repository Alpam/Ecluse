#include "ecluse.h"
#include "ui_ecluse.h"

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
  ui->etat->setText("Valve Amont : " + QString::number(listePortes[AMONT]->getState())
                    + "\nValve Aval : " + QString::number(listePortes[AVAL]->getState())
                    + "\nPorte Amont : " + QString::number(listeValves[AMONT]->getState())
                    + "\nPorte Aval : " + QString::number(listeValves[AVAL]->getState())
                    + "\nSignLumi Amont : " + listeFeux[AMONT]->getColor()
                    + "\nSignLumi Aval : " + listeFeux[AVAL]->getColor());
}

void Ecluse::ouvrePorte(int num){
    /*if(unlocked && (alarmeGeneral != ON)){
        QTimer *timer = new QTimer(parent);
        QObject::connect(&timer, SIGNAL(timeout()), *parent,SLOT(timer_timeout(num,'o')));
        if(listePortes[num]->open()){

        }
    }*/
    listePortes[num]->sendSignal(OUVRE,AMONT);

}
