#include <stdio.h>
#include "X.h"

X::X()
{ident=0;printf("TemplateParam1: Contructing object X:%d\n", ident);}

X::~X()
{printf("TemplateParam1: Destroying object X:%d\n", ident);}

void X::SetIdent(int i)
{printf("TemplateParam1: SetIdent in object X:%d\n", i); ident = i;}

int X::GetIdent()
{printf("TemplateParam1: GetIdent in object X:%d\n", ident); return ident;}

void X::Serialize(POPBuffer &buf, bool pack)
{
	if (pack)
	{
		buf.Pack(&ident, 1);
	}
	else
	{
		buf.UnPack(&ident,1);
	}
}
