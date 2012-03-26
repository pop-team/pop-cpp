#include "type.h"
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include <assert.h>


char DataType::stdType[MAXSTDTYPES][32]={"bool",
										"char",
										"signed char",
										"unsigned char",
										"short",
										"short int",
										"unsigned short",
										"signed short",
										"int",
										"unsigned",
										"unsigned int",
										"signed int",
										"long",
										"signed long",
										"unsigned long",
										"long int",
										"long long",
										"long double",
										"float",
										"double",
										"void",
										"paroc_string",
										"std::string",
										"string"
										};


int DataType::counter=0;

DataType::DataType(char *tname)
{
	isStandard=false;
	isparclass=false;

	if (tname!=NULL)
	{
		char str[1024];
		char str1[1024];
		char sep[]=" \n\t\r";

		strcpy(str,tname);
		char *tmp=strtok(str,sep);
		*str1=0;
		while (tmp!=NULL)
		{
			strcat(str1,tmp);
			tmp=strtok(NULL,sep);
			if (tmp!=NULL) strcat(str1," ");
		}
		name=strdup(str1);

		for (int i=0;i<MAXSTDTYPES;i++) if (strcmp(name,stdType[i])==0)
			{
				isStandard=true;
				break;
			}
	}
	else name=NULL;

	mark=false;

}

DataType::~DataType()
{
	if (name!=NULL) free(name);
}

int DataType::CanMarshal()
{
	return isStandard;
}

void DataType::Marshal(char *varname, char *bufname, char *sizehelper,  CArrayChar &output)
{
	char tmpcode[1024];
	char paramname[256];
	const char *sz=(sizehelper==NULL)? "1" : sizehelper;

	if (!FindVarName(varname,paramname)) strcpy(paramname,"unkown");
	sprintf(tmpcode,"%s.Push(\"%s\",\"%s\", %s);\n",bufname,paramname, GetName(), sz);
	output.InsertAt(-1,tmpcode,strlen(tmpcode));

	sprintf(tmpcode,"%s.Pack(&%s, %s);\n",bufname,varname, sz);
	output.InsertAt(-1, tmpcode, strlen(tmpcode));

	sprintf(tmpcode,"%s.Pop();\n",bufname);
	output.InsertAt(-1,tmpcode,strlen(tmpcode));

}

void DataType::DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpcode[1024];
	char paramname[256];
	const char *sz=(sizehelper==NULL)? "1" : sizehelper;

	if (!FindVarName(varname,paramname)) strcpy(paramname,"unkown");
	sprintf(tmpcode,"%s.Push(\"%s\",\"%s\", %s);\n",bufname,paramname, GetName(), sz);
	output.InsertAt(-1,tmpcode,strlen(tmpcode));

	sprintf(tmpcode,"%s.UnPack(&%s,%s);\n",bufname,varname, sz);
	output.InsertAt(-1, tmpcode, strlen(tmpcode));

	sprintf(tmpcode,"%s.Pop();\n",bufname);
	output.InsertAt(-1,tmpcode,strlen(tmpcode));
}

bool DataType::GetDeclaration(const char *varname, char *output)
{
	if (name==NULL) return false;
	if (varname!=NULL)
	{
		sprintf(output,"%s %s",name, varname);
	}
	else
	{
		sprintf(output,"%s",name);
	}
	return true;
}

bool DataType::GetCastType(char *output)
{
	return GetDeclaration(NULL,output);
}


void DataType::GetExpandType(char *output)
{
	if (name==NULL) *output=0;
	else strcpy(output,name);
}

char *DataType::GetName()
{
	return name;
}

void DataType::SetName(const char *tname)
{
	if (name!=NULL) free(name);
	if (tname==NULL) name=NULL;
	else
	{
		name=strdup(tname);
		isStandard=false;
		for (int i=0;i<MAXSTDTYPES;i++) if (strcmp(name,stdType[i])==0)
			{
				isStandard=true;
				break;
			}
	}
}

int DataType::IsPointer()
{
	return 0;
}

bool DataType::IsArray()
{
	return false;
}

bool DataType::IsPrototype()
{
	return false;
}

bool DataType::IsStandardType()
{
	return isStandard;
}

bool DataType::IsParClass()
{
	return isparclass;
}

bool DataType::Same(DataType *other)
{
	char str1[1024];
	char str2[1024];
	GetExpandType(str1);
	other->GetExpandType(str2);
	return (strcmp(str1, str2)==0);
}

bool DataType::Same(char *tname)
{
	char str1[1024];
	GetExpandType(str1);
	return (strcmp(str1, tname)==0);
}

DataType * DataType::GetBaseType()
{
	return NULL;
}

void DataType::Mark(bool val)
{
	mark=val;
}

bool DataType::IsMarked()
{
	return mark;
}

void DataType::SetOwnerFile(CodeFile *owner)
{
	codefile=owner;
}

CodeFile * DataType::GetOwnerFile()
{
	return codefile;
}

bool DataType::FindVarName(const char *var, char name[256])
{
	if (var==NULL) return false;

	char tmp[1024];
	char *curname=NULL;
	strcpy(tmp,var);
	char *tok=curname=strtok(tmp," .->(*)<>[]");
	while (tok!=NULL)
	{
		curname=tok;
		tok=strtok(NULL," .->(*)<>[]");
	}
	if (curname==NULL) return false;
	strcpy(name,curname);
	return true;
}
/*

int DataType::GetSTLArg(char *name, char argout[1024])
{
  for (int i=0;i<MAXSTLTYPES;i++) if (strstr(name, stlType[i])==name)
    {
      char *arg=name+strlen(stlType[i]);
      if (*arg==' ') arg++;
      if (*arg!='<') continue;
      arg++;
      if (*arg==' ') arg++;
      char *end=arg;
      int count=1;
      bool done=false;
      while (1)
	{
	  if (*end==0) break;

	  if (*end=='<') count++;
	  else if (*end=='>') count--;
	  if (count<=0 || (count==1 && (*end==',' || *end=='&'))) break;
	  end++ ;
	}
      int len=end-arg;
      strncpy(argout, arg,len);
      argout[len]=0;
      return i;
    }
  return -1;

}
*/
