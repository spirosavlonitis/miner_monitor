#include "hdr.h"
#include <pwd.h>
#include <string.h>

static void readargs(int argc, char **, char **);

int main(int argc, char *argv[])
{
	int temp;
	char path[MAXCHARS], *command = NULL;
	FILE *fp;
	struct passwd *pwd;
	
	l = 0;

	readargs(argc,argv, &command);
	if (command == NULL)
		command = strdup(DEF_COMMAND);
	
	pwd = getpwuid(geteuid());
	snprintf(path, sizeof(path),"/home/%s/gpu_temp.txt",pwd->pw_name);

	for (; ;) {
		fp = (l) ? fopen(path,"a") : stdout;

		temp = logtemp(fp);

		if (WEXITSTATUS(system(PIDOF)) == 1){
			fprintf(fp, "%s\n", "miner down");
			fflush(fp);
			system(command);
		}else if (temp >= MAXTEMP)
			recover(fp,PIDOF);
		
		if (l)
			fclose(fp);
		sleep(MON_INRERVAL*MINUTE);
	}
	exit(EXIT_SUCCESS);
}

static void readargs(int argc, char **argv, char **command)
{
	char	c;
	int		i;
	while ( --argc > 0) 
		if ( (c = **++argv ) == '-'){
			c = (*argv)[1];
			switch (c) {
				case 'l':					// log file
					l = 1;
					break;
				case 'c':
					++argv;
					--argc;
					*command = strdup(*argv);
					break;
				default:
					err_quit("uknown option %c", c);
					break;
			}
		}
}