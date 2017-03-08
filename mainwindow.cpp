/*
 * =====================================================================================
 *
 *       Filename:
 *
 *    Description:
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(Ecluse *e) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ecluse = e;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_boutonModeExp_released()
{
    QString txt = QInputDialog::getText(this,"Password ?","Mot de passe ?",QLineEdit::Password);
        if(txt == "password"){
            Expert *w = new Expert(ecluse);
            w->show();
            this->close();
        }
}

void MainWindow::on_boutonModeAuto_released()
{
    Automatique *w = new Automatique(ecluse);
    w->show();
    this->close();
}
