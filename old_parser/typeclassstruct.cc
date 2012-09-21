#include "type.h"

TypeClassStruct::TypeClassStruct(char *name, bool classtype): TypeSeqClass(name), TypeStruct(name), DataType(name)
{
	isClass=classtype;
}

TypeClassStruct::~TypeClassStruct()
{
}

bool TypeClassStruct::SetTypeClass(bool classtype)
{
	isClass=classtype;
}

bool TypeClassStruct::IsPrototype()
{
	if (isClass) return TypeSeqClass::IsPrototype();
	else return TypeStruct::IsPrototype();
}

int TypeClassStruct::CanMarshal()
{
	if (isClass) return TypeSeqClass::CanMarshal();
	else return TypeStruct::CanMarshal();
}

void TypeClassStruct::Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	if (isClass) TypeSeqClass::Marshal(varname,bufname,sizehelper, output);
	else TypeStruct::Marshal(varname,bufname,sizehelper, output);
}

void TypeClassStruct::DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	if (isClass) TypeSeqClass::DeMarshal(varname,bufname,sizehelper, output);
	else TypeStruct::DeMarshal(varname,bufname,sizehelper, output);
}
