#include "type.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TypeStruct::TypeStruct(char *name): DataType(name)
{
}

TypeStruct::~TypeStruct()
{
	POSITION pos=attr_names.GetHeadPosition();

	while (pos!=NULL)
	{
		char *tmp=attr_names.GetNext(pos);
		free(tmp);
	}
}

void TypeStruct::Add(DataType *elem, char *ename)
{
	assert(ename!=NULL);
	attr_types.AddTail(elem);
	ename=strdup(ename);
	attr_names.AddTail(ename);
}

int TypeStruct::CanMarshal()
{
	if (IsMarked())
	{
		Mark(false);
		return 0;
	}
	Mark(true);

	POSITION pos=attr_types.GetHeadPosition();
	while (pos!=NULL)
	{
		DataType *tmp=attr_types.GetNext(pos);
		if (tmp->CanMarshal()!=1)
		{
			Mark(false);
			return 0;
		}
	}
	Mark(false);
	return 1;
}

void TypeStruct::Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	POSITION pos=attr_types.GetHeadPosition();
	POSITION pos1=attr_names.GetHeadPosition();
	char paramname[256], tmpcode[1024];

	if (!FindVarName(varname,paramname)) strcpy(paramname,"unknown");
	sprintf(tmpcode,"%s.Push(\"%s\",\"%s\", 1);\n",bufname,paramname, GetName());
	output.InsertAt(-1,tmpcode,strlen(tmpcode));

	while (pos!=NULL)
	{
		DataType *tmp=attr_types.GetNext(pos);
		char *tname=attr_names.GetNext(pos1);
		sprintf(tmpcode,"%s.%s",varname,tname);
		tmp->Marshal(tmpcode,bufname,NULL,output);
	}
	sprintf(tmpcode,"%s.Pop();\n",bufname);
	output.InsertAt(-1,tmpcode,strlen(tmpcode));

}

void TypeStruct::DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	POSITION pos=attr_types.GetHeadPosition();
	POSITION pos1=attr_names.GetHeadPosition();
	char paramname[256], tmpcode[1024];

	if (!FindVarName(varname,paramname)) strcpy(paramname,"unknown");
	sprintf(tmpcode,"%s.Push(\"%s\",\"%s\",1);\n",bufname,paramname, GetName());
	output.InsertAt(-1,tmpcode,strlen(tmpcode));

	while (pos!=NULL)
	{
		DataType *tmp=attr_types.GetNext(pos);
		char *tname=attr_names.GetNext(pos1);

		sprintf(tmpcode,"%s.%s",varname,tname);
		tmp->DeMarshal(tmpcode,bufname,NULL,output);
	}
	sprintf(tmpcode,"%s.Pop();\n",bufname);
	output.InsertAt(-1,tmpcode,strlen(tmpcode));
}

bool TypeStruct::IsPrototype()
{
	return (attr_types.GetCount()==0);
}
