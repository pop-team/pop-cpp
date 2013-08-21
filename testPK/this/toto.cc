#include <stdio.h>
#include "toto.ph"
#include "titi.ph"

Toto::Toto()
{
  printf("this: Object Toto on \"%s\"\n", POPGetHost());
  ident = -1;
}

Toto::~Toto()
{
  printf("this: Destroying the object Toto...\n");
}

void Toto::work()
{
  Titi t;
  t.setToto(*this);
  /*this->*/setIdent(10);
  t.callToto();
}

void Toto::setIdent(int i)
{
  ident = i;
}

int Toto::getIdent()
{
  return ident;
}

@pack(Toto);
