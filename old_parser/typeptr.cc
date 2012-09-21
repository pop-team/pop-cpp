#include "string.h"
#include "stdio.h"
#include "type.h"

//Pointer of a type....

TypePtr::TypePtr(char *name, int level, DataType *base): DataType(name)
{
	typebase=base;
	assert(base!=NULL);
	nptr=(level<=0)? 1: level;
	size=NULL;
}

TypePtr::~TypePtr()
{
	if (size!=NULL) free(size);
}

int TypePtr::CanMarshal()
{
	if (IsMarked())
	{
		Mark(false);
		return 0;
	}
	Mark(true);
	int ret=0;
	if (nptr==1 && typebase->CanMarshal()) ret=2;
	Mark(false);
	return ret;
}

void TypePtr::Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpvar[1024];
	char *tmpsize=(sizehelper!=NULL)? sizehelper: size;

	if (typebase->IsStandardType() || tmpsize==NULL || strcmp(tmpsize,"1")==0)
	{
		sprintf(tmpvar,"(*(%s))",varname);
		typebase->Marshal(tmpvar,bufname, tmpsize, output);
	}
	else
	{
		char tmpcode[1024];

		char paramname[256];
		if (!FindVarName(varname,paramname)) strcpy(paramname,"unknown");
		sprintf(tmpcode,"\n%s.Push(\"%s\",\"%s\", %s);\n", bufname, paramname,typebase->GetName(),tmpsize);      output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpcode,"\n{for (int _paroc_item=0; _paroc_item < %s; _paroc_item++) { \n", tmpsize);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
		sprintf(tmpvar,"(%s[_paroc_item])",varname);
		typebase->Marshal(tmpvar,bufname, NULL, output);

		strcpy(tmpcode,"}\n}\n");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpcode,"%s.Pop();\n",bufname);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

	}
}

void TypePtr::DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpvar[1024];
	char *tmpsize=(sizehelper!=NULL)? sizehelper: size;

	if (typebase->IsStandardType() || tmpsize==NULL || strcmp(tmpsize,"1")==0)
	{
		sprintf(tmpvar,"(*(%s))",varname);
		typebase->DeMarshal(tmpvar,bufname, tmpsize, output);
	}
	else
	{
		char tmpcode[1024];

		char paramname[256];
		if (!FindVarName(varname,paramname)) strcpy(paramname,"unknown");
		sprintf(tmpcode,"\n%s.Push(\"%s\",\"%s\", %s);\n", bufname, paramname,typebase->GetName(),tmpsize);      output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpcode," {\nfor (int _paroc_item=0; _paroc_item < %s; _paroc_item++) { \n", tmpsize);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
		sprintf(tmpvar,"(%s[_paroc_item])",varname);
		typebase->DeMarshal(tmpvar,bufname, NULL, output);

		strcpy(tmpcode,"}\n}\n");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpcode,"%s.Pop();\n",bufname);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
	}
}

bool TypePtr::GetDeclaration(const char *varname, char *output)
{
	if (name!=NULL) return DataType::GetDeclaration(varname, output);

	char tmp[1024];
	if (!typebase->GetDeclaration(NULL,output)) return false;
	strcat(output," ");
	for (int i=0;i<nptr;i++) strcat(output,"*");
	if (varname!=NULL) strcat(output,varname);
	return true;
}

void TypePtr::GetExpandType(char *output)
{
	typebase->GetExpandType(output);
	for (int i=0;i<nptr;i++) strcat(output,"*");
}


void TypePtr::SetSize(char *sizestr)
{
	if (size!=NULL) free(size);
	size=(sizestr==NULL)? NULL : strdup(sizestr);
}

int TypePtr::IsPointer()
{
	return nptr+ typebase->IsPointer();
}

DataType * TypePtr::GetBaseType()
{
	DataType *t=typebase->GetBaseType();
	if (t!=NULL) return t;
	return typebase;
}
