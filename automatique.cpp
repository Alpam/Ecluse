#include "automatique.h"
#include "ui_automatique.h"

#include <QInputDialog>

Automatique::Automatique(Ecluse *e) :
    QWidget(0),
    ui(new Ui::Automatique)
{
    ui->setupUi(this);
    ecluse = e;
}

Automatique::~Automatique()
{
    delete ui;
}

void Automatique::on_boutonModeExp_released()
{
    QString txt = QInputDialog::getText(this,"Password ?","Mot de passe ?",QLineEdit::Password);
        if(txt == "password"){
            Expert *w = new Expert(ecluse);
            w->show();
            this->close();
        }
}
