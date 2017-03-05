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

void MainWindow::on_pushButton_12_released()
{
    Expert *w = new Expert;
    w->show();
}

void MainWindow::on_pushButton_14_released()
{
    Automatique *w = new Automatique;
    w->show();
}
