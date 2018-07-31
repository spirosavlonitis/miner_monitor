#include "hdr.h"
#include <pwd.h>

static void readargs(int argc, char **);

int main(int argc, char *argv[])
{
	int temp;
	char path[MAXCHARS];
	FILE *lg;
	struct passwd *pwd;
	
	l = 0;

	readargs(argc,argv);

	pwd = getpwuid(geteuid());
	snprintf(path, sizeof(path),"/home/%s/gpu_temp.md",pwd->pw_name);

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


static void readargs(int argc, char **argv)
{
	char	c;
	int		i;

	while ( --argc > 0 && (c = **++argv ) ) {
		if (c == '-')
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
	
}