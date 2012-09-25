#include "child.ph"

Child::Child()
{
}

Child::~Child()
{
}

void Child::method_pv()
{
	printf("Call method_pv in the child\n");
}

@pack(Child, Mother);