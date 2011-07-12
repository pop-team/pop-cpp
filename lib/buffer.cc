/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of message buffer base class\
 */
#include <string.h>
#include <stdlib.h>
#include "paroc_interface.h"
#include "paroc_buffer.h"
#include "paroc_array.h"

#define METH_VECT_PACK(type) \
void paroc_buffer::Pack( std::vector<type> *vect, int n)\
{\
	int s=vect->size();\
	Pack(&s,1);\
	Pack((type*)&(*vect)[0],s);\
}

#define METH_VECT_UNPACK(type) \
void paroc_buffer::UnPack( std::vector<type> *vect, int n)\
{\
	int s=0;\
	UnPack(&s,1);\
	vect->resize(s);\
	UnPack((type*)&(*vect)[0],s);\
}


//Message header

paroc_message_header::paroc_message_header(int classid, int methodid, int semantics, const char *metname)
{
	type=TYPE_REQUEST;

	id[0]=classid;
	id[1]=methodid;
	id[2]=semantics;
	methodname=metname;
}

paroc_message_header::paroc_message_header(const char *metname)
{
	type=TYPE_RESPONSE;
	methodname=metname;
}

paroc_message_header::paroc_message_header(int exceptioncode, const char *metname)
{
	type=TYPE_EXCEPTION;
	methodname=metname;
	SetExceptionCode(exceptioncode);
}

paroc_message_header::paroc_message_header()
{
	type=-1;
	methodname=NULL;
}

void paroc_message_header::operator =(const  paroc_message_header &dat)
{
	if (&dat==this) return;
	type=dat.GetType();
	SetMethodName(dat.GetMethodName());
	switch (type)
	{
	case TYPE_REQUEST:
		id[0]=dat.GetClassID();
		id[1]=dat.GetMethodID();
		id[2]=dat.GetSemantics();
		break;
	case TYPE_EXCEPTION:
		exception=dat.GetExceptionCode();
		break;
	}
}

//Message envelop

paroc_buffer::paroc_buffer()
{
}

paroc_buffer::~paroc_buffer()
{
}

void paroc_buffer::SetHeader(const paroc_message_header &data)
{
	header=data;
}

const paroc_message_header & paroc_buffer::GetHeader() const
{
	return header;
}

void paroc_buffer::Push(const char *paramname, const char *paramtype, int nelem)
{
}

void paroc_buffer::Pop()
{
}

void paroc_buffer::Pack(const paroc_string *list, int n)
{
	if (n<=0 || list==NULL) return;
	for (int i=0;i<n;i++,list++)
	{
		const char *res=(*list);
		int len=list->Length()+1;
		Pack(&len,1);
		if (len>0) Pack(res,len);
	}
}

void paroc_buffer::UnPack(paroc_string *list, int n)
{
	if (n<=0 || list==NULL) return;
	paroc_array<char> tmpstr;
	int len;
	for (int i=0;i<n;i++,list++)
	{
		UnPack(&len,1);
		if (len>0)
		{
			tmpstr.SetSize(len);
			UnPack(tmpstr,len);
			(*list)=(char *)tmpstr;
		}
		else (*list)=NULL;
	}
}

void paroc_buffer::Pack(const std::string *list, int n)
{
	if (n<=0 || list==NULL) return;
	for (int i=0;i<n;i++,list++)
	{
		int len=list->length()+1;
		Pack(&len,1);
		if (len>0) Pack(list->c_str(),len);
	}
}

void paroc_buffer::UnPack(std::string *list, int n)
{
	if (n<=0 || list==NULL) return;
	paroc_array<char> tmpstr;
	int len;
	for (int i=0;i<n;i++,list++)
	{
		UnPack(&len,1);
		if (len>0)
		{
			tmpstr.SetSize(len);
			UnPack(tmpstr,len);
			(*list)=(char *)tmpstr;
		}
		else list->clear();
	}
}

METH_VECT_PACK(float)
METH_VECT_UNPACK(float)
METH_VECT_PACK(double)
METH_VECT_UNPACK(double)

//METH_VECT_PACK(bool)
//METH_VECT_UNPACK(bool)
METH_VECT_PACK(char)
METH_VECT_UNPACK(char)
METH_VECT_PACK(unsigned char)
METH_VECT_UNPACK(unsigned char)
METH_VECT_PACK(short)
METH_VECT_UNPACK(short)
METH_VECT_PACK(unsigned short)
METH_VECT_UNPACK(unsigned short)
METH_VECT_PACK(int)
METH_VECT_UNPACK(int)
METH_VECT_PACK(long)
METH_VECT_UNPACK(long)
METH_VECT_PACK(std::string)
METH_VECT_UNPACK(std::string)

bool paroc_buffer::Send(paroc_connection *conn)
{
	if (conn==NULL) return false;
	paroc_combox *combox=conn->GetCombox();
	return Send(*combox, conn);
}

bool paroc_buffer::Recv(paroc_connection *conn)
{
	if (conn==NULL) return false;
	paroc_combox *combox=conn->GetCombox();
	return Recv(*combox, conn);
}


#define SEND_EXCEPTION(x)  paroc_message_header tmp(x, except.GetHeader().GetMethodName()); \
 except.Reset();\
except.SetHeader(tmp);\
  except.Pack(&code,1);\
  return except.Send(s);



bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,int code)
{
	SEND_EXCEPTION(EXCEPTION_INT);
}


bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,unsigned code)
{
	SEND_EXCEPTION(EXCEPTION_UINT);
}


bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,long code)
{
	SEND_EXCEPTION(EXCEPTION_LONG);
}

bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,unsigned long code)
{

	SEND_EXCEPTION(EXCEPTION_ULONG);
}

bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,short code)
{
	SEND_EXCEPTION(EXCEPTION_SHORT);
}
bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,unsigned short code)
{
	SEND_EXCEPTION(EXCEPTION_USHORT);
}


bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,bool code)
{
	SEND_EXCEPTION(EXCEPTION_BOOL);
}


bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,char code)
{
	SEND_EXCEPTION(EXCEPTION_CHAR);
}

bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,unsigned char code)
{
	SEND_EXCEPTION(EXCEPTION_UCHAR);
}



bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,char *code)
{
	except.Reset();
	paroc_message_header tmp(EXCEPTION_STRING,except.GetHeader().GetMethodName());
	except.SetHeader(tmp);
	int len=(code==NULL)? 0 : strlen(code)+1;
	except.Pack(&len,1);
	except.Pack(code,len);

	return except.Send(s);
}
bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,float code)
{
	SEND_EXCEPTION(EXCEPTION_FLOAT);
}


bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s,double code)
{
	SEND_EXCEPTION(EXCEPTION_DOUBLE);
}

bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s, paroc_exception &code)
{
	//  SEND_EXCEPTION(EXCEPTION_POPC_STD);
	paroc_message_header tmp(EXCEPTION_POPC_STD, except.GetHeader().GetMethodName());
	except.Reset();
	except.SetHeader(tmp);
	code.Serialize(except,true);
	return except.Send(s);
}

bool paroc_buffer::SendException(paroc_buffer &except, paroc_connection *s, paroc_interface &code)
{
	paroc_message_header tmp(EXCEPTION_OBJECT, except.GetHeader().GetMethodName());
	except.Reset();
	except.SetHeader(tmp);
	code.Serialize(except,true);
	return except.Send(s);
}

void  paroc_buffer::CheckAndThrow(paroc_buffer &except)
{
	const paroc_message_header &h=except.GetHeader();

	if (h.GetType()!=TYPE_EXCEPTION) return;
	int code=h.GetExceptionCode();
	switch (code)
	{
	case EXCEPTION_INT:
	{
		int t;
		except.UnPack(&t,1);
		throw t;
	}
	case EXCEPTION_UINT:
	{
		unsigned t;
		except.UnPack(&t,1);
		throw t;
	}
	case EXCEPTION_LONG:
	{
		long t;
		except.UnPack(&t,1);
		throw t;
	}
	case EXCEPTION_ULONG:
	{
		unsigned long t;
		except.UnPack(&t,1);
		throw t;
	}

	case EXCEPTION_SHORT:
	{
		short t;
		except.UnPack(&t,1);
		throw t;
	}

	case EXCEPTION_USHORT:
	{
		unsigned short t;
		except.UnPack(&t,1);
		throw t;
	}
	case EXCEPTION_BOOL:
	{
		bool t;
		except.UnPack(&t,1);
		throw t;
	}
	case EXCEPTION_CHAR:
	{
		char t;
		except.UnPack(&t,1);
		throw t;
	}
	case EXCEPTION_UCHAR:
	{
		unsigned char t;
		except.UnPack(&t,1);
		throw t;
	}

	case EXCEPTION_STRING:
	{
		char *t;
		int len;
		except.UnPack(&len,1);
		if (len<=0) throw (char *)NULL;
		t=(char *)malloc(len*sizeof(char));
		except.UnPack(t,len);
		throw t;
	}

	case EXCEPTION_FLOAT:
	{
		float t;
		except.UnPack(&t,1);
		throw t;
	}

	case EXCEPTION_DOUBLE:
	{
		double t;
		except.UnPack(&t,1);
		throw t;
	}
	case EXCEPTION_POPC_STD:
	{
		paroc_exception *t=paroc_exception::create(0);
		t->Serialize(except,false);
		throw t;
	}
	case EXCEPTION_OBJECT:
	{
		paroc_interface t;
		t.Serialize(except,false);
		//        except.UnPack(&t,1);
		throw t;
	}
	default:
		paroc_exception::paroc_throw(POPC_BUFFER_FORMAT);
	}
}


void paroc_buffer::Destroy()
{
	delete this;
}



