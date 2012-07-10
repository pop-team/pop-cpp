#ifndef CHILD_H
#define CHILD_H

#include "child.h"
#include "mother.h"

#include <stdio.h>

class Child: public Mother
{
public:
	Child();
	~Child();
	void method1();
	void method_pv();
};

#endif /* CHILD_H */