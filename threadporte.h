/*#ifndef THREADPORTE_H
#define THREADPORTE_H

#include <QThread>


class ThreadPorte : public QThread
{
    Q_OBJECT

public:
    ThreadPorte(int n, QObject *parent = 0);
    int num;
    void run();

signals :
    void complete(int num);
};

#endif // THREADPORTE_H
*/
