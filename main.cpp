/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  main file, démarre le programme
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ecluse *ecluse = new Ecluse;
    ecluse->update();
    ecluse->show();
    MainWindow w(ecluse);
    w.show();

    return a.exec();
}
