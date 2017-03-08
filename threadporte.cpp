/*
 * =====================================================================================
 *
 *       Filename:
 *
 *    Description:
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "threadporte.h"
#include <unistd.h>

ThreadPorte::ThreadPorte(int n, int a)
{
    num=n;
    act=a;
}

void ThreadPorte::run()
{
    sleep(10);
    emit signalTerminal(num,act);
}
