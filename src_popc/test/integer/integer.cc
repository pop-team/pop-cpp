#include <stdio.h>
#include "integer.ph"
#include <unistd.h>
#ifdef _PAROC_
#define printf rprintf
#endif


Integer::Integer(int wanted, int minp)
{
	rprintf("Object Integer on %s\n",(const char *)paroc_system::GetHost());
}

Integer::Integer(paroc_string machine)
{
        rprintf("Object Integer on %s\n",(const char *)paroc_system::GetHost());
}

Integer::~Integer()
{
  printf("Destroying the object...\n");
}

void Integer::Set(int val)
{
  data=val;
}
int Integer::Get()
{
  return data;
}
void Integer::Add(Integer &other)
{
  data+=other.Get();
}

void Integer::Add(Integer &o1, Integer &o2)
{
  data=o1.Get()+o2.Get();
}

int Integer::Sum(int x[5000])
{
  int t=0;

  for (int i=0;i<5000;i++) t+=x[i];
  DEBUG("SUM=%d",t);
  return t;
}

void Integer::Wait(int t)
{
  sleep(t);
}

@pack( Integer);
