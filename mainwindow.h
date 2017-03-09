/*
 * =====================================================================================
 *
 *       Filename: mainwindow.h
 *
 *    Description: fichier header de mainwindow
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "automatique.h"
#include "expert.h"
#include "ecluse.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(Ecluse *e);
        ~MainWindow();
        Ecluse *ecluse;

    private slots:
        void on_boutonModeAuto_released();
        void on_boutonModeExp_released();

    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
