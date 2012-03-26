#include <stdio.h>
#include "child.ph"

Child::Child()
{
	val = -1;
}

int Child::Method1()
{
	printf("Heritage: Executing Method1 in Child no:%d\n", val);
}

void Child::callMethod(Mother &c, int v)
{
	c.Method1();
	c.SetVal(v);
	c.Method1();
	printf("Heritage: In Child, GetVal=%d\n",c.GetVal());
}

// Warning: Mother parclass and Child parclass must be packed in the same file
@pack(Child, Mother);

