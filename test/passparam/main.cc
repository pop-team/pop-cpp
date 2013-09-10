#include "POPCobject.ph"
#include "data.h"
#include "structdata.h"
#include <stdio.h>
#include <unistd.h>
int main(int argc, char** argv)

{
   printf("\nPassParam: Starting test..\n");

   POPCobject o1, o2;
   StructData d;
   Data i;
   int tab[10];

   d.SetMyData(10);
   i.SetInternalData(20);
   d.SetInternalData(i);

   printf("PassParam: call to m2\n"); sleep(1);
   o1.m2(o2);
   printf("PassParam: call to m4\n"); sleep(1);
   o1.m4(d);
   printf("PassParam: call to m300\n"); sleep(1);
   o1.m300(d);
   printf("PassParam: call to m400\n"); sleep(1);
   o1.m400(d);
   printf("PassParam: call to m20\n"); sleep(1);
   o2=o1.m20();
   o2.m300(d);
   printf("PassParam: call to m12\n"); sleep(1);
   d=o1.m12(11);

   if ((d.GetMyData()==11) && (d.GetInternalData().GetInternalData()==0))
   {
     printf("\nPassParam: test succeeded, destroying objects...\n");
     return 0;
   }
   else
   {
     printf("\nPassParam: ...Test failed (%d,%d)\n",
               d.GetMyData(), d.GetInternalData().GetInternalData());
     return 1;
   }
} 
  
