#include "hdr.h"
#include <string.h>
#include <time.h>

static int gettemp()
{
	int	 i;
	char temperature[10];
	FILE *fp;
	fp = popen("nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader","r");
	for (i = 0; (temperature[i] = fgetc(fp)) != '\n' ; ++i)
		;
	temperature[i] = '\0';
	pclose(fp);
	return atoi(temperature);
}

int logtemp(FILE *fp)
{
	char	buf[MAXCHARS];
	int 	temp;
	time_t	now;
	
	time(&now);
	temp = gettemp();
	strcpy(buf, ctime(&now));
	buf[strlen(buf)-1] = '\0';

	fprintf(fp, "%s", buf);
	fprintf(fp,"\t%d\n",temp);

	return temp;
}