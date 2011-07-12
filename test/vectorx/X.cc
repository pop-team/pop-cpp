#include <stdio.h>
#include "X.h"

X::X()
{value=0;}

X::~X()
{}

void X::SetValue(int i)
{value = i;}

int X::GetValue()
{return value;}

void X::Serialize(POPBuffer &buf, bool pack)
{
	if (pack)
	{
		buf.Pack(&value, 1);
	}
	else
	{
		buf.UnPack(&value,1);
	}
}
