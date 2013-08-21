#include <stdio.h>
#include <timer.h>
#include "POPCobject.ph"

#define maxI 100000
#define maxJ 10000

POPCobject::POPCobject()
{
  printf("POPCobject created on machine \"%s\"\n", POPGetHost()); 
}

POPCobject::~POPCobject()
{
  //printf("POPCobject on machine \"%s\" is being destroyed\n", POPGetHost()); 
}

void POPCobject::sendBytesAsyncSeq(char* b, int n)
{
 // printf("POPCobject on machine \"%s\" has recieved (async) %d bytes\n",POPGetHost(), n);
}

void POPCobject::sendBytesSyncSeq(char* b, int n)
{
  //printf("POPCobject on machine \"%s\" has recieved  (sync) %d bytes\n",POPGetHost(), n);
}

void POPCobject::sendDataAsyncSeq(ByteData b)
{
  //printf("POPCobject on machine \"%s\" has recieved %d data\n",POPGetHost(), b.n);
}

void POPCobject::sendDataSyncSeq(ByteData b)
{
  //printf("POPCobject on machine \"%s\" has recieved %d data\n",POPGetHost(), b.n);
}

float POPCobject::computeFlops(float a, float b)
{
  Timer timer;
  double computeTime;
  float x = 1.0;
  timer.Start();
  for (int i=0; i<maxI; i++)
    for (int j=0; j<maxJ; j++)
      x = x * ((a/x)+(b/x));
      //x=x*b;
  computeTime = timer.Elapsed();
  timer.Stop();
  printf("X = %f, time=%g sec\n", x, computeTime);
  return (maxI*4.0*maxJ)/((float)computeTime*1.0e6);
}


@pack(POPCobject);
