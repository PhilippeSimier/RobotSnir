/* 
 * File:   robot.h
 * Author: psimier
 *
 * Created on 30 novembre 2018, 14:17
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <stdio.h>
#include <stdlib.h>
#include <wiringPiI2C.h>   
#include "unistd.h"        // Pour inclure sleep
#include <tof.h>         // time of flight sensor library

typedef enum {AVANT, ARRIERE, DROITE, GAUCHE}direction;

void initialiserMoteurs(int *fdMoteur1, int *fdMoteur2);
void fixerVitesse(int vitesse, direction sens, int fdMoteur1, int fdMoteur2);

void arreter(int fdMoteur1, int fdMoteur2);
void tourner(int vitesse, direction sens, int fdMoteur1, int fdMoteur2);

int initialiserTelemetre();
int lireDistance();

#endif /* ROBOT_H */

