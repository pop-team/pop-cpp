/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: benchmark code for MFlops (used by JobMgr)
 */

#include <time.h>
#include <paroc_utils.h>
#include "timer.h"


#ifndef MATRIXSIZE
#define MATRIXSIZE 400
#endif

void matrix_mult(float a[MATRIXSIZE][MATRIXSIZE], float b[MATRIXSIZE][MATRIXSIZE], float c[MATRIXSIZE][MATRIXSIZE])
{
	for (int j=0;j<MATRIXSIZE;j++)
		for (int i=0;i<MATRIXSIZE;i++)
		{
			float tmp=0;
			float *a1=a[i];
			float *b1=b[0]+j;
			for (int k=0;k<MATRIXSIZE;k++,a1++, b1+=MATRIXSIZE) tmp+=(*b1)*(*a1);
			c[i][j]=tmp;
		}
}

float paroc_utils::benchmark_power()
{
	float a[MATRIXSIZE][MATRIXSIZE], b[MATRIXSIZE][MATRIXSIZE], c[MATRIXSIZE][MATRIXSIZE];
	for (int i=0;i<MATRIXSIZE;i++)
		for (int j=0;j<MATRIXSIZE;j++) a[i][j]=b[i][j]=1;

	Timer timer;
	timer.Start();
	matrix_mult(a,b,c);
	double t=timer.Elapsed();
	if (t==0) t=1.0E-10;
	return (6.0*MATRIXSIZE*MATRIXSIZE*MATRIXSIZE)/1.0E6/t;
}
