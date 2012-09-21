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

#define MIN_CLASSID 1000
char Class::interface_base[]="paroc_interface";
char Class::broker_base[]="paroc_broker";
char Class::object_base[]="paroc_object";

//BEGIN Class implementation

Class::Class(char *clname, CodeFile *file): CodeData(file), DataType(clname), constructor(this, PUBLIC)
{
	*classid=0;
	initDone=false;
	endid=11;
	myFile=NULL;
	startline=endline=0;
	strcpy(constructor.name,clname);
	constructor.id=10;

	noConstructor=true;
	pureVirtual=false;

	my_interface_base=strdup(interface_base);
	my_object_base=strdup(object_base);
	my_broker_base=strdup(broker_base);

}

Class::~Class()
{
	int i,n;
	n=baseClass.GetSize();
	for (i=0;i<n;i++) if (baseClass[i]!=NULL) delete baseClass[i];

	n=memberList.GetSize();
	for (i=0;i<n;i++) if (memberList[i]!=NULL) delete memberList[i];

	if (myFile!=NULL) free(myFile);
	if (my_interface_base!=NULL) free(my_interface_base);
	if (my_object_base!=NULL) free(my_object_base);
	if (my_broker_base!=NULL) free(my_broker_base);

}

/*
parclass is also a data type
 */

bool Class::IsParClass()
{
	return true;
}

int Class::CanMarshal()
{
	return 1;
}

void Class::Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpstr[1024];
	char paramname[256];

	if (!FindVarName(varname,paramname)) strcpy(paramname,"unkown");
	sprintf(tmpstr,"%s.Push(\"%s\",\"paroc_interface\",1);\n",bufname,paramname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));

	// If uncommented, the 4 following lines will check at runtime if polymorphism is used (and exit)
	//sprintf(tmpstr, "if(!paroc_utils::MatchWildcard(typeid(%s).name(),\"*%s\"))\n",varname,GetName());
	//output.InsertAt(-1,tmpstr,strlen(tmpstr));
	//sprintf(tmpstr, "{printf(\"POPC Error at method call: dynamic type of %s must correspond with static type %s\\n\");exit(-1);}\n",varname,GetName());
	//output.InsertAt(-1,tmpstr,strlen(tmpstr));

	sprintf(tmpstr, "((%s &)(%s)).Serialize(%s, true);",GetName(),varname,bufname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));

	sprintf(tmpstr,"%s.Pop();\n",bufname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));
}

void Class::DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output)
{
	char tmpstr[1024];
	char paramname[256];

	if (!FindVarName(varname,paramname)) strcpy(paramname,"unkown");
	sprintf(tmpstr,"%s.Push(\"%s\",\"paroc_interface\",1);\n",bufname,paramname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));

	sprintf(tmpstr, "((%s &)(%s)).Serialize(%s, false);",GetName(),varname,bufname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));

	sprintf(tmpstr,"%s.Pop();\n",bufname);
	output.InsertAt(-1,tmpstr,strlen(tmpstr));
}


/*
Other methods...
*/

void Class::SetFileInfo(char *file)
{
	if (myFile!=NULL) free(myFile);
	myFile=strdup(file);

}

char * Class::GetFileInfo()
{
	return myFile;
}

void Class::SetStartLine(int num)
{
	startline=num;
}


void Class::SetEndLine(int num)
{
	endline=num;
}


void Class::GenerateCode(CArrayChar &output)
{
	char str[1024];

	if (*classid==0)
	{
		sprintf(str,"\nconst unsigned CLASSUID_%s=unsigned(%u);\n",name,IDFromString(name));
		fprintf(stderr,"Warning: class unique identifier (classuid) for %s is not specified.\n",name);
	}
	else
	{
		sprintf(str,"\nconst unsigned  CLASSUID_%s=unsigned(%s);\n",name,classid);
	}

	if (!pureVirtual)
	{
		CArrayMethod puremethods;
		findPureVirtual(puremethods);
		pureVirtual=(puremethods.GetSize()>0);
	}

	output.InsertAt(-1,str,strlen(str));

	GenerateHeader(output,true);

	GenerateHeader(output,false);

	GenerateBrokerHeader(output);

}
void Class::AddMember(ClassMember *t)
{
	if (t->Type()==TYPE_METHOD)
	{
		Method *met=(Method *)t;
		int type=met->MethodType();
		if (type==METHOD_CONSTRUCTOR) noConstructor=false;

		if (type==METHOD_CONSTRUCTOR && ((Constructor *)met)->isDefault())
		{
			met->id=10;
		}
		else met->id=endid++;
	}
	memberList.InsertAt(-1,t);
}


void Class::SetClassID(char *id)
{
	if (id==NULL)
	{
		sprintf(classid,"%u",IDFromString(name));
	}
	else
	{
		strncpy(classid,id,63);
		classid[63]=0;
	}
}

void Class::SetPureVirtual(bool val)
{
	pureVirtual=val;
}

bool Class::hasMethod(Method &x)
{
	int n=memberList.GetSize();
	for (int i=0;i<n;i++) if (memberList[i]->Type()==TYPE_METHOD)
		{
			Method &t=*((Method *)memberList[i]);
			if (t==x) return true;
		}
	return false;
}

bool Class::methodInBaseClass(Method &x)
{
	CodeFile *prog=GetCodeFile();

	int n=baseClass.GetSize();
	for (int i=0;i<n;i++)
	{
		BaseClass &t=*(baseClass[i]);
		if (t.type!=PUBLIC) continue;
		if (t.base->hasMethod(x)) return true;
		if (t.base->methodInBaseClass(x)) return true;
	}
	return false;
}


void Class::findPureVirtual(CArrayMethod &lst)
{
	CodeFile *prog=GetCodeFile();

	int n=baseClass.GetSize();
	for (int i=0;i<n;i++)
	{
		BaseClass &t=*(baseClass[i]);
		if (t.type!=PUBLIC) continue;
		t.base->findPureVirtual(lst);
	}

	n=memberList.GetSize();
	int m=lst.GetSize();
	for (int i=0;i<n;i++) if (memberList[i]->Type()==TYPE_METHOD)
		{
			Method *t=(Method *)(memberList[i]);
			if (t->isPureVirtual) lst.InsertAt(-1,t);
			else if (m)
			{
				for (int j=m-1;j>=0;j--) if  ( *(lst[j]) == (*t) ) lst.RemoveAt(j);
			}
		}
}

bool Class::GenerateClient(CArrayChar &code)
{
	char tmpcode[10240];

	char *outfile=GetCodeFile()->GetOutputName();
	if (outfile!=NULL)
	{
		int lines=CountCodeLines(code);
		sprintf(tmpcode,"\n# %d \"%s\"\n",lines+3, outfile);
		code.InsertAt(-1,tmpcode,strlen(tmpcode));
	}

	int n=memberList.GetSize();
	for (int i=0;i<n;i++)
	{
		if (memberList[i]->Type()!=TYPE_METHOD || memberList[i]->GetMyAccess()!=PUBLIC) continue;

		Method *met=(Method *)memberList[i];
		if (pureVirtual && met->MethodType()==METHOD_CONSTRUCTOR) continue;

		met->GenerateClient(code);
	}

	if (noConstructor && !pureVirtual)
	{
		constructor.GenerateClient(code);
	}

	//  code.InsertAt(-1,tmpcode,strlen(tmpcode));

	char *fname=GetCodeFile()->GetFileName();
	if (endline>0 && fname!=NULL)
	{
		sprintf(tmpcode,"\n# %d \"%s\"\n",endline,fname);
		code.InsertAt(-1,tmpcode,strlen(tmpcode));
	}
	return true;
}

unsigned Class::IDFromString(char *str)
{
	char tmp[256];
	int n=0;
	int len=strlen(str);
	int starta=('Z'-'A')+1;
	for (int i=0;i<len && i<256; i++,str++)
	{
		if (*str>='A' && *str>='Z')
		{
			tmp[n++]=(*str)-'A';
		}
		else if (*str>='a' && *str>='z')
		{
			tmp[n++]=(*str)-'a'+starta;
		}
		else if (*str=='_')
		{
			tmp[n++]=2*starta;
		}
		else if (*str>='0' && *str<='9')
		{
			tmp[n++]=(*str)-'0'+2*starta+1;
		}
	}

	unsigned sz=2*starta+11;
	n--;
	unsigned id=tmp[n];
	for (int i=0;i<n;i++) id=id*sz+tmp[i];
	return id+MIN_CLASSID;

}

bool Class::GenerateHeader(CArrayChar &code, bool interface)
{
	char tmpcode[10240];
	char str[1024];

	char *fname=GetCodeFile()->GetFileName();
	if (startline>0 && fname!=NULL)
	{
		sprintf(str,"\n# %d \"%s\"\n",startline,fname);
		code.InsertAt(-1,str,strlen(str));
	}

	strcpy(str,name);

	if (!interface)
	{
		strcat(str,OBJ_POSTFIX);
	}

	sprintf(tmpcode,"class %s ",str);
	int n=baseClass.GetSize();
	strcat(tmpcode," :");

	int i,j;
	bool defaultconstructor=false;

	for (i=0;i<n;i++)
	{
		BaseClass &base=*(baseClass[i]);
		if (base.baseVirtual) strcat(tmpcode,"virtual ");
		if (base.type==PUBLIC) strcat(tmpcode,"public ");
		else if (base.type==PROTECTED) strcat(tmpcode,"protected ");
		else strcat(tmpcode,"private ");

		strcat(tmpcode,base.base->GetName());
		if (!interface) strcat(tmpcode, OBJ_POSTFIX);
		if (i<n-1) strcat(tmpcode,", ");
	}
	if (n) strcat(tmpcode,"\n{\npublic:");
	else if (interface)
	{
		sprintf(str," virtual public %s\n{\npublic:", my_interface_base);
		strcat(tmpcode, str);
	}
	else
	{
		sprintf(str," virtual public %s\n{\npublic:", my_object_base);
		strcat(tmpcode, str);
	}

	code.InsertAt(-1,tmpcode,strlen(tmpcode));
	*tmpcode=0;

	//Generate members
	const char *accessstr[3]={"\npublic:","\nprotected:","\nprivate:"};
	AccessType currentaccess=PUBLIC;
	n=memberList.GetSize();

	for (i=0;i<n;i++)
	{
		if (interface && memberList[i]->GetMyAccess()!=PUBLIC) continue;

		if (memberList[i]->GetMyAccess()!=currentaccess)
		{
			currentaccess=memberList[i]->GetMyAccess();
			code.InsertAt(-1,accessstr[currentaccess],strlen(accessstr[currentaccess]));
		}

		if (memberList[i]->Type()==TYPE_METHOD)
		{
			Method *t=(Method *)memberList[i];
			if (t->MethodType()==METHOD_CONSTRUCTOR)
			{
				if ( ((Constructor *)t)->isDefault()) defaultconstructor=true;
				if (interface && pureVirtual) continue;
			}
		}

		memberList[i]->GenerateHeader(code,interface);
	}

	if (interface)
	{
		sprintf(str,"\npublic:\nvirtual const char *ClassName() { return \"%s\"; };",name);
		code.InsertAt(-1,str,strlen(str));

		//Generate constructor from paroc_accesspoint...

		sprintf(str,"\npublic:\n%s(const paroc_accesspoint &p)",name);
		code.InsertAt(-1,str,strlen(str));

		int n=baseClass.GetSize();
		if (n)
		{
			CArrayClass bases;
			bases.SetSize(n);
			for (int i=0;i<n;i++)  bases[i]=baseClass[i]->base;
			CodeFile *prog=GetCodeFile();
			prog->FindAllBaseClass(*this, bases,true);

			n=bases.GetSize();
			strcpy(tmpcode," : ");
			for (int j=0;j<n;j++)
			{
				strcat(tmpcode,bases[j]->GetName());
				if (j<n-1) strcat(tmpcode,"(_paroc_nobind) ,");
				else  strcat(tmpcode,"(_paroc_nobind)");
			}
			code.InsertAt(-1,tmpcode,strlen(tmpcode));
		}

		strcpy(str," { Bind(p); };\n");
		code.InsertAt(-1,str,strlen(str));

		//If no constructor, generate default for interface...
		if (noConstructor && !pureVirtual) constructor.GenerateHeader(code, interface);

		//Generate constructor from the interface binding
		sprintf(str,"\n%s(const %s &inf)",name, my_interface_base);
		code.InsertAt(-1,str,strlen(str));
		code.InsertAt(-1,tmpcode,strlen(tmpcode));
		strcpy(str," { SetOD(inf.GetOD()); Bind(inf.GetAccessPoint()); };\n");
		code.InsertAt(-1,str,strlen(str));

		//Generate constructor from the object side binding
		sprintf(str,"\n%s(const paroc_object *obj)",name);
		code.InsertAt(-1,str,strlen(str));
		code.InsertAt(-1,tmpcode,strlen(tmpcode));
		strcpy(str," { Bind(obj->GetAccessPoint());};\n");
		code.InsertAt(-1,str,strlen(str));



//       if (!defaultconstructor && interface)
// 	{
// 	  sprintf(str,"\n\t%s ()",name);
// 	  code.InsertAt(-1,str,strlen(str));
// 	  if (n)
// 	    {
// 	      code.InsertAt(-1,tmpcode,strlen(tmpcode));
// 	    }
// 	  code.InsertAt(-1," {};\n",5);
// 	}
	}

	strcpy(str,"\n};\n");
	code.InsertAt(-1,str, strlen(str));

	if (endline>0 && fname!=NULL)
	{
		sprintf(str,"\n# %d \"%s\"\n",endline,fname);
		code.InsertAt(-1,str,strlen(str));
	}
	return true;
}

bool Class::GenerateBrokerHeader(CArrayChar &code)
{
	int i,j;
	char str[1024];
	char tmpcode[10240];

	char brokername[256];

	char *outfile=GetCodeFile()->GetOutputName();
	if (outfile!=NULL)
	{
		int lines=CountCodeLines(code);
		sprintf(tmpcode,"\n# %d \"%s\"\n",lines+3, outfile);
		code.InsertAt(-1,tmpcode,strlen(tmpcode));
	}
	sprintf(brokername,"%s%sBroker",name,OBJ_POSTFIX);

	int n=baseClass.GetSize();
	if (n==0) sprintf(tmpcode,"\n\nclass %s: virtual public %s",brokername, my_broker_base);
	else
	{
		sprintf(tmpcode,"\n\nclass %s: ",brokername);
		for (i=0;i<n;i++)
		{
			if (baseClass[i]->baseVirtual) strcat(tmpcode,"virtual ");
			strcat(tmpcode,"public ");
			strcat(tmpcode, baseClass[i]->base->GetName());
			strcat(tmpcode, OBJ_POSTFIX);
			strcat(tmpcode, "Broker");
			if (i<n-1) strcat(tmpcode,", ");
		}
	}
	sprintf(str,"\n{\npublic:\n%s();\nvirtual bool Invoke(unsigned method[3],  paroc_buffer &__brokerbuf, paroc_connection *peer);", brokername);
	strcat(tmpcode,str);

	strcat(tmpcode,"\nprotected:");
	code.InsertAt(-1,tmpcode,strlen(tmpcode));

	n=memberList.GetSize();
	for (i=0;i<n;i++)
	{
		if (memberList[i]->GetMyAccess()!=PUBLIC || memberList[i]->Type()!=TYPE_METHOD) continue;
		Method &met=*((Method *)memberList[i]);
		if (pureVirtual && met.MethodType()==METHOD_CONSTRUCTOR) continue;

		met.GenerateBrokerHeader(code);
	}

	if (noConstructor && !pureVirtual) constructor.GenerateBrokerHeader(code);

	//Propagate object to parent....
	//  sprintf(str,"\n\t%s%s *obj;\n\tvoid SetImpObject(%s%s *newobj);",name,OBJ_POSTFIX,name,OBJ_POSTFIX);
	//  code.InsertAt(-1,str,strlen(str));

	//Now generate the static paroc_broker_factory....
	if (!pureVirtual)
	{
		sprintf(tmpcode,"\npublic:\nstatic paroc_broker *_init();\nstatic paroc_broker_factory _fact;\n");
		code.InsertAt(-1,tmpcode,strlen(tmpcode));
	}

	strcpy(str,"\n}\n;");

	code.InsertAt(-1,str,strlen(str));

	char *fname=GetCodeFile()->GetFileName();
	if (endline>0 && fname!=NULL)
	{
		sprintf(str,"\n# %d \"%s\"\n",endline,fname);
		code.InsertAt(-1,str,strlen(str));
	}
	return true;

}

bool Class::GenerateBroker(CArrayChar &code)
{
	//Generate Broker-derived class for creation objects and the re-implementation of

	int i,j;
	char str[10240];
	char tmpcode[10240];
	char brokername[256];

	CodeFile *codefile=GetCodeFile();

	char *outfile=codefile->GetOutputName();
	if (outfile!=NULL)
	{
		int lines=CountCodeLines(code);
		sprintf(tmpcode,"\n# %d \"%s\"\n",lines+3, outfile);
		code.InsertAt(-1,tmpcode,strlen(tmpcode));
	}

	sprintf(brokername,"%s%sBroker",name,OBJ_POSTFIX);
	//now...the implementation....

//Generate broker::Invoke virtual method
	sprintf(str,"\nbool %s::Invoke(unsigned method[3], paroc_buffer &__brokerbuf, paroc_connection *peer)\n{\nif (*method==CLASSUID_%s) switch(method[1])\n{",brokername,name);
	code.InsertAt(-1,str,strlen(str));

	char methodinfo[10240];
	char methodcount=0;
	char *methodinfoptr=methodinfo;
	*methodinfoptr=0;

	int n=memberList.GetSize();
	for (i=0;i<n;i++)
	{
		if (memberList[i]->GetMyAccess()!=PUBLIC || memberList[i]->Type()!=TYPE_METHOD) continue;
		Method &met=*((Method *)memberList[i]);

		int t=met.MethodType();
		if (t==METHOD_DESTRUCTOR  || met.isHidden || (pureVirtual && t==METHOD_CONSTRUCTOR) || (met.isVirtual && methodInBaseClass(met))) continue;

		sprintf(str,"\ncase %d: Invoke_%s_%d(__brokerbuf, peer); return true;",met.id,met.name,met.id);
		code.InsertAt(-1,str,strlen(str));

//Collect method id, name
		if (methodcount)
		{
			sprintf(methodinfoptr,",{%d,(char*)\"%s\"}",met.id,met.name);
		}
		else
		{
			sprintf(methodinfoptr,"{%d,(char*)\"%s\"}",met.id,met.name);
		}
		methodcount++;
		methodinfoptr+=strlen(methodinfoptr);
	}
	if (noConstructor && !pureVirtual)
	{
		sprintf(str,"\ncase %d: Invoke_%s_%d(__brokerbuf, peer); return true;",constructor.id, constructor.name,constructor.id);
		code.InsertAt(-1,str,strlen(str));

		if (methodcount)
		{
			sprintf(methodinfoptr,",{%d,(char*)\"%s\"}",constructor.id,constructor.name);
		}
		else
		{
			sprintf(methodinfoptr,"{%d,(char*)\"%s\"}",constructor.id,constructor.name);
		}
		methodcount++;
	}

	strcpy(str,"\ndefault: return false;\n}");
	code.InsertAt(-1,str,strlen(str));


	n=baseClass.GetSize();
	for (i=0;i<n;i++)
	{
		sprintf(str,"\nelse if (%s%sBroker::Invoke(method,__brokerbuf,peer)) return true;",baseClass[i]->base->GetName(),OBJ_POSTFIX);
		code.InsertAt(-1,str,strlen(str));
	}
	if (n) strcpy(str,"\nreturn false;\n}");
	else strcpy(str,"\nreturn paroc_broker::Invoke(method,__brokerbuf,peer);\n}");

	code.InsertAt(-1,str,strlen(str));

//Generate default constructor....
	sprintf(str,"\n%s::%s()\n{\nstatic paroc_method_info _paroc_minfo[%d]={%s};\nAddMethodInfo(CLASSUID_%s, _paroc_minfo, %d);\n}", brokername, brokername, methodcount, methodinfo, name, methodcount);
	code.InsertAt(-1,str,strlen(str));

	//Generate code for Invoke_xxx(...) to invoke object's method
	n=memberList.GetSize();
	for (i=0;i<n;i++)
	{
		int j,nb;
		bool haveReturn=false;
		int alloc_count=0;

		if (memberList[i]->GetMyAccess()!=PUBLIC || memberList[i]->Type()!=TYPE_METHOD) continue;
		Method &met=*((Method *)memberList[i]);
		int t=met.MethodType();

		if (t==METHOD_DESTRUCTOR || met.isHidden || (pureVirtual && t==METHOD_CONSTRUCTOR) || (met.isVirtual && methodInBaseClass(met)))  continue;

		met.GenerateBroker(code);
	}

	//Generate default constructor stubs

	if (!pureVirtual)
	{
		if (noConstructor)
		{
			constructor.GenerateBroker(code);
		}

		//Generate Broker init stuffs...

		sprintf(tmpcode,"\nparoc_broker *%s::_init() { return new %s; }\nparoc_broker_factory %s::_fact(_init, \"%s\");\n",brokername, brokername, brokername, name);

		code.InsertAt(-1,tmpcode,strlen(tmpcode));
	}

	char *fname=GetCodeFile()->GetFileName();
	if (endline>0 && fname!=NULL)
	{
		sprintf(str,"\n# %d \"%s\"\n",endline,fname);
		code.InsertAt(-1,str,strlen(str));
	}
	return true;


}
