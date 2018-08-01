#include "hdr.h"

#define RCV_INTERVAL  10

void recover(FILE *fp,char *pidof)
{
	char	kill[MAXCHARS];
	long	timeout;

	timeout = RCV_INTERVAL * MINUTE;
	fputs("Entered recovery mode\n", fp);
	snprintf(kill, sizeof(kill),"kill -9 $(%s)", pidof);
	system(kill);

	while (timeout > 0){
		fprintf(stderr,"Time until retry %ldmin\n",timeout/MINUTE);
		if (l) 
			fflush(fp);
		timeout -= MINUTE;
		sleep(MINUTE);
	}
}