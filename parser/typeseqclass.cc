#include "type.h"
#include <stdio.h>
#include <strings.h>

TypeSeqClass::TypeSeqClass(char *name): DataType(name)
{
}

TypeSeqClass::~TypeSeqClass()
{
}

void TypeSeqClass::AddBase(DataType *t)
{
	bases.AddTail(t);
}

int TypeSeqClass::CanMarshal()
{
	if (IsMarked())
	{
		Mark(false);
		return 0;
	}
	char *str=GetName();
	if (str==NULL) return 0;
	if (strcmp(str,"paroc_base")==0) return 1;

	Mark(true);
	POSITION pos=bases.GetHeadPosition();
	while (pos!=NULL)
	{
		DataType *t=bases.GetNext(pos);
		if (t->CanMarshal())
		{
			Mark(false);
			return 1;
		}
	}
	Mark(false);
	return 0;
}

void TypeSeqClass::Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpstr[1024];
	char paramname[256];

	if (!FindVarName(varname,paramname)) strcpy(paramname,"unkown");
	sprintf(tmpstr,"%s.Push(\"%s\",\"%s\",1);\n",bufname,paramname, GetName());
	output.InsertAt(-1,tmpstr,strlen(tmpstr));

	sprintf(tmpstr, "((%s &)(%s)).Serialize(%s, true);\n",GetName(),varname,bufname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));

	sprintf(tmpstr,"%s.Pop();\n",bufname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));
}

void TypeSeqClass::DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpstr[1024];
	char paramname[256];

	if (!FindVarName(varname,paramname)) strcpy(paramname,"unkown");
	sprintf(tmpstr,"%s.Push(\"%s\",\"%s\",1);\n",bufname,paramname, GetName());
	output.InsertAt(-1,tmpstr,strlen(tmpstr));

	sprintf(tmpstr, "((%s &)(%s)).Serialize(%s, false);\n",GetName(),varname,bufname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));

	sprintf(tmpstr,"%s.Pop();\n",bufname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));
}
