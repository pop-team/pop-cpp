#include <stdio.h>
#include "integer.ph"
#include <unistd.h>

Integer::Integer()
{
	printf("Create remote object Integer on %s (od.search fixed)\n",
		   POPGetHost());
}

Integer::Integer(int maxhop, int timeout)
{
	printf("Create remote object Integer on %s (od.search(%d, 0, %d))\n",
		   POPGetHost(), maxhop, timeout);
}
Integer::Integer(POPString machine){
	printf("Create remote object on %s\n", POPGetHost());
}
Integer::~Integer()
{
	printf("Destroying Integer object...\n");
}

void Integer::Set(int val)
{
	data=val;
}

int Integer::Get()
{
	return data;
}

void Integer::Add(Integer &other)
{
	data += other.Get();
}

@pack( Integer);
