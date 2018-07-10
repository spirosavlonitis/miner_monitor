#include "hdr.h"
#include <unistd.h>
#include <pwd.h>

#define MAXTEMP	 81
#define MAXCHARS 1000
#define MINUTE	 60
#define MON_INRERVAL	5

#define COMMAND  "daemon mine_classic"
#define PIDOF 	 "pidof ethminer"

void recover(FILE *,char *);

int l;

int main(int argc, char *argv[])
{
	int temp;
	char path[MAXCHARS];
	FILE *lg;
	struct passwd *pwd;

	pwd = getpwuid(geteuid());
	snprintf(path, sizeof(path),"/home/%s/gpu_temp.md",pwd->pw_name);
	l = 1;

	for (; ;) {
		lg = fopen(path,"a");
		if (l)
			temp = logtemp(lg);

		if (WEXITSTATUS(system(PIDOF)) == 1)
			system(COMMAND);
		else if (temp >= MAXTEMP)
			recover(lg,PIDOF);
		
		fclose(lg);
		sleep(MON_INRERVAL*MINUTE);
	}
	exit(EXIT_SUCCESS);
}

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
