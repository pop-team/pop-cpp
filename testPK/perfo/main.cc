#include <stdio.h>
#include <stdlib.h>
#include <timer.h>
#include "bytedata.h"
#include "POPCobject.ph"

#define size 1000000
#define maxI 100

int main(int argc, char** argv)

{	  
  printf("\nSTART program\n\n");
  POPCobject anObject;
  ByteData myData;
  char* myBytes = (char*)malloc(size);

  myData.theData = (char*)malloc(size);
  myData.n = size;

  printf("Launch calls\n\n");
  Timer timer;

  double call1, call2, call3, call4;
  float flops;

  timer.Start(); //----------------------------------------- Start Timer
  for (int i=0; i<maxI; i++)
    anObject.sendBytesSyncSeq(myBytes, size);
  call1 = timer.Elapsed();  // ---------------------- call1 Time
  timer.Stop(); timer.Reset();
  call1 = (maxI*size)/(call1*1.0e6);

  timer.Start();
  for (int i=0; i<maxI; i++)
    anObject.sendDataSyncSeq(myData);
  call2 = timer.Elapsed();  // ---------------------- call2 Time
  timer.Stop();timer.Reset();
  call2 = (maxI*size)/(call2*1.0e6);

  timer.Start();
  for (int i=0; i<maxI; i++)
    anObject.sendBytesAsyncSeq(myBytes, size);
  call3 = timer.Elapsed();  // ---------------------- call3 Time
  timer.Stop();timer.Reset();
  call3 = (maxI*size)/(call3*1.0e6);

  timer.Start();
  for (int i=0; i<maxI; i++)
    anObject.sendDataAsyncSeq(myData);
  call4 = timer.Elapsed();  // ---------------------- call4 Time
  timer.Stop();
  call4 = (maxI*size)/(call4*1.0e6);

  flops = anObject.computeFlops(0.3333, 0.6666);
  
  printf("\nBandwith call1, call2, call3, call4 = %g %g %g %g MBytes/sec\n\n",
            call1, call2, call3, call4);
  printf("Processor speed = %f Mflops\n\n", flops);


  printf("\nEND of program\n\n");
  return 0;
}
