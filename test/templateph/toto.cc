#include <stdio.h>
#include "toto.ph"

Toto::Toto()
{
	printf("Template: Object Toto on localhost\n");
	t.SetIdent(0);
}

Toto::Toto(POPString machine)
{
	printf("Template: Object Toto on %s\n"/*,(const char *)POPSystem::GetHost()*/);
	t.SetIdent(1);
}

Toto::~Toto()
{
	printf("Template: Destroying the object toto...%d\n", t.GetIdent());
}

void Toto::SetIdent(int id)
{
	printf("Template: SetIdent on Toto object %d\n",id);
	t.SetIdent(id);
}
int Toto::GetIdent()
{
	printf("Template: GetIdent on Toto object %d\n",t.GetIdent());
	return t.GetIdent();
}

@pack(Toto);

