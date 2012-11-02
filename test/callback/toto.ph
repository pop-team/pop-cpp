#ifndef _TOTO_PH
#define _TOTO_PH

parclass Toto          
{

classuid(1002);

public:
	Toto() @{ od.node(1); od.executable("./toto.obj"); };
	~Toto();

	seq sync void SetIdent(int i);
  conc sync int GetIdent();

private:
	int ident;
};

#endif
