/* 
 * File:   biblio_serie.h
 * Author: psimier
 *
 * Created on 7 décembre 2018, 08:48
 */

#ifndef BIBLIO_SERIE_H
#define BIBLIO_SERIE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>


int  ouvrirSerie(const char *device);
void configurerSerie (int fd, const int baud);
void recevoirMessage(int fd, char *message, char fin);
void flush (const int fd);
void envoyerCaractere (const int fd, const unsigned char c);
void envoyerMessage (const int fd, const char *s);

#endif 

