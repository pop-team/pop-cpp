#include <stdio.h>
#include "integer.ph"
#include <unistd.h>

Integer::Integer()
{
//	printf("Create remote object Integer on %s (od.search fixed)\n",POPGetHost());
}


Integer::~Integer()
{
//	printf("Destroying Integer object...\n");
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
	printf("Add 1\n");
	data += other.Get();
	printf("Add 2 %d\n", data);
}

@pack( Integer);
