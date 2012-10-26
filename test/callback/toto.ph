#ifndef _TOTO_PH
#define _TOTO_PH

parclass Toto          
{

classuid(1002);

public:
	Toto() @{ od.url("localhost"); od.executable("/Users/clementval/versioning/popc/popc2.6.2/test/callback/toto.obj"); };
	~Toto();

	seq sync void SetIdent(int i);
  conc sync int GetIdent();

private:
	int ident;
};

#endif
