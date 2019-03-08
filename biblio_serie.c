#include "biblio_serie.h"

int ouvrirSerie(const char device[]){
    int fd = -1;
    fd = open(device, O_RDWR | O_NOCTTY);
    if ( fd == -1 ) {
        printf("pb ouverture: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return fd;
}


void configurerSerie (int fd, const int baud){
    
    struct termios term;
    speed_t myBaud;

    switch (baud){
    	case     50:        myBaud =     B50 ; break ;
    	case     75:        myBaud =     B75 ; break ;
    	case    110:        myBaud =    B110 ; break ;
    	case    134:        myBaud =    B134 ; break ;
    	case    150:        myBaud =    B150 ; break ;
    	case    200:        myBaud =    B200 ; break ;
    	case    300:        myBaud =    B300 ; break ;
    	case    600:        myBaud =    B600 ; break ;
    	case   1200:        myBaud =   B1200 ; break ;
    	case   1800:        myBaud =   B1800 ; break ;
    	case   2400:        myBaud =   B2400 ; break ;
    	case   4800:        myBaud =   B4800 ; break ;
    	case   9600:        myBaud =   B9600 ; break ;
    	case  19200:        myBaud =  B19200 ; break ;
    	case  38400:        myBaud =  B38400 ; break ;
    	case  57600:        myBaud =  B57600 ; break ;
    	case 115200:        myBaud = B115200 ; break ;
    	case 230400:        myBaud = B230400 ; break ;

    	default:
      	    myBaud =   B9600;
    }

    tcgetattr(fd, &term);

    /* mode RAW, pas de mode canonique, pas d'echo */
    term.c_iflag = IGNBRK;
    term.c_lflag = 0;
    term.c_oflag = 0;


    /* 1 caractère suffit */
    term.c_cc[VMIN] = 1;

    /* Donnée disponible immédiatement */
    term.c_cc[VTIME] = 0;

    /* Inhibe le controle de flux XON/XOFF */
    term.c_iflag &= ~(IXON|IXOFF|IXANY);

    /* 8 bits de données, pas de parité */
    term.c_cflag &= ~(PARENB | CSIZE);
    term.c_cflag |= CS8;
    /* vitesse de la transmission */
    if(cfsetispeed(&term, myBaud) < 0 || cfsetospeed(&term, myBaud) < 0) {
       printf("Erreur configuration\n");
    }
    
    tcsetattr(fd, TCSANOW, &term);

    // play with DTR
	int iFlags;

   // turn off DTR
    iFlags = TIOCM_DTR;
    ioctl(fd, TIOCMBIC, &iFlags);
}

void flush (const int fd){
  tcflush (fd, TCIOFLUSH);
}

void envoyerUnCaratere (const int fd, const unsigned char c){
  write (fd, &c, 1) ;
}

void envoyerMessage (const int fd, const char *s){
  write (fd, s, strlen (s)) ;
}

void recevoirMessage(const int fd, char *message, char fin){
    char buffer;
    int nb_lus = 0;

    do{
      	nb_lus = read(fd, &buffer, 1);     // réception d'un caractère
      	if (nb_lus < 0) {
		printf("Erreur de réception\n");
		exit(EXIT_FAILURE);
      	}     	
	*message = buffer;
        message++;
    }
    while (buffer != fin);   // tant que pas un  caratère fin 
    *message = '\0';         // fin de chaine de caratère
}




