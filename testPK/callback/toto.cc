#include <stdio.h>
#include "toto.ph"
#include "titi.ph"

Toto::Toto()
{
  printf("CallBack: Object Toto on \"%s\"\n", POPGetHost());
  ident = 0;
}

Toto::~Toto()
{
  printf("CallBack: Destroying the object Toto...\n");
}

void Toto::SetIdent(int i)
{
  printf("CallBack: SetIdent(%d) on Toto...\n",i);
  ident=i;
}

int Toto::GetIdent()
{
   printf("CallBack: GetIdent on Toto, ident =%d\n",ident);

   Titi t;                 // create an object to call me back
   printf("ICI 1\n");
   this->SetIdent(222);    // test of "this"
   printf("ICI 2\n");
   t.ComputeIdent(*this);  // t is going to call me back
    printf("ICI 3\n");
  return(ident);          // ident has changed because of the call back
}

@pack(Toto);
