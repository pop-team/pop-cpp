/** 
 * @author  P.Kuonen
 * @date    2012.09.04
 * This program tests passing (sequential) object as parameter
 */
#include <stdio.h>
#include "ParObject.ph"
#include "data.h"
#include "classdata.h"

int main(int argc, char** argv)
{
  printf("\nClassparam: Starting test..\n");

  int v;
  ClassData b;
  Data a;
  ParObject o("localhost");

  a.SetInternalData(10);
  b.SetInternalData(a);
  b.SetMyData(100);
  o.SetData(b);

  printf("Classparam: Current object internal data = %d, %d\n",
          o.GetData().GetMyData(),
          o.GetData().GetInternalData().GetInternalData());
  
  a.SetInternalData(20);
  b.SetInternalData(a);
  b.SetMyData(200);
  o.SetData(b);

  v = o.GetData().GetInternalData().GetInternalData();
  printf("Classparam: Current object internal data = %d, %d\n",
          o.GetData().GetMyData(),
          o.GetData().GetInternalData().GetInternalData());

  a.SetInternalData(0);
  b.SetInternalData(a);
  b.SetMyData(0);
  printf("Classparam: Current b internal data = %d, %d\n",
          b.GetMyData(), b.GetInternalData().GetInternalData());

  o.Get(b);

  if ((v==20) && (b.GetMyData()==200) &&
      (b.GetInternalData().GetInternalData()==20))
  {
    printf("Classparam: test succeeded, destroying objects...\n");
    return 0;
  }
  else
  {
    printf("Classparam: Test failed, bad value transmission\n");
    return 1;
  }
  return 0;
}

