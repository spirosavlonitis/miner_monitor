#include "hdr.h"
#include "stdarg.h"


void err_quit(char *fmt, ...)
{
	va_list		args;

	va_start(args, fmt);
	vfprintf(stderr,fmt, args);
	fprintf(stderr, "\n");
	va_end(args);

	exit(EXIT_FAILURE);
}