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

//BEGIN Class implementation

Class::Class(char *clname, CodeFile *file): CodeData(file), DataType(clname)
{
  *classid=0;
  initDone=false;
  endid=10;
  myFile=NULL;
  startline=endline=0;
}

Class::~Class()
{
  int i,n;
  n=baseClass.GetSize();
  for (i=0;i<n;i++) if (baseClass[i]!=NULL) delete baseClass[i];
  
  n=memberList.GetSize();
  for (i=0;i<n;i++) if (memberList[i]!=NULL) delete memberList[i];

  if (myFile!=NULL) free(myFile);
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
      fprintf(stderr,"Warning: unique identifier for class %s is not specified. Automatic generated ID may cause conflict\n",name);
    }
  else 
    {
      sprintf(str,"\nconst unsigned  CLASSUID_%s=unsigned(%s);\n",name,classid);
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
      ((Method *)t)->id=endid++;
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
      Class *base=prog->FindClass(t.basename);
      if (base==NULL)
	{
	  printf("WARNING: Can not find the definition of %s in %s",t.basename, name);
	  continue;
	}
      if (base->hasMethod(x)) return true;
      if (base->methodInBaseClass(x)) return true;
    }
  return false;
}


bool Class::GenerateClient(CArrayChar &code)
{
  char tmpcode[10240];

  strcpy(tmpcode,"\n#ifndef __NO_PAROC_INTERFACE\n");
  code.InsertAt(-1,tmpcode,strlen(tmpcode));
 
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
      met->GenerateClient(code);
    }

  strcpy(tmpcode,"\n#endif\n");
  code.InsertAt(-1,tmpcode,strlen(tmpcode));

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

  if (interface)
    strcpy(str,"\n#ifndef __NO_PAROC_INTERFACE\n");
  else 
    strcpy(str,"\n#ifndef __NO_PAROC_SERVER\n");
  
  code.InsertAt(-1,str, strlen(str));

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
		
	  strcat(tmpcode,base.basename);
	  if (!interface) strcat(tmpcode, OBJ_POSTFIX);
	  if (i<n-1) strcat(tmpcode,", ");
    }
  if (n) strcat(tmpcode,"\n{\npublic:");
  else if (interface)
    {
      sprintf(str," virtual public %s\n{\npublic:", Class::interface_base);
      strcat(tmpcode, str);
    }
  else strcat(tmpcode," virtual public paroc_object\n{\npublic:");

  code.InsertAt(-1,tmpcode,strlen(tmpcode));
  *tmpcode=0;

  char *accessstr[3]={"\npublic:","\nprotected:","\nprivate:"};
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
      memberList[i]->GenerateHeader(code,interface);
      if (!defaultconstructor)
	{
	  if (memberList[i]->Type()==TYPE_METHOD)
	    {
	      Method *t=(Method *)memberList[i];
	      if (t->MethodType()==METHOD_CONSTRUCTOR)
		{
		  if ( ((Constructor *)t)->isDefault()) defaultconstructor=true;
		}
	    }
	}

    }

  if (interface)
    {
      sprintf(str,"\npublic:\n\tvirtual const char *ClassName() { return \"%s\"; };",name);
      code.InsertAt(-1,str,strlen(str));

      //Generate constructor from paroc_accesspoint...

      sprintf(str,"\npublic:\n\t%s(const paroc_accesspoint &p)",name);
      code.InsertAt(-1,str,strlen(str));
  
      int n=baseClass.GetSize();
      if (n)
	{
	  CArrayString bases;
	  bases.SetSize(n);
	  for (int i=0;i<n;i++)  strcpy(bases[i], baseClass[i]->basename);
	  CodeFile *prog=GetCodeFile();
	  prog->FindAllBaseClassName(*this, bases,true);
	  
	  n=bases.GetSize();
	  strcpy(tmpcode," : ");
	  for (int j=0;j<n;j++)
	    {
	      strcat(tmpcode,bases[j]);
	      if (j<n-1) strcat(tmpcode,"(_paroc_nobind) ,");
	      else  strcat(tmpcode,"(_paroc_nobind)");
	    }
	  code.InsertAt(-1,tmpcode,strlen(tmpcode));
	}

      strcpy(str," { Bind(p); };\n");
      code.InsertAt(-1,str,strlen(str));

      //Generate constructor from the interface binding
      sprintf(str,"\n\t%s(const %s &inf)",name, Class::interface_base);
      code.InsertAt(-1,str,strlen(str));
      code.InsertAt(-1,tmpcode,strlen(tmpcode));
      strcpy(str," { SetOD(inf.GetOD()); Bind(inf.GetAccessPoint()); };\n");
      code.InsertAt(-1,str,strlen(str));

     //Generate constructor from the object side binding
      sprintf(str,"\n\t%s(const paroc_object *obj)",name);
      code.InsertAt(-1,str,strlen(str));
      code.InsertAt(-1,tmpcode,strlen(tmpcode));
      strcpy(str," { Bind(obj->GetAccessPoint()); };\n");
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


  strcpy(str,"\n};\n#endif\n");
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

  strcpy(str,"\n#ifndef __NO_PAROC_BROKER\n");
  code.InsertAt(-1,str,strlen(str));

  char *outfile=GetCodeFile()->GetOutputName();
  if (outfile!=NULL)
    {
      int lines=CountCodeLines(code);
      sprintf(tmpcode,"\n# %d \"%s\"\n",lines+3, outfile);
      code.InsertAt(-1,tmpcode,strlen(tmpcode));
    }
  sprintf(brokername,"%s%sBroker",name,OBJ_POSTFIX);

   int n=baseClass.GetSize();
  if (n==0) sprintf(tmpcode,"\n\nclass %s: virtual public %s",brokername, Class::broker_base); 
  else
    {
      sprintf(tmpcode,"\n\nclass %s: ",brokername);
      for (i=0;i<n;i++)
	{
	  if (baseClass[i]->baseVirtual) strcat(tmpcode,"virtual ");
	  strcat(tmpcode,"public ");
	  strcat(tmpcode, baseClass[i]->basename);
	  strcat(tmpcode, OBJ_POSTFIX);
	  strcat(tmpcode, "Broker");
	  if (i<n-1) strcat(tmpcode,", ");
	}
    }
  sprintf(str,"\n{\npublic:\n\tvirtual bool Invoke(unsigned method[3],  paroc_buffer &__brokerbuf, paroc_connection *peer);");
  strcat(tmpcode,str);
 
  strcat(tmpcode,"\nprotected:");
  code.InsertAt(-1,tmpcode,strlen(tmpcode));

  n=memberList.GetSize();
  for (i=0;i<n;i++)
    {
      
	  if (memberList[i]->GetMyAccess()!=PUBLIC || memberList[i]->Type()!=TYPE_METHOD) continue;
	  Method &met=*((Method *)memberList[i]);
	  met.GenerateBrokerHeader(code);
    }

  //Propagate object to parent....
  //  sprintf(str,"\n\t%s%s *obj;\n\tvoid SetImpObject(%s%s *newobj);",name,OBJ_POSTFIX,name,OBJ_POSTFIX);
  //  code.InsertAt(-1,str,strlen(str));

  strcpy(str,"}\n;\n#endif\n");
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

  strcpy(str,"\n#ifndef __NO_PAROC_BROKER\n");
  code.InsertAt(-1,str, strlen(str));

  sprintf(brokername,"%s%sBroker",name,OBJ_POSTFIX);
  //now...the implementation....

  sprintf(str,"\nbool %s::Invoke(unsigned method[3], paroc_buffer &__brokerbuf, paroc_connection *peer)\n{\n\tif (*method==CLASSUID_%s) switch(method[1])\n\t{",brokername,name);
  code.InsertAt(-1,str,strlen(str));
  int n=memberList.GetSize();
  for (i=0;i<n;i++)
    {
      if (memberList[i]->GetMyAccess()!=PUBLIC || memberList[i]->Type()!=TYPE_METHOD) continue;
      Method &met=*((Method *)memberList[i]);

      if (met.MethodType()==METHOD_DESTRUCTOR || (met.isVirtual && methodInBaseClass(met)) || met.isHidden) continue;
      sprintf(str,"\n\t\tcase %d: Invoke_%s_%d(__brokerbuf, peer); return true;",met.id,name,met.id); 
      code.InsertAt(-1,str,strlen(str));
    }

  strcpy(str,"\n\t\tdefault: return false;\n\t}");
  code.InsertAt(-1,str,strlen(str));

  
  n=baseClass.GetSize();
  for (i=0;i<n;i++)
    {
      sprintf(str,"\n\telse if (%s%sBroker::Invoke(method,__brokerbuf,peer)) return true;",baseClass[i]->basename,OBJ_POSTFIX);
      code.InsertAt(-1,str,strlen(str));
    }
  strcpy(str,"\n\treturn false;\n}");
  
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
	
      if (met.MethodType()==METHOD_DESTRUCTOR|| (met.isVirtual && methodInBaseClass(met)) || met.isHidden) continue;

      met.GenerateBroker(code);
    }

  code.InsertAt(-1,"\n#endif\n",8);
  char *fname=GetCodeFile()->GetFileName();
   if (endline>0 && fname!=NULL)
    {
      sprintf(str,"\n# %d \"%s\"\n",endline,fname);
      code.InsertAt(-1,str,strlen(str));
    }
  return true;
  
  
}
