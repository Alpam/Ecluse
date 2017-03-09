/*
 * =====================================================================================
 *
 *       Filename: signallumineux.cpp
 *
 *    Description: classe représentant les feux
 *
 *         Author:  Paul Robin (), paul.robin@etu.unistra.fr
 *         Author:  Arthur Delrue (), arthur.delrue@etu.unistra.fr
 *
 * =====================================================================================
 */

#include "signallumineux.h"

/**
 * @brief SignalLumineux::SignalLumineux
 *        constructeur, un feu est initialisé sur rouge
 */
SignalLumineux::SignalLumineux()
{
    color = 'R';
}

/**
 * @brief SignalLumineux::setGreen
 *        passe le feu au vert
 */
void SignalLumineux::setGreen()
{
    if (color != 'V') color = 'V';
}

/**
 * @brief SignalLumineux::setRed
 *        passe le feu au rouge
 */
void SignalLumineux::setRed() {
    if (color != 'R') color = 'R';
}

/**
 * @brief SignalLumineux::getColor
 * @return
 *        retourne la couleur du feu
 */
char SignalLumineux::getColor() {
    return color;
}

