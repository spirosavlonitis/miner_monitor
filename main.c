#include "hdr.h"
#include <unistd.h>
#include <pwd.h>

#define MAXTEMP	 81
#define MAXCHARS 1000
#define MINUTE	 60
#define DEAULT   "mine_classic"

void recover(FILE *,char *);

int main(int argc, char *argv[])
{
	int temp;
	char path[MAXCHARS],command[MAXCHARS],*pidof;
	FILE *lg;
	struct passwd *pwd;

	sprintf(command,"daemon %s",(argc < 2) ? DEAULT : *(argv+1));
	pidof = (argc < 2) ? "pidof ethminer" : "pidof miner";
	pwd = getpwuid(geteuid());
	sprintf(path,"/home/%s/gpu_temp.md",pwd->pw_name);

	while (1) {
		lg = fopen(path,"a");
		temp = logtemp(lg);
		if (WEXITSTATUS(system(pidof)) == 1)
			system(command);
		else if (temp >= MAXTEMP)
			recover(lg,pidof);
		fclose(lg);
		sleep(5*MINUTE);
	}
	exit(0);
}

void recover(FILE *lg,char *pidof)
{
	char	kill[MAXCHARS];
	long	timeout;

	timeout = 10 * MINUTE;
	fputs("Entered recovery mode\n",lg);
	fputs("Entered recovery mode\n",stderr);
	sprintf(kill,"kill -9 $(%s)",pidof);
	system(kill);
	while (timeout > 0){
		fprintf(lg,"Time until retry %ldmin\n",timeout/MINUTE);
		fflush(lg);
		fprintf(stderr,"Time until retry %ldmin\n",timeout/MINUTE);
		timeout -= MINUTE;
		sleep(MINUTE);
	}
}
