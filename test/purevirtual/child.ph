#ifndef CHILD_H
#define CHILD_H

#include "child.ph"
#include "mother.ph"

#include <stdio.h>

parclass Child: public Mother
{
public:
	classuid(1201);
	Child() @{  od.node(1); od.executable("child.obj");  };
	~Child();
	sync seq void method_pv();
};

#endif /* CHILD_H */
