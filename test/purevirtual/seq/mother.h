#ifndef MOTHER_H
#define MOTHER_H

#include "mother.h"

class Mother
{
public:
	Mother();
	~Mother();
	void method_master();
	virtual void method_pv()=0;
};

#endif /* MOTHER_H */