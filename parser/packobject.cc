#include "parser.h"
#include "paroc_utils.h"
#include "debug.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/types.h>
#include <time.h>

//PackObject implementation

PackObject::PackObject(CodeFile *file): CodeData(file), objects(0,5)
{
	startline=endline=-1;
}

void PackObject::GenerateCode(CArrayChar &output)
{
	char str[1024];
	char *fname=GetCodeFile()->GetFileName();
	if (startline>0 && fname!=NULL)
	{
		sprintf(str,"\n# %d \"%s\"\n",startline,fname);
		output.InsertAt(-1,str,strlen(str));
	}

	//New code: BEGIN===================
	strcpy(str,"void paroc_registerbroker() {\n");
	output.InsertAt(-1,str,strlen(str));
	int n=objects.GetSize();
	for (int i=0;i<n;i++)
	{
		//      sprintf(str,"paroc_broker_factory _br%d(%s%sBroker::_init,\"%s\");\n",i, objects[i],OBJ_POSTFIX,objects[i]);
		sprintf(str,"%s%sBroker::_fact.Test(\"%s\");\n",objects[i],OBJ_POSTFIX,objects[i]);
		output.InsertAt(-1,str,strlen(str));
	}
	strcpy(str,"}\n");
	output.InsertAt(-1,str,strlen(str));

	//New code : Check if the object broker is packed
	strcpy(str,"bool CheckIfPacked(const char *objname)\n{\n\tif (objname==0) return false;\n");
	output.InsertAt(-1,str,strlen(str));
	int sz=objects.GetSize();
	for (int j=0;j<sz;j++)
	{
		sprintf(str,"\n\tif (paroc_utils::isEqual(objname, \"%s\")) return true;",objects[j]);
		output.InsertAt(-1,str,strlen(str));
	}
	strcpy(str,"\n\treturn false;\n}\n");
	output.InsertAt(-1,str,strlen(str));
	if (endline>0 && fname!=NULL)
	{
		sprintf(str,"\n# %d \"%s\"\n",endline,fname);
		output.InsertAt(-1,str,strlen(str));
	}

	if (endline>0 && fname!=NULL)
	{
		sprintf(str,"\n# %d \"%s\"\n",endline,fname);
		output.InsertAt(-1,str,strlen(str));
	}
	return;
	//New code: END===========================


	//OLD code for the "pack" directive
	/*  if (objects.GetSize())
	    {
	      strcpy(str,"#ifndef __NO_POPC_INITBROKER\nparoc_broker* InitBroker(char *objname)\n{\n\tif (objname==0) return 0;\n");
	      output.InsertAt(-1,str,strlen(str));
	      int sz=objects.GetSize();
	      for (int j=0;j<sz;j++)
		{
		  sprintf(str,"\n\tif (strcmp(objname,\"%s\")==0) return new %s%sBroker;",objects[j],objects[j],OBJ_POSTFIX);
		  output.InsertAt(-1,str,strlen(str));

		}
	      strcpy(str,"\n\treturn 0;\n}\n");
	      output.InsertAt(-1,str,strlen(str));

	      strcpy(str,"\nvoid  QueryObjectList(char *list, int n)\n{\nstrncpy(list,\"");
	      output.InsertAt(-1,str,strlen(str));
	      for (int j=0;j<sz;j++)
		{
		  sprintf(str,"%s\\n",objects[j]);
		  output.InsertAt(-1,str,strlen(str));
		}
	      strcpy(str,"\",n);\n}\n#endif\n");
	      output.InsertAt(-1,str,strlen(str));
	    }*/
}


void PackObject::AddObject(string64 objname)
{
	int n=objects.GetSize();
	for (int i=0;i<n;i++) if (paroc_utils::isEqual(objects[i],objname)) return;

	objects.SetSize(n+1);
	strcpy(objects[n],objname);
}

int PackObject::GetNumObject()
{
	return objects.GetSize();
}


void  PackObject::SetStartLine(int l)
{
	startline=l;
}

void  PackObject::SetEndLine(int l)
{
	endline=l;
}
