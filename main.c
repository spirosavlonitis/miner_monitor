#include "hdr.h"
#include <pwd.h>
#include <string.h>

static void readargs(int argc, char **, char **);
static void help_message(void);

int main(int argc, char *argv[])
{
	int temp;
	char path[MAXCHARS], *command = NULL, daemon[MAXCHARS];
	FILE *fp;
	struct passwd *pwd;
	
	l = 0;

	readargs(argc,argv, &command);
	if (command == NULL)
		command = strdup(DEF_COMMAND);
	
	if (l) {
		pwd = getpwuid(geteuid());
		snprintf(path, sizeof(path),"/home/%s/gpu_temp.txt",pwd->pw_name);
	}

	snprintf(daemon, MAXCHARS, "daemon %s", command);
	for (; ;) {
		fp = (l) ? fopen(path,"a") : stdout;

		temp = logtemp(fp);

		if (WEXITSTATUS(system(PIDOF)) == 1){
			fprintf(fp, "%s\n", "miner down");
			fflush(fp);
			system(daemon);
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
	int		i = argc;
	while (--argc > 0) 
		if ( (c = **++argv) == '-'){
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
				case '-':
					if (strcmp("help", *argv+2) == 0)
						help_message();
					break;
				default:
					err_quit("uknown option %c", c);
					break;
			}
		}
}


static void help_message()
{
	char *message = "\
Example:\n    miner_monitor.out -c some_command\n\
\n\
Options:\n\
	-c\tsets the mining command to deamonize\n\t\tdefault value is mine_eth\n\n\
	-l\tcreates a log file at the user's home directory\n\t\tnamed gpu_temp.txt\n\n\
	--help\tprints this message\n\
";

	printf("%s\n", message);


	exit(0);
}