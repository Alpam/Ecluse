#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QApplication>
#include <QtGUI>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT

    public:
            MyThread(int n);

    public slots :
            void run();

    signals :
            void valueChanged(int num);

    public :
            int num;
};

#endif
