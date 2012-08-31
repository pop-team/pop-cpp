#include <stdio.h>

#include "ParObject.ph"
#include "heritdata.h"

int main(int argc, char** argv)
{
  printf("\nHeritparam3: Starting test..\n");

  int v;
  HeritData a;
  Data b;
  ParObject o;

  b.SetInternalData(11);

  a.SetInternalData(10);
  a.SetMyData(100);
  a.SetMyData(256, 3.1415926);
  o.SetData(a, a);

  printf("Heritparam3: Current internal data =%d\n", o.GetData().GetInternalData());
  printf("Heritparam3: My current data =%d\n", o.GetData().GetMyData());
  printf("Heritparam3: My current data[256]=%f\n", o.GetData().GetMyData(256));
  printf("Heritparam3: a.InternalData=%d\n", a.GetInternalData());
  
  a.SetInternalData(20);
  a.SetMyData(200);
  o.SetData(a, b);

  v = o.GetData().GetInternalData();
  printf("Heritparam3: Current internal data =%d\n", v);
  printf("Heritparam3: My current data =%d\n", o.GetData().GetMyData());
  printf("Heritparam3: b.InternalData=%d\n", b.GetInternalData());

  if ((v==20) && (b.GetInternalData()==13) && (a.GetMyData()==200))
    printf("Heritparam3: test succeeded, destroying objects...\n");
  else
    printf("Heritparam3: Test failed, bad value transmission\n");
 
  return 0;
}

