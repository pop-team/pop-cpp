#ifndef CHILD_H
#define CHILD_H

#include "child.ph"
#include "mother.ph"

#include <stdio.h>

parclass Child: public Mother
{
public:
	classuid(1201);
	Child();
	~Child();
	sync seq void method_pv();
};

@pack(Child, Mother);

#endif /* CHILD_H */