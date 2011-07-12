#ifndef _CLASSA_H
#define _CLASSA_H

template <class C> class ClassA
{
public:
	ClassA();
	~ClassA();
	int GetIdent();
	void SetIdent(int i);

private:
	C x;
};

#endif
