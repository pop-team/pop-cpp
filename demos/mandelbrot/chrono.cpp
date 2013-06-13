#include <stdio.h>
#include <string.h>
#include "chrono.h"


Chronometer::Chronometer(int nlaps)
{
	lapTable = new double[nlaps];
	textTable = new char *[nlaps];
	lapN = 0;
	maxN = nlaps-1;
	struct timeval tv;
	gettimeofday(&tv, 0);
	zero = (double) tv.tv_usec / 1e6 + tv.tv_sec;
	toSkip = 0;
}


void Chronometer::skip(int s)
{
	toSkip = s;
}


void Chronometer::lap(const char *text)
{
	if (toSkip>0) {
		toSkip --;
		return;
	}
	struct timeval tv;
	gettimeofday(&tv, 0);
	lapTable[lapN] = (double) tv.tv_usec / 1e6 + tv.tv_sec - zero;
	textTable[lapN] = strdup(text);
	if (lapN < maxN)
		lapN ++;
}


void Chronometer::lap(const char *text, int i)
{
	char s[10000];
	sprintf(s, text, i);
	lap(s);
}


void Chronometer::dump(const char *fn)
{
	FILE *f = fopen(fn, "w");
	for (int i=0; i<lapN; i++)
		fprintf(f, "%12.4lf %s\n", lapTable[i], textTable[i]);
	fclose(f);
}

void Chronometer::dump()
{
	for (int i=0; i<lapN; i++)
		printf("%12.4lf %s\n", lapTable[i], textTable[i]);
}
