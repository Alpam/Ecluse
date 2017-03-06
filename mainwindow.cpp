#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "automatique.h"
#include "expert.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_boutonModeExp_released()
{
    Expert *w = new Expert;
    w->show();
    this->close();
}

void MainWindow::on_boutonModeAuto_released()
{
    Automatique *w = new Automatique;
    w->show();
    this->close();
}
