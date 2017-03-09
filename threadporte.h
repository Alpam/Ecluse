/*
 * =====================================================================================
 *
 *       Filename: threadporte.h
 *
 *    Description: fichier header de threadporte
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef THREADPORTE_H
#define THREADPORTE_H

#include <QApplication>
#include <QThread>

class ThreadPorte : public QThread{
    Q_OBJECT

    public:
        ThreadPorte(int n, int a);

    public slots :
        void run();

    signals :
        void signalTerminal(int num, int act);

    public :
        int num;
        int act;
};

#endif
