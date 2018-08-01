#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXTEMP	 81
#define MAXCHARS 1000
#define MINUTE	 60
#define MON_INRERVAL	5

#define COMMAND  "daemon mine_classic"
#define PIDOF 	 "pidof ethminer"


void recover(FILE *,char *);
int logtemp(FILE *);
void err_quit(char *, ...);

int l;