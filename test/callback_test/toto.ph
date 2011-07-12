#ifndef _TOTO_PH
#define _TOTO_PH

parclass Toto
{
	classuid(1002);
public:
	Toto() @{od.url("localhost");};
	~Toto();

	seq sync void SetIdent(int i);
	conc sync int GetIdent();

private:
	int ident;
	Toto* POPC_this;
};

#endif
