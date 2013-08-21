#ifndef _TOTO_PH
#define _TOTO_PH

parclass Toto          
{

classuid(1002);

public:
	Toto() @{od.url("localhost");};
	~Toto();

	conc sync void work();
	seq sync int getIdent();
	seq sync void setIdent(int i);

private:
  int ident;

};

#endif
