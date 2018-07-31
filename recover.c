#include "hdr.h"

#define RCV_INTERVAL  10

void recover(FILE *lg,char *pidof)
{
	char	kill[MAXCHARS];
	long	timeout;

	timeout = RCV_INTERVAL * MINUTE;
	fputs("Entered recovery mode\n", (l) ? lg : stderr);
	snprintf(kill, sizeof(kill),"kill -9 $(%s)",pidof);
	system(kill);
	while (timeout > 0){
		if (l) {
			fprintf(lg,"Time until retry %ldmin\n",timeout/MINUTE);
			fflush(lg);
		}else
			fprintf(stderr,"Time until retry %ldmin\n",timeout/MINUTE);

		timeout -= MINUTE;
		sleep(MINUTE);
	}
}