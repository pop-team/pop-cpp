#include <stdio.h>
#include <stdarg.h>
#include "debug.h"

#ifndef NDEBUG

#ifndef __GNUC__

char *thisfile_debug;
int thisline_debug;

int printdebug(const char *format,...)
{
	fprintf(stderr,"DEBUG[%s:%d]",thisfile_debug,thisline_debug);
	va_list ap;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	fprintf(stderr,"\n");
	va_end(ap);
	fflush(stderr);
	return 1;
}

int printdebugif(int cond, const char *format,...)
{
	if (cond)
	{
		fprintf(stderr,"DEBUGIF[%s:%d]",thisfile_debug,thisline_debug);
		va_list ap;
		va_start(ap, format);
		vfprintf(stderr, format, ap);
		fprintf(stderr,"\n");
		va_end(ap);
		fflush(stderr);
		return 1;
	}
	return -1;
}

#endif

#endif
