#include "hdr.h"
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

static void setdate(int *year,int *mon,int *mday,int *hour,int *min,int *sec)
{
	time_t	smp;
	struct tm *now;
	time(&smp);
	now = localtime(&smp);
	*year = now->tm_year+1900, *mon = now->tm_mon+1, *mday = now->tm_mday;
	*hour = now->tm_hour, *min = now->tm_min, *sec = now->tm_sec;
}

int logtemp(FILE *lg)
{
	int year,mon,mday,hour,min,sec,temp;
	
	temp = gettemp();
	setdate(&year,&mon,&mday,&hour,&min,&sec);
	
	fprintf(lg,"%d-%d-%d %d%s%d%s%d:",year,mon,mday,hour,(min > 9) ? ":" : ":0",min,(sec > 9) ? ":" : ":0" ,sec);
	fprintf(lg,"\t%d\n",temp);

	return temp;
}