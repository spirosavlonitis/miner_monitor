#include "hdr.h"



void recover(FILE *fp,char *pidof)
{
	char	kill[MAXCHARS];
	long	timeout;

	timeout = RCV_INTERVAL * MINUTE;
	fputs("Entered recovery mode\n", fp);
	snprintf(kill, sizeof(kill),"kill -9 $(%s)", pidof);
	system(kill);

	while (timeout > 0){
		fprintf(fp, "Time until retry %ldmin\n", timeout/MINUTE);
		fflush(fp);
		timeout -= MINUTE;
		sleep(MINUTE);
	}
}