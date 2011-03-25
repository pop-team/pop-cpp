#include <string.h>
#include <stdio.h>
#include "type.h"

TypeArray::TypeArray(char *name, char *cardstr, DataType *base): DataType(name)
{
	cardinal=strdup(cardstr);
	typebase=base;
}

TypeArray::~TypeArray()
{
	if (cardinal!=NULL) free(cardinal);
}

void TypeArray::GetCardinalSize(char *size)
{
	char *tmpindex=cardinal;
	char *tmpindex1=size;
	int openbracket=0;
	int ignore=0;
	bool firstdim=true;

	while (*tmpindex!=0)
	{
		*tmpindex1=*tmpindex;

		if (ignore && *tmpindex1=='\\')
		{
			tmpindex1++;
			tmpindex++;
			*tmpindex1=*tmpindex;
		}
		else if (*tmpindex1=='"') ignore=!ignore;
		else if (!ignore)
		{
			if (*tmpindex1=='[')
			{
				if (openbracket==0)
				{
					if (!firstdim)
					{
						*tmpindex1='*';
						tmpindex1++;
					} else firstdim=false;
					*tmpindex1='(';
				}
				openbracket++;
			}
			else if  (*tmpindex1==']')
			{
				openbracket--;
				if (openbracket==0)  *tmpindex1=')';
			}
		}

		tmpindex1++;
		tmpindex++;
	}
	*tmpindex1=0;
}

int TypeArray::CanMarshal()
{
	if (IsMarked())
	{
		Mark(false);
		return 0;
	}
	Mark(true);
	int ret=typebase->CanMarshal();
	Mark(false);
	return ret;
}

void TypeArray::Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpvar[1024];
	char size[1024];
	char *tmpsize;


	if (sizehelper==NULL)
	{
		GetCardinalSize(size);
		tmpsize=size;
	}
	else tmpsize=sizehelper;

	if (typebase->IsStandardType() || tmpsize==NULL || strcmp(tmpsize,"1")==0)
	{
		sprintf(tmpvar,"(*((%s *)%s))",typebase->GetName(),varname);
		typebase->Marshal(tmpvar,bufname, tmpsize, output);
	}
	else
	{
		char tmpcode[1024];

		sprintf(tmpcode,"{ int _paroc_count%d=%s;\n",counter, tmpsize);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		char paramname[256];
		if (!FindVarName(varname,paramname)) strcpy(paramname,"unknown");
		sprintf(tmpcode,"%s.Push(\"%s\",\"%s\",_paroc_count%d);\n",bufname, paramname,typebase->GetName(), counter);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));


		sprintf(tmpcode,"for (%s *_paroc_elem%d =(%s *)(%s); _paroc_count%d>0; _paroc_count%d--, _paroc_elem%d++)\n{\n", typebase->GetName(), counter, typebase->GetName(), varname, counter,counter, counter);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpvar,"(*_paroc_elem%d)",counter);
		typebase->Marshal(tmpvar,bufname, NULL, output);
		strcpy(tmpcode,"}\n}\n");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpcode,"%s.Pop();\n",bufname);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		counter++;
	}

}

void TypeArray::DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpvar[1024];
	char size[1024];
	char *tmpsize;


	if (sizehelper==NULL)
	{
		GetCardinalSize(size);
		tmpsize=size;
	}
	else tmpsize=sizehelper;

	if (typebase->IsStandardType() || tmpsize==NULL || strcmp(tmpsize,"1")==0)
	{
		sprintf(tmpvar,"(*((%s *)%s))",typebase->GetName(),varname);
		typebase->DeMarshal(tmpvar,bufname, tmpsize, output);
	}
	else
	{
		char tmpcode[1024];

		sprintf(tmpcode,"{ int _paroc_count%d=%s;\n",counter, tmpsize);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		char paramname[256];
		if (!FindVarName(varname,paramname)) strcpy(paramname,"unknown");
		sprintf(tmpcode,"%s.Push(\"%s\",\"%s\",_paroc_count%d);\n",bufname, paramname, typebase->GetName(), counter);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpcode,"for (%s *_paroc_elem%d =(%s *)(%s); _paroc_count%d>0; _paroc_count%d--, _paroc_elem%d++)\n{\n", typebase->GetName(), counter, typebase->GetName(), varname, counter,counter, counter);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpvar,"(*_paroc_elem%d)",counter);
		typebase->DeMarshal(tmpvar,bufname, NULL, output);
		strcpy(tmpcode,"}\n}\n");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		sprintf(tmpcode,"%s.Pop();\n",bufname);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));

		counter++;
	}

}

bool TypeArray::GetDeclaration(const char *varname, char *output)
{
	if (DataType::GetDeclaration(varname, output)) return true;

	if (typebase->GetDeclaration(varname, output))
	{
		strcat(output,cardinal);
		return true;
	}

	return false;
}

bool TypeArray::GetCastType(char *output)
{
	char *str=cardinal;
	while (*str!=0 && *str!='[') str++;

	if (*str=='[')
	{
		int count=0;
		do
		{
			if (*str=='[') count++;
			else if (*str==']') count--;
			str++;
		}
		while (count>0 && *str!=0);
	}

	if (!typebase->GetCastType(output)) return false;
	strcat(output,"(*)");
	strcat(output,str);
	return true;
}

void TypeArray::GetExpandType(char *output)
{
	typebase->GetExpandType(output);
	strcat(output,cardinal);
}

bool TypeArray::IsArray()
{
	return true;
}
