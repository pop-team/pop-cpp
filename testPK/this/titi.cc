#include <stdio.h>
#include "titi.ph"

Titi::Titi()
{
  printf("this: Object Titi created on %s\n", POPGetHost());
}

Titi::~Titi()
{
  printf("this: Destroying the object Titi on %s...\n", POPGetHost());
}

void Titi::setToto(Toto& t)
{
  printf("this: SetToto(Toto &t) on Titi...\n");
  x = new Toto(t);
}

void Titi::callToto()
{
  printf("this: CallToto() on Titi...\n");
  printf("this: t->getIdent()=%d\n", x->getIdent());
}

@pack(Titi);
