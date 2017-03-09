/*
 * =====================================================================================
 *
 *       Filename: threadbarrepro.h
 *
 *    Description: fichier header de threadbarrepro
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef THREADBARREPRO_H
#define THREADBARREPRO_H

#include <QApplication>
#include <QThread>

class ThreadBarrePro : public QThread
{
    Q_OBJECT
    public:
        ThreadBarrePro(int *nE);

    public slots:
        void run();

    signals :
        void fin();
        void timeToUpdate(int nE);

    private :
        int *niveauEcluse;
};

#endif // THREADBARREPRO_H
