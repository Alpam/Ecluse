/*
 * =====================================================================================
 *
 *       Filename: signallumineurx.h
 *
 *    Description: fichier header de signallumineux
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#ifndef SIGNALLUMINEUX_H
#define SIGNALLUMINEUX_H

#include "gear.h"
#include <iostream>

class SignalLumineux{
    public:
        SignalLumineux();
        void setGreen();
        void setRed();
        char getColor();

    private:
        char color;
};

#endif // SIGNALLUMINEUX_H
