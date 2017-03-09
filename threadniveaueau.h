/*
 * =====================================================================================
 *
 *       Filename: threadniveaueau.h
 *
 *    Description: fichier header de threadniveaueau
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef THREADNIVEAUEAU_H
#define THREADNIVEAUEAU_H

#include <QApplication>
#include <QThread>

class ThreadNiveauEau : public QThread{
    Q_OBJECT
    public:
        ThreadNiveauEau(int *ne, int n);

    public slots :
        void run();

    signals :
        void finish();
        void timeToUpdate();

    private :
        int num;
        int *niveauEau;
};

#endif // THREADNIVEAUEAU_H
