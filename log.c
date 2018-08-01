#include "hdr.h"
#include <string.h>
#include <time.h>

#define MAXGPU	100

static int gettemp(int *temps)
{
	int	 i, j, maxtemp;
	char temperature[10];
	FILE *fp;
	
	fp = popen("nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader", "r");
	j = 0;
	for (i = 0; (temperature[i] = fgetc(fp)) != EOF ; ++i)
		if (temperature[i] == '\n') {
			temperature[i] = '\0';
			temps[j++] = atoi(temperature);
			i = -1;
		}
	pclose(fp);

	maxtemp = 0;
	for (i = 0; temps[i] != -1  ; ++i)
		if (maxtemp == 0)
			maxtemp = temps[i];
		else if (temps[i] > maxtemp)
			maxtemp = temps[i];
	return maxtemp;
}

#define Green	"\033[0;32m"
#define White	"\x1b[0m"

static void color_log(FILE *fp,int i,int *temps)
{
	if (*temps < 70)
		fprintf(fp,"gpu%d:%s%d%s%s", i, Green, *temps, White,(*(temps+1) == -1) ?  ", miner pid: " : ", ");

}

int logtemp(FILE *fp)
{
	char	buf[MAXCHARS];
	int 	maxtemp, i, temps[MAXGPU];
	time_t	now;

	time(&now);
	strcpy(buf, ctime(&now));
	buf[strlen(buf)-1] = '\0';
	
	for (i = 0; i < MAXGPU ; ++i)
		temps[i] = -1;
	maxtemp = gettemp(temps);
	fprintf(fp, "%s  ", buf);
	for (i = 0; temps[i] != -1; ++i)
		if (l == 0)
			color_log(fp, i, temps+i);
		else
		  fprintf(fp,"gpu%d:%d%s", i, temps[i], (temps[i+1] == -1) ?  ", miner pid: " : ", ");

	fflush(fp);
	return maxtemp;
}