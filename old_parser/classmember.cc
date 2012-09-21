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

//Begin Param implementation

Param::Param(DataType *ptype)
{
	name[0]=0;
	mytype=ptype;

	paramSize=marshalProc=defaultVal=NULL;
	isRef=isConst=isInput=isOutput=false;
}

Param::Param()
{
	name[0]=0;
	mytype=NULL;

	paramSize=marshalProc=defaultVal=NULL;
	isRef=isConst=isInput=isOutput=false;
}

Param::~Param()
{
	if (paramSize!=NULL) free(paramSize);
	if (marshalProc!=NULL) free(marshalProc);
	if (defaultVal!=NULL) free(defaultVal);
}

bool Param::Match(Param *p)
{
	return (paroc_utils::isEqual(name,p->GetName()));
}

bool Param::InParam()
{
	if (isInput || isConst) return true;
	if (isOutput) return false;
	return true;
}

bool Param::OutParam()
{
	if (isConst) return false;
	if (isOutput) return true;
	if (isInput) return false;
	return (isRef || IsPointer() || mytype->IsArray());
}

bool Param::IsPointer()
{
	return (mytype->IsPointer()>0);
}

bool Param::IsRef()
{
	return isRef;
}

bool Param::IsConst()
{
	return isConst;
}

void Param::SetType(DataType *type)
{
	mytype=type;
}

DataType *Param::GetType()
{
	return mytype;
}

char *Param::GetName()
{
	return name;
}

char *Param::GetDefaultValue()
{
	return defaultVal;
}

int  Param::GetAttr()
{
	return attr;
}

bool Param::CanMarshal()
{
	if (mytype==NULL) return false;
	int stat=mytype->CanMarshal();
	if (marshalProc!=NULL || stat==1 || (stat==2 && paramSize!=NULL)) return true;
	return false;

}

bool Param::DeclareParam(char *output, bool header)
{
	if (mytype==NULL) return false;

	if (isConst)
	{
		strcpy(output,"const ");
		output+=strlen(output);
	}
	char tmpvar[1024];
	if (isRef) sprintf(tmpvar,"&%s", name);
	else strcpy(tmpvar,name);

	if (!mytype->GetDeclaration(tmpvar, output)) return false;
	if (defaultVal!=NULL && header)
	{
		strcat(output,"=");
		strcat(output,defaultVal);
	}
	return true;
}

bool Param::DeclareVariable(char *output, bool &reformat, bool allocmem)
{
	if (mytype==NULL) return false;

	int nptr=mytype->IsPointer();
	if (nptr==1 && paramSize==NULL)
	{
		DataType *base=mytype->GetBaseType();
		assert(base!=NULL);
		if (!base->GetDeclaration(name, output)) return false;
		if (base->IsParClass()) strcat(output,"(paroc_interface::_paroc_nobind)");
		strcat(output,";\n");
		reformat=true;
	}
	else
	{
		if (!mytype->GetDeclaration(name, output)) return false;
		if (mytype->IsParClass()) strcat(output,"(paroc_interface::_paroc_nobind)");
		reformat=false;
		strcat(output,";\n");

		//Check and allocate memory....
		if (allocmem && paramSize!=NULL && nptr)
		{
			char decl[1024];
			DataType *base=mytype->GetBaseType();
			assert(base!=NULL);
			char basetype[1024];
			base->GetDeclaration(NULL,basetype);

			if (nptr==1 && base->IsParClass())
				sprintf(decl, "paroc_interface_container<%s> __paroc_container_%s(%s);\n%s =__paroc_container_%s;\n", basetype,name,paramSize,name,name);
			else
			{
				char tmpstr[1024];
				strcpy(tmpstr,base->GetName());
				for (int i=1;i<nptr;i++) strcat(tmpstr,"*");
				sprintf(decl, "paroc_container<%s> __paroc_container_%s(%s);\n%s=__paroc_container_%s;\n", tmpstr,name ,paramSize,   name, name);

			}
			strcat(output,decl);
		}
	}
	return true;
}

bool Param::DeclareVariable(char *output)
{
	if (mytype==NULL) return false;

	char tmpvar[1024];
	if (isRef&&!GetType()->IsParClass()) sprintf(tmpvar,"&%s", name);
	else strcpy(tmpvar,name);

	if (mytype->GetDeclaration(tmpvar, output))
	{
		strcat(output,";\n");
		return true;
	}
	return false;
}

bool Param::Marshal(char *bufname, bool reformat,bool inf_side, CArrayChar &output)
{
	if (mytype==NULL) return false;

	char tmpvar[1024];
	if (isConst)
	{
		*tmpvar=0;
//             *tmpvar='(';
//       mytype->GetCastType(tmpvar+1);
//       if (isRef) strcat(tmpvar,"&");
//       strcat(tmpvar,")");
	}
	else *tmpvar=0;

	if (reformat) strcat(tmpvar,"&");

	strcat(tmpvar,name);

	int flags=(inf_side)? FLAG_INPUT : 0;
	flags|=FLAG_MARSHAL;

	char sizeinfo[1024];
	*sizeinfo=0;

	if (paramSize!=NULL && !reformat)
	{
		char decl[1024];
		sprintf(decl, "int __paroc_size1_%s=%s;\n%s.Push(\"%sSize\",\"int\",1);\n%s.Pack(& __paroc_size1_%s,1);\n%s.Pop();\n",name,paramSize,bufname, name, bufname,name, bufname);
		sprintf(sizeinfo,"__paroc_size1_%s",name);

		output.InsertAt(-1,decl,strlen(decl));
	}

	if (marshalProc!=NULL)
	{
		char tmpcode[1024];
		sprintf(tmpcode,"%s(%s,%s, %s, %d, 0);\n",marshalProc,bufname,tmpvar, (*sizeinfo==0)? "0" : sizeinfo,flags);
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
	}
	else
	{
		mytype->Marshal(tmpvar,bufname,(*sizeinfo==0)? NULL : sizeinfo,output);
	}
	return true;
}

bool Param::UnMarshal(char *bufname, bool reformat, bool alloc_mem, bool inf_side, CArrayChar &output)
{
	if (mytype==NULL) return false;

	int flags=(inf_side)? 0: FLAG_INPUT;

	char tmpvar[1024];

	*tmpvar=0;
	if (reformat) strcat(tmpvar,"&");
	strcat(tmpvar,name);

	char sizeinfo[1024];
	*sizeinfo=0;

	if (paramSize!=NULL && !reformat)
	{
		char decl[1024];
		sprintf(decl, "int __paroc_size2_%s;\n%s.Push(\"%sSize\",\"int\",1);\n \n%s.UnPack(& __paroc_size2_%s,1);\n%s.Pop();\n",name,bufname, name, bufname,name, bufname);

		sprintf(sizeinfo,"__paroc_size2_%s",name);

		output.InsertAt(-1,decl,strlen(decl));

		//check to alloc the memory
		int nptr=mytype->IsPointer();
		if (alloc_mem && nptr)
		{
			char alloccode[1024];
			DataType *base=mytype->GetBaseType();
			assert(base!=NULL);
			char basetype[1024];
			base->GetDeclaration(NULL,basetype);

			if (nptr==1 && base->IsParClass())
				sprintf(alloccode, "paroc_interface_container<%s> __paroc_container_%s(__paroc_size2_%s);\n %s=__paroc_container_%s;\n", basetype,name,name,name, name);
			else
			{
				//	      sprintf(alloccode, "paroc_container<typeof(*%s)> __paroc_container_%s(%s,__paroc_size2_%s);\n", name,name,name,name);
				char tmpstr[1024];
				strcpy(tmpstr,base->GetName());
				for (int i=1;i<nptr;i++) strcat(tmpstr,"*");
				sprintf(alloccode, "paroc_container<%s> __paroc_container_%s(__paroc_size2_%s);\n%s=__paroc_container_%s;\n", tmpstr,name,name,name,name);
			}
			output.InsertAt(-1,alloccode,strlen(alloccode));
		}
	}
	if (marshalProc!=NULL)
	{
		char tmpcode[1024];

		sprintf(tmpcode,"%s(%s,%s,%s,%d,%s);",marshalProc,bufname,tmpvar, (*sizeinfo==0)?  "0" : sizeinfo,flags,(inf_side ? "0" : "&_internal_mem"));
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
	}
	else
		mytype->DeMarshal(tmpvar,bufname,(*sizeinfo==0)? NULL : sizeinfo,output);

	return true;
}

bool Param::UserProc(char *output)
{
	if (mytype==NULL) return false;

	*output=0;
	if (marshalProc==0) return false;
	char decl[1024];

	mytype->GetDeclaration("param",decl);
	sprintf(output,"void %s(paroc_buffer &buf, %s, int hint,  bool marshal);" , marshalProc, decl);
	return true;


}
//END Param implementation



//BEGIN OD - object description class
ObjDesc::ObjDesc()
{
	odstr=NULL;
}
ObjDesc::~ObjDesc()
{
	if (odstr!=NULL) free(odstr);
}

void ObjDesc::Generate(char *code)
{
	code[0]=0;
	if (odstr==NULL) return;
	strcpy(code,odstr);
}

void ObjDesc::SetCode(char *code)
{
	if (odstr!=NULL) free(odstr);
	odstr=(code==NULL)? NULL : strdup(code);
}

//END ObjectDesc - object description class

// BEGIN ClassMember class implementation....
ClassMember::ClassMember(Class *cl, AccessType myaccess)
{
	accessType=myaccess;
	myclass=cl;
	line=-1;
}

ClassMember::~ClassMember()
{
}


AccessType ClassMember::GetMyAccess()
{
	return accessType;
}

Class * ClassMember::GetClass()
{
	return myclass;
}

void ClassMember::SetLineInfo(int linenum)
{
	line=linenum;
}

void ClassMember::GenerateClient(CArrayChar &output)
{
}

void ClassMember::GenerateHeader(CArrayChar &output, bool interface)
{
	char *fname;
	if (line>0 && (fname=myclass->GetFileInfo())!=NULL)
	{
		char str[1024];
		sprintf(str,"\n# %d \"%s\"\n",line,fname);
		output.InsertAt(-1,str,strlen(str));
	}

}

// END  ClassMember implementation....

//Implement Attribute class
Attribute::Attribute(Class *cl, AccessType myaccess): ClassMember(cl, myaccess), attributes(0,1)
{
}

void Attribute::GenerateHeader(CArrayChar &output, bool interface)
{
	if (interface) return;
	ClassMember::GenerateHeader(output, interface);

	char tmp[1024];
	int n=attributes.GetSize();
	for (int i=0;i<n;i++)
	{
		Param &p=*(attributes[i]);
		p.DeclareVariable(tmp);
		output.InsertAt(-1,tmp,strlen(tmp));
	}
}

Param *Attribute::NewAttribute()
{
	Param *t=new Param;
	attributes.InsertAt(-1,t);
	return t;
}

//Directives inside a parallel class

Directive::Directive(Class *cl, char *directive): ClassMember(cl, PUBLIC)
{
	code=strdup(directive);
}

Directive::~Directive()
{
	if (code!=NULL) free(code);
}

void Directive::GenerateHeader(CArrayChar &output, bool interface)
{
	if (code!=NULL)
	{
		output.InsertAt(-1,"\n",1);
		output.InsertAt(-1,code,strlen(code));
		output.InsertAt(-1,"\n",1);
	}
}



// BEGIN Method class implementation....

Method::Method(Class *cl, AccessType myaccess): ClassMember(cl, myaccess), returnparam(NULL)
{
	name[0]=0;
	id=0;
	invoketype=invokesync;
	isConcurrent=false;
	isMutex=false;
	isHidden=false;
	isVirtual=false;
	isPureVirtual=false;
}

Method::~Method()
{
	int n,i;
	n=params.GetSize();
	for (i=0;i<n;i++) if (params[i]!=NULL) delete params[i];
}

int Method::CheckMarshal()
{
	if (GetMyAccess()!=PUBLIC || isHidden) return 0;

	if (MethodType()==METHOD_NORMAL && !returnparam.CanMarshal()) return -1;
	int n=params.GetSize();
	Class *cl=GetClass();

	for (int i=0;i<n;i++)
	{
		if (params[i]->GetType()->IsParClass() && !params[i]->IsRef())
		{
			fprintf(stderr,"%s:%d: ERROR in %s::%s : parallel object '%s' must be passed as reference to the remote object.\n",  cl->GetFileInfo(), line, cl->GetName(), name,params[i]->GetName());
			return(i+1);
		}
		if (!params[i]->CanMarshal()) return (i+1);
	}
	return 0;

}

void Method::GenerateReturn(CArrayChar &output, bool header)
{
	DataType *type=returnparam.GetType();
	if (type==NULL) return;
	if (header && isVirtual) output.InsertAt(-1,"virtual ",8);
	else if (!header) output.InsertAt(-1,"\n",1);

	if (returnparam.GetType()->IsParClass())
	{
		fprintf(stderr,"%s:%d: WARNING in %s::%s : the return argument '%s' is treated as a reference to a parallel object.\n", GetClass()->GetFileInfo(), line, GetClass()->GetName(), (const char*)name, returnparam.GetType()->GetName());
	}
	if (returnparam.IsRef()/*&&!returnparam.GetType()->IsParClass()*/)
	{
		fprintf(stderr,"%s:%d: ERROR in %s::%s : methods of parallel objects cannot technically return a reference.\n", GetClass()->GetFileInfo(), line, GetClass()->GetName(), (const char*)name);
		exit(1);
	}

	char tmp[1024];
	type->GetDeclaration(NULL,tmp);
	if (returnparam.IsConst())sprintf(tmp, "const %s", tmp);
	output.InsertAt(-1,tmp, strlen(tmp));
	output.InsertAt(-1," ");
}

void Method::GeneratePostfix(CArrayChar &output, bool header)
{
	if (header) output.InsertAt(-1,";",1);
}

void Method::GenerateName(CArrayChar &output, bool header)
{
	if (header) output.InsertAt(-1,name,strlen(name));
	else
	{
		char str[256];
		sprintf(str,"%s::%s",GetClass()->GetName(),name);
		output.InsertAt(-1,str,strlen(str));
	}
}

void Method::GenerateArguments(CArrayChar &output, bool header)
{
	char tmpcode[10240];

	output.InsertAt(-1,"(",1);
	int nb=params.GetSize();
	for (int j=0;j<nb;j++)
	{
		Param &p=*(params[j]);
		p.DeclareParam(tmpcode, header);
		if (j<nb-1) strcat(tmpcode,", ");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
	}
	output.InsertAt(-1,")",1);
}


void Method::GenerateClientPrefixBody(CArrayChar &output)
{

}

void Method::GenerateClient(CArrayChar &output)
{

	if ((isVirtual && GetClass()->methodInBaseClass(*this)) || isHidden) return;

	//Check if we can generate marshalling stubs....
	int t=CheckMarshal();
	if (t!=0)
	{
		Class *cl=GetClass();
		if (t==-1)
			fprintf(stderr,"%s:%d: ERROR in %s::%s: unable to marshal the return argument.\n", cl->GetFileInfo(),line, cl->GetName(), name);
		else
			fprintf(stderr,"%s:%d: ERROR in %s::%s: unable to marshal argument %d.\n",  cl->GetFileInfo(), line, cl->GetName(), name,t);
		exit(1);
	}

	//  Method &met=*memberList[i]->GetMethod();
	char tmpcode[10240];
	char str[1024];

	char *clname=GetClass()->GetName();
	int j,nb=params.GetSize();
	//      Param &ret=met.returnparam;

	GenerateReturn(output,false);
	GenerateName(output, false);
	GenerateArguments(output,false);
	GeneratePostfix(output,false);

	output.InsertAt(-1,"\n{",2);

	GenerateClientPrefixBody(output);

	//Generate method body ---interface part
	int invoke_code=0;
	bool waitreturn=false;
	if (MethodType()==METHOD_CONSTRUCTOR)
	{
		invoke_code|=INVOKE_CONSTRUCTOR | INVOKE_SYNC | INVOKE_MUTEX;
		waitreturn=true;
	}
	else
	{
		if (invoketype==invokesync || (invoketype==autoselect && hasOutput()) )
		{
			invoke_code|=INVOKE_SYNC;
			waitreturn=true;
		}
		//      else  invoke_code|=INVOKE_ASYNC;

		if (isMutex) invoke_code|=INVOKE_MUTEX;
		else if (isConcurrent) invoke_code|=INVOKE_CONC;
	}

	sprintf(tmpcode,"\nparoc_mutex_locker __paroc_lock(_paroc_imutex);\n__paroc_buf->Reset();\nparoc_message_header __paroc_buf_header(CLASSUID_%s,%d,%d, \"%s\");\n__paroc_buf->SetHeader(__paroc_buf_header);\n",clname, id, invoke_code, name);
	output.InsertAt(-1,tmpcode,strlen(tmpcode));

	//Generate marshalling stub
	for (j=0;j<nb;j++)
	{
		Param &p=*(params[j]);
		if (p.InParam())
		{
			p.Marshal("(*__paroc_buf)", false,true,output);
		}
	}

	//Finish marshaling buffer....now transmit the buffer....

	strcpy(tmpcode,"\nparoc_Dispatch(__paroc_buf);");
	output.InsertAt(-1,tmpcode,strlen(tmpcode));

	if (waitreturn)
	{
#ifdef OD_DISCONNECT
		strcpy(tmpcode,"\n\tif(od.getCheckConnection()){\n\t\tif(!RecvCtrl())paroc_exception::paroc_throw_errno();\n\t}");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
		strcpy(tmpcode,"\n\telse\n");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
#endif
		strcpy(tmpcode,"\t{\n\t\tif (!__paroc_buf->Recv(*__paroc_combox)) paroc_exception::paroc_throw_errno();\n\t}\n\t\n\tparoc_buffer::CheckAndThrow(*__paroc_buf);\n");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
		for (j=0;j<nb;j++)
		{
			Param &p=*(params[j]);
			if (p.OutParam())
			{
				p.UnMarshal("(*__paroc_buf)",false,false, true, output);
			}
		}

		if (MethodType()==METHOD_NORMAL && !returnparam.GetType()->Same("void"))
		{
			bool reformat;
			returnparam.DeclareVariable(tmpcode,reformat,false);
			output.InsertAt(-1,tmpcode,strlen(tmpcode));

			returnparam.UnMarshal("(*__paroc_buf)",reformat,true, true, output);
			strcpy(tmpcode,"\n__paroc_buf->Reset();\nreturn ");
			if (reformat) strcat(tmpcode,"&");
			strcat(tmpcode,returnparam.name);
			strcat(tmpcode,";\n}\n");
			output.InsertAt(-1,tmpcode,strlen(tmpcode));
		}
		else
		{
			strcpy(tmpcode,"\n__paroc_buf->Reset();\n}\n");
			output.InsertAt(-1,tmpcode,strlen(tmpcode));
		}
	}
	else
	{
		// Check that we are not waiting for a returning param
		for (j=0;j<nb;j++) {
			if (params[j]->OutParam() && !params[j]->GetType()->IsParClass() ) {
				Class *cl=GetClass();
				fprintf(stderr,"%s:%d: ERROR in %s::%s: Asynchronous method cannot have an output (parameter %s must be declared with [in])\n",cl->GetFileInfo(),line, cl->GetName(), name, params[j]->name);
				exit(1);
			}
		}
		if (MethodType()==METHOD_NORMAL &&!returnparam.GetType()->Same("void")) {
			Class *cl=GetClass();
			fprintf(stderr,"%s:%d: ERROR in %s::%s: Asynchronous method must return void\n",cl->GetFileInfo(),line, cl->GetName(), name);
			exit(1);
		}
#ifdef OD_DISCONNECT
		strcpy(tmpcode,"\n\tint time_alive, time_control, oldTime;\nod.getCheckConnection(time_alive, time_control);\n\t");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
		strcpy(tmpcode,"\n\tif(time_alive > 0 && time_control > 0 ){\n\t\toldTime=__paroc_combox->GetTimeout();\n\t\t__paroc_combox->SetTimeout(time_alive);\n\t\t__paroc_combox->RecvAck();\n\t\t__paroc_combox->SetTimeout(oldTime);\n\t}");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
#else
		strcpy(tmpcode,"__paroc_buf->Reset();\n}\n");
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
#endif
	}
}

void Method::GenerateHeader(CArrayChar &output, bool interface)
{
	int type=MethodType();
	if (interface)
	{
		if (type==METHOD_DESTRUCTOR || GetMyAccess()!=PUBLIC || isHidden) return;
		if (isVirtual && GetClass()->methodInBaseClass(*this))
		{
			return;
		}
	}
	ClassMember::GenerateHeader(output, interface);
	GenerateReturn(output, true);

	if (!interface && type!=METHOD_NORMAL)
	{
		char str[256];
		sprintf(str,"%s%s",name,OBJ_POSTFIX);
		output.InsertAt(-1,str,strlen(str));
	}
	else GenerateName(output, true);
	GenerateArguments(output, true);

	if (isPureVirtual && !interface)
	{
		output.InsertAt(-1,"=0",2);
	}

	GeneratePostfix(output,true);
}

void Method::GenerateBrokerHeader(CArrayChar &output)
{
	int type=MethodType();
	if (type==METHOD_DESTRUCTOR || GetMyAccess()!=PUBLIC || isHidden) return;
	if (isVirtual && GetClass()->methodInBaseClass(*this)) return;

	char str[1024];
	sprintf(str,"\nvoid Invoke_%s_%d(paroc_buffer &__paroc_buf, paroc_connection *__interface_output);",name , id);
	output.InsertAt(-1,str,strlen(str));
}

void Method::GenerateBroker(CArrayChar &output)
{
	int type=MethodType();
	if (type==METHOD_DESTRUCTOR || GetMyAccess()!=PUBLIC || isHidden) return;
	if (isVirtual && GetClass()->methodInBaseClass(*this)) return;

	Class *cl=GetClass();
	char *clname=cl->GetName();

	int nb=params.GetSize();

	char brokername[256];
	sprintf(brokername,"%s%sBroker",cl->GetName(),OBJ_POSTFIX);

	paroc_array<bool>  reformat;
	reformat.SetSize(nb);


	//Now generate method wrappers...
	char str[1024];

	sprintf(str,"\nvoid %s::Invoke_%s_%d(paroc_buffer &__paroc_buf, paroc_connection *__interface_output)\n{",brokername,name, id);

	output.InsertAt(-1,str,strlen(str));

	char methodcall[1024];
	bool haveReturn=false;

	if (type==METHOD_CONSTRUCTOR)
	{
		//Constructor...create object now...
		sprintf(methodcall,"\nobj=new %s%s(",clname,OBJ_POSTFIX);
	}
	else if (type!=METHOD_NORMAL || returnparam.GetType()->Same("void"))
	{
		sprintf(methodcall,"\n%s%s * _paroc_obj=dynamic_cast<%s%s *>(obj);\n_paroc_obj->%s(",clname,OBJ_POSTFIX,clname,OBJ_POSTFIX, name);
	}
	else
	{
		//CHECK HERE....
		char retdecl[1024];
		char tmpvar[1024];
		if (returnparam.isRef) sprintf(tmpvar,"&%s",returnparam.GetName());
		else strcpy(tmpvar,returnparam.GetName());
		returnparam.GetType()->GetDeclaration(tmpvar,retdecl);

		if (returnparam.isRef)
			sprintf(methodcall,"\n%s%s * _paroc_obj=dynamic_cast<%s%s *>(obj); \n%s=_paroc_obj->%s(",clname,OBJ_POSTFIX,clname,OBJ_POSTFIX,retdecl, name);
		else if (returnparam.GetType()->IsParClass())
			sprintf(methodcall,"\n%s(paroc_interface::_paroc_nobind);\n%s%s * _paroc_obj=dynamic_cast<%s%s *>(obj);\n%s=_paroc_obj->%s(",retdecl,clname,OBJ_POSTFIX,clname,OBJ_POSTFIX, tmpvar,name);
		else
			sprintf(methodcall,"\n%s;\n%s%s * _paroc_obj=dynamic_cast<%s%s *>(obj);\n%s=_paroc_obj->%s(",retdecl, clname, OBJ_POSTFIX, clname, OBJ_POSTFIX, tmpvar, name);

		haveReturn=true;
	}

	bool have_memspool=false;

	//unmarhall and allocate memory for inpput arguments first
	for (int j=0;j<nb;j++)
	{
		Param &p=*(params[j]);
		if (!p.InParam()) continue;
		char decl[1024];

		p.DeclareVariable(decl,reformat[j],false);
		output.InsertAt(-1, decl, strlen(decl));

		strcpy(str,"__paroc_buf");
		if (p.marshalProc!=NULL && !have_memspool)
		{
			strcpy(str,"\nparoc_memspool _internal_mem;");
			output.InsertAt(-1,str,strlen(str));
			have_memspool=true;
		}
		p.UnMarshal("__paroc_buf",reformat[j],true,false,output);
	}

	//Then, declare and alloc mem  for output-only arguments

	for (int j=0;j<nb;j++)
	{
		Param &p=*(params[j]);
		if (!p.InParam())
		{
			char decl[1024];

			p.DeclareVariable(decl,reformat[j],true);
			output.InsertAt(-1, decl, strlen(decl));
		}

		if (reformat[j])  strcat(methodcall," &");
		strcat(methodcall,p.GetName());
		if (j<nb-1) strcat(methodcall,", ");
	}

	strcat(methodcall,");");

	//now....generate the call...
	output.InsertAt(-1,methodcall,strlen(methodcall));
	sprintf(str,"\nif (__interface_output!=0) \n{\n__paroc_buf.Reset();\nparoc_message_header __paroc_buf_header(\"%s\");\n__paroc_buf.SetHeader(__paroc_buf_header);\n", name);
	output.InsertAt(-1,str,strlen(str));

	for (int j=0;j<nb;j++)
	{
		Param &p=*(params[j]);
		if (p.OutParam())
		{
			p.Marshal("__paroc_buf", reformat[j], false, output);
		}
	}
	if (haveReturn)
	{
		returnparam.Marshal("__paroc_buf",false,false, output);
	}
	strcpy(str,"\nif (!__paroc_buf.Send(__interface_output)) paroc_exception::paroc_throw_errno();\n}\n}\n");
	output.InsertAt(-1,str,strlen(str));
}

Param *Method::AddNewParam()
{
	Param *t=new Param;
	params.InsertAt(-1,t);
	return t;
}

bool Method::hasInput()
{
	int np=params.GetSize();
	Param **pr=params;
	for (int i=0;i<np;i++,pr++) if ((*pr)->InParam()) return true;
	return false;
}

bool Method::hasOutput()
{
	if (MethodType()==METHOD_NORMAL)
	{
		if (!returnparam.GetType()->Same("void")) return true;
	}

	int np=params.GetSize();
	Param **pr=params;
	for (int i=0;i<np;i++,pr++) if ((*pr)->OutParam()) return true;
	return false;
}

bool Method::operator ==(Method &other)
{
	if (isVirtual!=other.isVirtual) return false;
	if (GetMyAccess()!=other.GetMyAccess()) return false;
	if (MethodType()!=other.MethodType()) return false;
	if ( !paroc_utils::isEqual(name,other.name) ) return false;


	DataType *type1=returnparam.GetType();
	DataType *type2=other.returnparam.GetType();

	if ((type1==NULL || type2==NULL) && type1!=type2) return false;

	if (!type1->Same(type2)) return false;

	int n=params.GetSize();
	if (n!=other.params.GetSize()) return false;
	for (int i=0;i<n;i++)
	{
		Param &t1=*params[i];
		Param &t2=*other.params[i];
		if (!t1.GetType()->Same(t2.GetType())) return false;
	}
	return true;
}

// END Method class implementation....

//Implement Constructor class

Constructor::Constructor(Class *cl, AccessType myaccess):Method(cl, myaccess)
{
	strcpy(name, cl->GetName());
}

bool Constructor::isDefault()
{
	return (params.GetSize()==0);
}


ObjDesc & Constructor::GetOD()
{
	return od;
}

void Constructor::GenerateHeader(CArrayChar &output, bool interface)
{
	Method::GenerateHeader(output,interface);

	//SEPARATE allocation from invocation
	if (interface)
	{
		char str[1024];
		strcpy(str,"\nvoid _paroc_Construct");
		output.InsertAt(-1,str,strlen(str));
		GenerateArguments(output, true);
		GeneratePostfix(output,true);
	}
}

void Constructor::GenerateReturn(CArrayChar &output, bool header)
{
}

void Constructor::GeneratePostfix(CArrayChar &output, bool header)
{
	if (header)
	{
		output.InsertAt(-1,";",1);
		return;
	}

	CArrayBaseClass &baseClass=GetClass()->baseClass;
	int n=baseClass.GetSize();
	if (n)
	{
		CArrayClass bases;
		bases.SetSize(n);
		for (int i=0;i<n;i++)  bases[i]=baseClass[i]->base;
		Class *cl=GetClass();
		CodeFile *prog=cl->GetCodeFile();
		prog->FindAllBaseClass(*cl, bases,true);

		n=bases.GetSize();
		char tmpcode[10240];
		strcpy(tmpcode," : ");
		for (int j=0;j<n;j++)
		{
			strcat(tmpcode,bases[j]->GetName());
			if (j<n-1) strcat(tmpcode,"(_paroc_nobind) ,");
			else  strcat(tmpcode,"(_paroc_nobind)");
		}
		output.InsertAt(-1,tmpcode,strlen(tmpcode));
	}
}

void Constructor::GenerateClientPrefixBody(CArrayChar &output)
{
	char tmpcode[10240];
	od.Generate(tmpcode);
//   if (baseClass.GetSize()>=2)
//     {
//       sprintf(str,"\n\t%s::Allocate();",baseClass[0]->basename);
//       strcat(tmpcode,str);
//     } else

	strcat(tmpcode,"\nAllocate();");
	output.InsertAt(-1, tmpcode, strlen(tmpcode));

	//SEPARATE ALLOCATION FROM INVOCATION.....
	strcpy(tmpcode,"\n_paroc_Construct(");
	int nb=params.GetSize();
	for (int j=0;j<nb;j++)
	{
		Param &p=*(params[j]);
		strcat(tmpcode,p.GetName());
		if (j<nb-1) strcat(tmpcode,", ");
	}

	strcat(tmpcode,");\n}");
	output.InsertAt(-1, tmpcode, strlen(tmpcode));

	sprintf(tmpcode,"\nvoid %s::_paroc_Construct",GetClass()->GetName());
	output.InsertAt(-1, tmpcode, strlen(tmpcode));
	GenerateArguments(output,false);

	strcpy(tmpcode,"\n{");
	output.InsertAt(-1, tmpcode, strlen(tmpcode));
}

//Implement Destructor class

Destructor::Destructor(Class *cl, AccessType myaccess): Method(cl, myaccess)
{
}
void Destructor::GenerateClient(CArrayChar &output)
{
	//Ignore the destructor of the interface....
}

void Destructor::GenerateReturn(CArrayChar &output, bool header)
{
	if (header) output.InsertAt(-1,"~",1);
	else output.InsertAt(-1,"\n~",2);
}

// BEGIN  BaseClass implementation....

BaseClass::BaseClass(Class *name, AccessType basemode, bool onlyVirtual)
{
	base=name;
	type=basemode;
	baseVirtual=onlyVirtual;
}
// END  BaseClass implementation....

