/*
 * =====================================================================================
 *
 *       Filename: mainwindow.cpp
 *
 *    Description: fenetre avec donnant le choix entre les deux modes
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

/**
 * @brief MainWindow::MainWindow
 *        constructeur
 * @param e
 *        représentation de l'écluse
 */
MainWindow::MainWindow(Ecluse *e) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ecluse = e;
}

/**
 * @brief MainWindow::~MainWindow
 *        destructeur
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_boutonModeExp_released
 *        permet de passer au mode expert
 */
void MainWindow::on_boutonModeExp_released()
{
    QString txt = QInputDialog::getText(this,"Password ?","Mot de passe ?",QLineEdit::Password);
        if(txt == "password"){
            Expert *w = new Expert(ecluse);
            w->show();
            this->close();
        }
}

/**
 * @brief MainWindow::on_boutonModeAuto_released
 *        permet de passer au mode automatique
 */
void MainWindow::on_boutonModeAuto_released()
{
    Automatique *w = new Automatique(ecluse);
    w->show();
    this->close();
}
