#include <stdio.h>
#include "toto.ph"
#include "titi.ph"

Toto::Toto()
{
	POPC_this = new Toto(GetAccessPoint());
	printf("CallBack: Object Toto on localhost\n");
	ident = 0;
}

Toto::~Toto()
{
	printf("CallBack: Destroying the object Toto...%d\n",ident);
}

void Toto::SetIdent(int i)
{
	printf("CallBack: SetIdent(%d) on Toto...\n",i);
	ident=i;
}

int Toto::GetIdent()
{
	printf("CallBack: GetIdent on Toto, ident =%d\n",ident);
	Titi* t = new Titi;
	POPC_this->SetIdent(222);
	t->ComputeIdent(*POPC_this);
	return(ident);
}

@pack(Toto);
