#include "hdr.h"
#include <unistd.h>
#include <pwd.h>

#define MAXTEMP	 81
#define MAXCHARS 1000
#define MINUTE	 60
#define MON_INRERVAL	5

#define COMMAND  "mine_zec"
#define PIDOF 	 "pidof miner"

void recover(FILE *,char *);

int l;

int main(int argc, char  *argv[])
{
	int temp;
	char path[MAXCHARS];
	pid_t	parent;
	FILE *lg;
	struct passwd *pwd;

	pwd = getpwuid(geteuid());
	snprintf(path, sizeof(path),"/home/%s/gpu_temp.md",pwd->pw_name);
	l = 1;
	parent = fork();

	for (; ;) {

		if (parent){	/* parent process monitors temperature */
			if (l)
				lg = fopen(path,"a");
			temp = logtemp((l) ? lg : stderr);
			
			if (parent && temp >= MAXTEMP)
				recover(lg,PIDOF);
			if (l)
				fclose(lg);
		}else if (parent == 0 &&  WEXITSTATUS(system(PIDOF)) == 1) /* fork monitors connection status */
					system(COMMAND);
			
		sleep(MINUTE);
	}
	exit(EXIT_SUCCESS);
}

#define RCV_INTERVAL  10

void recover(FILE *fp,char *pidof)
{
	char	kill[MAXCHARS];
	long	timeout;

	timeout = RCV_INTERVAL * MINUTE;
	fputs("Entered recovery mode\n", fp);
	snprintf(kill, sizeof(kill),"kill -9 $(%s)",pidof);
	system(kill);
	while (timeout > 0){
		fprintf(fp,"Time until retry %ldmin\n",timeout/MINUTE);
		fflush(fp);

		timeout -= MINUTE;
		sleep(MINUTE);
	}
}
