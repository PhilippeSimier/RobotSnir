/* 
 * File:   main.c
 * Author: psimier
 *
 * Created on 29 novembre 2018, 15:30
 */

#include "robot.h"
#include "biblio_serie.h"

int main(int argc, char** argv) 
{
    int indice;
    int fdMoteur1, fdMoteur2;
    int fdSerie = 0;
    char message[255];

    // initialisation des moteurs, du telemètre et du port série    
    initialiserMoteurs(&fdMoteur1, &fdMoteur2);
    indice = initialiserTelemetre();
    fdSerie = ouvrirSerie("/dev/ttyS1");
    configurerSerie(fdSerie,57600);
    flush(fdSerie); // nettoyage du buffer serie
    
    envoyerMessage(fdSerie, "Robot SNIR dit hello! \n\r");
    do{
        recevoirMessage(fdSerie, message, ' ');
        
        if(!strncmp(message,"avant",5)){  
            printf("Marche avant \n");
            envoyerMessage( fdSerie, "Marche avant \n\r");
            fixerVitesse(64, AVANT, fdMoteur1, fdMoteur2); 
        }
        if(!strncmp(message,"arriere",7)){
            fixerVitesse(64, ARRIERE, fdMoteur1, fdMoteur2);
            envoyerMessage(fdSerie, "Marche arrière \n\r");
            
        }
        if(!strncmp(message,"gauche",6)){
            tourner(64, GAUCHE,fdMoteur1, fdMoteur2);
            envoyerMessage(fdSerie, "Tourne à gauche \n\r");
        }
        if(!strncmp(message,"droite",6)){
            tourner(64, DROITE,fdMoteur1, fdMoteur2);
            envoyerMessage(fdSerie, "Tourne à droite \n\r");
        }
        if(!strncmp(message,"stop",4)){
            arreter(fdMoteur1, fdMoteur2);
            envoyerMessage(fdSerie, "Stoper \n\r");
        }
        
    }
    while(strncmp(message,"bye",3));    
    envoyerMessage(fdSerie, "Robot SNIR dit bye bye! \n\r");
    system("/sbin/halt");
    return (EXIT_SUCCESS);
}

