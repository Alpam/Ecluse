/*
 * =====================================================================================
 *
 *       Filename: threadattporte.h
 *
 *    Description: fichier header de threadattporte
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef THREADATTPORTE_H
#define THREADATTPORTE_H

#include <QApplication>
#include <QThread>

class ThreadAttPorte : public QThread{
    Q_OBJECT
    public:
        ThreadAttPorte(int *sP, int s);

    public slots:
        void run();

    signals :
        void finPorte();

    private :
        int *stateP;
        int state; //état attendu fermé ou ouvert
    };

#endif // THREADATTPORTE_H
