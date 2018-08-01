#include "hdr.h"
#include <pwd.h>

static void readargs(int argc, char **);

int main(int argc, char *argv[])
{
	int temp;
	char path[MAXCHARS];
	FILE *fp;
	struct passwd *pwd;
	
	l = 0;

	readargs(argc,argv);

	pwd = getpwuid(geteuid());
	snprintf(path, sizeof(path),"/home/%s/gpu_temp.md",pwd->pw_name);

	for (; ;) {
		fp = (l) ? fopen(path,"a") : stdout;

		temp = logtemp(fp);

		if (WEXITSTATUS(system(PIDOF)) == 1)
			system(COMMAND);
		else if (temp >= MAXTEMP)
			recover(fp,PIDOF);
		
		if (l)
			fclose(fp);

		sleep(MON_INRERVAL*MINUTE);
	}
	exit(EXIT_SUCCESS);
}

static void readargs(int argc, char **argv)
{
	char	c;
	int		i;

	while ( --argc > 0) 
		if ( (c = **++argv ) == '-')
			for (i = 1; (c = (*argv)[i]) ; ++i)
				switch (c) {
					case 'l':
						l = 1;
						break;
					default:
						err_quit("uknown option %c", c);
						break;
				}
}