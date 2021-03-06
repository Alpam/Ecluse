/*
 * =====================================================================================
 *
 *       Filename: threadattniveau.h
 *
 *    Description: fichier header de threadattniveau
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef THREADATTNIVEAU_H
#define THREADATTNIVEAU_H

#include <QApplication>
#include <QThread>

class ThreadAttNiveau : public QThread{
    Q_OBJECT
    public:
        ThreadAttNiveau(int *nE, int c);

    public slots :
        void run();

    signals :
        void finNiv();

    private :
        int *niveauEau;
        int cst;//niveau d'eau attendu
};

#endif // THREADATTNIVEAU_H
