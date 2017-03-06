#include "mainwindow.h"
#include <QApplication>
//ceci est un commentaire

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
