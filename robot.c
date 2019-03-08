#include "robot.h"


void initialiserMoteurs(int *fdMoteur1, int *fdMoteur2){
    *fdMoteur1 = wiringPiI2CSetup(0x08);
    *fdMoteur2 = wiringPiI2CSetup(0x09);
}

int initialiserTelemetre(){
    int i ,model, revision;
    i = tofInit(0, 0x29, 1); // set long range mode (up to 2m)
        if (i != 1)
        {
                return -1; // problem - quit
        }
        printf("VL53L0X device successfully opened.\r\n");
        i = tofGetModel(&model, &revision);
        printf("Model ID - %d\r\n", model);
        printf("Revision ID - %d\r\n", revision);
    return 0;    
}

void fixerVitesse(int vitesse, direction sens, int fdMoteur1, int fdMoteur2){
    int masque = 0x00;
    switch (sens) {
        case AVANT :
            masque = 0x00;
            break;
        case ARRIERE : 
            masque = 0x80;
            break;
    }
    wiringPiI2CWrite(fdMoteur1, masque | vitesse );
    wiringPiI2CWrite(fdMoteur2, masque | vitesse );
}

void tourner(int vitesse, direction sens, int fdMoteur1, int fdMoteur2){
    int masque1 = 0x00, masque2 = 0x00;
    switch(sens){
        case DROITE :
            masque1 = 0x80;
            break;
        case GAUCHE :
            masque2 = 0x80;
            break;
    }
    wiringPiI2CWrite(fdMoteur1, masque1 | vitesse );
    wiringPiI2CWrite(fdMoteur2, masque2 | vitesse );
    
}


void arreter(int fdMoteur1, int fdMoteur2){
    wiringPiI2CWrite(fdMoteur1, 0);
    wiringPiI2CWrite(fdMoteur2, 0);    
}

int lireDistance(){
    return tofReadDistance();
}

