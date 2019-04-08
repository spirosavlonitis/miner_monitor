#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXTEMP	 81
#define MAXCHARS 1000
#define MINUTE	 60
#define MON_INRERVAL	5
#define RCV_INTERVAL 10


#define DEF_COMMAND  "daemon mine_eth"
#define PIDOF 		 "pidof ethminer"

typedef struct monitor
{
	int 	max_temp;
} Monitor;


void recover(FILE *,char *);
int logtemp(FILE *);
void err_quit(char *, ...);

int l;