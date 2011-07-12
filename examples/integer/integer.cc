#include <stdio.h>
#include "integer.ph"
#include <unistd.h>

Integer::Integer()
{
	printf("Create remote object Integer on %s (default)\n",
		   (const char *)POPSystem::GetHost());
}

Integer::Integer(int wanted, int minp)
{
	printf("Create remote object Integer on %s (od.power)\n",
		   (const char *)POPSystem::GetHost());
}

Integer::Integer(POPString machine)
{
	printf("Create remote object Integer on %s (od.url)\n",
		   (const char *)POPSystem::GetHost());
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
