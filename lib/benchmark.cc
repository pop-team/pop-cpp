#include <time.h>
#include <paroc_utils.h>

#ifndef MATRIXSIZE
#define MATRIXSIZE 400
#endif

float paroc_utils::benchmark_power()
{
  float a[MATRIXSIZE][MATRIXSIZE], b[MATRIXSIZE][MATRIXSIZE], c[MATRIXSIZE][MATRIXSIZE];
  
  unsigned cl1=clock();

  for (int j=0;j<MATRIXSIZE;j++)
    for (int i=0;i<MATRIXSIZE;i++)     
      {
        float tmp=0;
        float *a1=a[i];
	float *b1=b[0]+j;
        for (int k=0;k<MATRIXSIZE;k++,a1++, b1+=MATRIXSIZE) tmp+=(*b1)*(*a1);
        c[i][j]=tmp;
      }
  unsigned cl2=clock()-cl1;
  return ((1.0*MATRIXSIZE*MATRIXSIZE*MATRIXSIZE*6.0)/(cl2*1.0E6/CLOCKS_PER_SEC));

}
