#include <stdio.h>
#include "titi.ph"

Titi::Titi()
{
  printf("CallBack: Object Titi created on %s\n", POPGetHost());
  ident = -1;
}

Titi::~Titi()
{
  printf("CallBack: Destroying the object Titi...\n");
}

void Titi::SetIdent(int i)
{
    printf("CallBack: SetIdent() on Titi...\n");

    ident=i;
}

void Titi::ComputeIdent(Toto &t)
{
  printf("CallBack: ComputeIdent() on Titi...\n");
  t.SetIdent(ident);
}

@pack(Titi);
