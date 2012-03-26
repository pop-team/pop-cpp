#include "type.h"

TypeEqual::TypeEqual(char *name, DataType *atype): DataType(name)
{
	type=atype;
	if (atype->GetName()==NULL && name!=NULL) atype->SetName(name);
}

int TypeEqual::CanMarshal()
{
	if (IsMarked())
	{
		Mark(false);
		return 0;
	}
	Mark(true);
	int ret=type->CanMarshal();
	Mark(false);
	return ret;
}

void TypeEqual::Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	type->Marshal(varname,bufname,sizehelper, output);
}

void TypeEqual::DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	type->DeMarshal(varname,bufname,sizehelper, output);
}


// bool TypeEqual::Same(DataType *other)
// {
//   if (DataType::Same(other)) return true;
//   return type->Same(other);
// }

// bool TypeEqual::Same(char *tname)
// {
//   if (strcmp(name, tname)==0) return true;
//   return type->Same(tname);
// }

int TypeEqual::IsPointer()
{
	return type->IsPointer();
}

bool TypeEqual::IsArray()
{
	return type->IsArray();
}

bool TypeEqual::IsParClass()
{
	return type->IsParClass();
}

DataType * TypeEqual::GetBaseType()
{
	DataType *t=type->GetBaseType();
	if (t!=NULL) return t;
	return type;
}

bool TypeEqual::GetCastType(char *output)
{
	if (!IsArray()) return GetDeclaration(NULL,output);
	else return type->GetDeclaration(NULL,output);
}

void TypeEqual::GetExpandType(char *output)
{
	type->GetExpandType(output);
}
