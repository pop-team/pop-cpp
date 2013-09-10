#include <stdio.h>

#include "ParObject.ph"
#include "data.h"

int main(int argc, char** argv)
{

  printf("\nStructparam: Starting test..\n");

  int v;
  StructData b;
  Data a;
  ParObject o("localhost");

  a.theData = 10;
  b.theData = a;
  b.myData  = 100;
  o.SetData(b);

  printf("Structparam: Current object internal data = %d, %d\n",
          o.GetData().myData,
          o.GetData().theData.theData);
  
  a.theData = 20;
  b.theData = a;
  b.myData = 200;
  o.SetData(b);

  v = o.GetData().theData.theData;
  printf("Structparam: Current object internal data = %d, %d\n",
          o.GetData().myData,
          o.GetData().theData.theData);

  a.theData =0;
  b.theData = a;
  b.myData = 0;
  printf("Structparam: Current b internal data = %d, %d\n",
          b.myData, b.theData.theData);

  o.Get(b);

  if ((v==20) &&
      (b.myData==200) &&
      (b.theData.theData==20))
  {
    printf("Structparam: test succeeded, destroying objects...\n");
    return 0;
  }
  else
  {
    printf("Structparam: Test failed, bad value transmission\n");
    return 1;
  }
}

