/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of raw message buffer
 */

#include <stdio.h>
#include <string.h>
#include "paroc_interface.h"
#include "paroc_buffer_raw.h"

paroc_buffer_raw::paroc_buffer_raw(): packeddata(0,1024)
{
	Reset();
}

paroc_buffer_raw::~paroc_buffer_raw()
{
}

void paroc_buffer_raw::Reset()
{
	unpackpos=20;
	//packeddata.RemoveAll();
	packeddata.SetSize(20);
}


void paroc_buffer_raw::Pack(const char *data, int n)
{
	if (n<=0) return;
	int t=packeddata.GetSize();
	packeddata.SetSize(t+((n-1)/4+1)*4);
	memcpy(( (char *)packeddata)+t,data,n);
}

void paroc_buffer_raw::UnPack(char *data, int n)
{
	if (n<=0) return;
	//CheckUnPack(n); // Error with this check in 64 bits
	int t=packeddata.GetSize();
	memcpy(data, ((char *)packeddata)+unpackpos,n);
	unpackpos+=((n-1)/4+1)*4;
}

void paroc_buffer_raw::Pack(const int *data, int n)
{
	Pack((const char *)data,n*sizeof(int));
}
void paroc_buffer_raw::UnPack(int *data, int n)
{
	UnPack((char *)data,n*sizeof(int));
}

void paroc_buffer_raw::Pack(const unsigned *data, int n)
{
	Pack((const char *)data,n*sizeof(unsigned));

}
void paroc_buffer_raw::UnPack(unsigned *data, int n)
{
	UnPack((char *)data,n*sizeof(unsigned));
}

void paroc_buffer_raw::Pack(const long *data, int n)
{
	Pack((const char *)data,n*sizeof(long));
}

void paroc_buffer_raw::UnPack(long *data, int n)
{
	UnPack((char *)data,n*sizeof(long));
}

void paroc_buffer_raw::Pack(const unsigned long *data, int n)
{
	Pack((const char *)data,n*sizeof(unsigned long));
}

void paroc_buffer_raw::UnPack(unsigned long *data, int n)
{
	UnPack((char *)data,n*sizeof(unsigned long));
}

void paroc_buffer_raw::Pack(const short *data, int n)
{
	Pack((const char *)data,n*sizeof(short));
}

void paroc_buffer_raw::UnPack(short *data, int n)
{
	UnPack((char *)data,n*sizeof(short));
}

void paroc_buffer_raw::Pack(const unsigned short *data, int n)
{
	Pack((const char *)data,n*sizeof(unsigned short));
}

void paroc_buffer_raw::UnPack(unsigned short *data, int n)
{
	UnPack((char *)data,n*sizeof(unsigned short));
}

void paroc_buffer_raw::Pack(const bool *data, int n)
{
	Pack((const char *)data,n*sizeof(bool));
}

void paroc_buffer_raw::UnPack(bool *data, int n)
{
	UnPack((char *)data,n*sizeof(bool));
}


void paroc_buffer_raw::Pack(const unsigned char *data, int n)
{
	Pack((char *)data,n);
}

void paroc_buffer_raw::UnPack(unsigned char *data, int n)
{
	UnPack((char *)data,n);
}

void paroc_buffer_raw::Pack(const float *data, int n)
{
	Pack((char *)data,n*sizeof(float));
}

void paroc_buffer_raw::UnPack(float *data, int n)
{
	UnPack((char *)data,n*sizeof(float));
}

void paroc_buffer_raw::Pack(const double *data, int n)
{
	Pack((char *)data,n*sizeof(double));
}

void paroc_buffer_raw::UnPack(double *data, int n)
{
	UnPack((char *)data,n*sizeof(double));
}

// added by lwk
void paroc_buffer_raw::Pack(const signed char *data, int n)
{
	Pack((char *)data,n);
}

void paroc_buffer_raw::UnPack(signed char *data, int n)
{
	UnPack((char *)data,n);
}

/*void paroc_buffer_raw::Pack(const long long *data, int n)
{
	Pack((char *)data,n*sizeof(long long));
}

void paroc_buffer_raw::UnPack(long long *data, int n)
{
	UnPack((char *)data,n*sizeof(long long));
}

void paroc_buffer_raw::Pack(const long double *data, int n)
{
	Pack((char *)data,n*sizeof(long double));
}

void paroc_buffer_raw::UnPack(long double *data, int n)
{
	UnPack((char *)data,n*sizeof(long double));
}*/


// void paroc_buffer_raw::Pack(const paroc_accesspoint *list, int n)
// {
//   if (n<=0 || list==NULL) return;
//   int len;
//   for (int i=0;i<n;i++,list++)
//     {
//       const char *res=list->GetAccessString();
//       int len=(res==NULL)? 0 : (strlen(res)+1);
//       Pack(&len,1);
//       if (len) Pack(res,len);
//     }
// }

// void paroc_buffer_raw::UnPack(paroc_accesspoint *list, int n)
// {
//   if (n<=0 || list==NULL) return;
//   paroc_array<char> tmpstr;
//   int len;
//   for (int i=0;i<n;i++,list++)
//     {
//       UnPack(&len,1);
//       if (len)
// 	{
// 	  tmpstr.SetSize(len);
// 	  UnPack(tmpstr,len);
// 	  list->SetAccessString(tmpstr);
// 	}
//       else list->SetAccessString(NULL);
//     }
// }

// void paroc_buffer_raw::Pack(const paroc_string *list, int n)
// {
//   if (n<=0 || list==NULL) return;
//   for (int i=0;i<n;i++,list++)
//     {
//       const char *res=(*list);
//       int len=list->Length()+1;
//       Pack(&len,1);
//       if (len>0) Pack(res,len);
//     }
// }

// void paroc_buffer_raw::UnPack(paroc_string *list, int n)
// {
//   if (n<=0 || list==NULL) return;
//   paroc_array<char> tmpstr;
//   int len;
//   for (int i=0;i<n;i++,list++)
//     {
//       UnPack(&len,1);
//       if (len>0)
// 	{
// 	  tmpstr.SetSize(len);
// 	  UnPack(tmpstr,len);
// 	  (*list)=(char *)tmpstr;
// 	}
//       else (*list)=NULL;
//     }
// }

// void paroc_buffer_raw::Pack(const paroc_od *list, int n)
// {
//   float val[7];
//   paroc_string t;
//   while (n>0)
//     {
//       list->getPower(val[0],val[1]);
//       list->getMemory(val[2],val[3]);
//       list->getBandwidth(val[4],val[5]);
//       val[6]=list->getWallTime();
//       Pack(val,7);

//       list->getURL(t);
//       Pack(&t,1);

//       list->getJobURL(t);
//       Pack(&t,1);

//       list->getExecutable(t);
//       Pack(&t,1);

//       list->getProtocol(t);
//       Pack(&t,1);

//       list->getEncoding(t);
//       Pack(&t,1);

//       n--;
//       list++;
//     }

// }

// void paroc_buffer_raw::UnPack(paroc_od *list, int n)
// {
//   float val[7];
//   paroc_string t;
//   while (n>0)
//     {
//       UnPack(val,7);
//       list->power(val[0],val[1]);
//       list->memory(val[2],val[3]);
//       list->bandwidth(val[4],val[5]);
//       list->walltime(val[6]);
//       UnPack(&t,1);
//       list->url(t);
//       UnPack(&t,1);
//       list->joburl(t);

//       UnPack(&t,1);
//       list->executable(t);

//       UnPack(&t,1);
//       list->protocol(t);

//       UnPack(&t,1);
//       list->encoding(t);
//       n--;
//       list++;
//     }
// }

// void paroc_buffer_raw::Pack(paroc_interface *inf, int n)
// {
//    if (n<=0) return;
//   int len;
//   for (int i=0;i<n;i++,inf++)
//     {
//       int ref=inf->AddRef();
//       Pack(&(inf->GetAccessPoint()),1);
//       Pack(&ref,1);
//       const paroc_od &myod=inf->GetOD();
//       Pack(&myod,1);
//     }
// }

// void paroc_buffer_raw::UnPack(paroc_interface *inf, int n)
// {
//   if (n<=0 || inf==NULL) return;
//   paroc_od myod;
//   paroc_accesspoint entry;
//   int len;
//   for (int i=0;i<n;i++,inf++)
//     {
//       int ref;
//       UnPack(&entry,1);
//       UnPack(&ref,1);
//       UnPack(&myod,1);

//       inf->SetOD(myod);

//       if (ref>0)
// 	{
// 	  inf->Bind(entry);
// 	  inf->DecRef();
// 	}
//     }
// }

// void paroc_buffer_raw::Pack(paroc_exception *e, int n)
// {
//    if (n<=0) return;
//   for (int i=0;i<n;i++,e++)
//     {
//       int t=e->Code();
//       Pack(&t,1);
//       char *extra=e->Extra();
//       t=strlen(extra)+1;
//       Pack(&t,1);
//       Pack(extra,t);
//     }
// }

// void paroc_buffer_raw::UnPack(paroc_exception *e, int n)
// {
//    if (n<=0) return;
//   for (int i=0;i<n;i++,e++)
//     {
//       int t;
//       UnPack(&t,1);
//       e->Code()=t;
//       char *extra=e->Extra();
//       UnPack(&t,1);
//       UnPack(extra,t);
//     }
// }


void paroc_buffer_raw::CheckUnPack(int sz)
{
	if (sz+unpackpos > packeddata.GetSize()) paroc_exception::paroc_throw(POPC_BUFFER_FORMAT);
}

bool paroc_buffer_raw::Send(paroc_combox &s, paroc_connection *conn)
{
//Pack the header (20 bytes)

	char *dat=(char *)packeddata;

	if (dat==NULL) return false;
	int n=packeddata.GetSize();
	int h[5];
	memset(h,0, 5*sizeof(int));

	int type=header.GetType();

	h[0]=n;
	h[1]=type;

	switch (type)
	{
	case TYPE_REQUEST:
		h[2]=header.GetClassID();
		h[3]=header.GetMethodID();
		h[4]=header.GetSemantics();
		break;
	case TYPE_EXCEPTION:
		h[2]=header.GetExceptionCode();
		break;
	case TYPE_RESPONSE:
		h[2]=header.GetClassID();
		h[3]=header.GetMethodID();
		break;
	default:
		return false;
	}
	memcpy(dat,h,20);
	if (s.Send(dat,n, conn)<0)
	{
		DEBUG("Fail to send a message!");
		return false;
	}
	return true;
}

//Propagation of exceptions back to caller...

bool paroc_buffer_raw::Recv(paroc_combox &s, paroc_connection *conn)
{
	int h[5];
	int n, i;

	//Recv the header...

	char *dat=(char *)h;
	n=20;
	do
	{
		if ((i=s.Recv(dat,n, conn)) <=0)
		{
			return false;
		}
		n-=i;
		dat+=i;
	}
	while (n);

	Reset();
	n=h[0];
	if (n<20)
	{
		DEBUG("Bad message header(size error:%d)",n);
		return false;
	}

	int type=h[1];
	header.SetType(type);
	switch (type)
	{
	case TYPE_REQUEST:
		header.SetClassID(h[2]);
		header.SetMethodID(h[3]);
		header.SetSemantics(h[4]);
		break;
	case TYPE_EXCEPTION:
		header.SetExceptionCode(h[2]);
		break;
	case TYPE_RESPONSE:
		header.SetClassID(h[2]);
		header.SetMethodID(h[3]);
		break;
	default:
		return false;
	}

	packeddata.SetSize(n);
	dat=(char *)packeddata+20;
	n-=20;

	i=0;
	while (n>0)
	{
		if ((i=s.Recv(dat,n, conn))<=0)
		{
			return false;
		}
		dat+=i;
		n-=i;
	}
	return true;
}

#ifdef OD_DISCONNECT
bool paroc_buffer_raw::RecvCtrl(paroc_combox &s, paroc_connection *conn)
{
	while (true)
	{
		paroc_connection * t = (paroc_connection *) s.Wait();
		if (t == NULL)
		{
			paroc_exception::paroc_throw(9999,
										 "[paroc_buffer_raw.cc] : Remote Object not alive\n");
		}
		if (!Recv(s, t))
			paroc_exception::paroc_throw(errno);
		if (header.GetType() == TYPE_RESPONSE)
		{
			if (header.GetClassID() == 0 && header.GetMethodID() == 6)
			{
				return true;
			} else {
				paroc_message_header h = header;
				int unpackposold = unpackpos;
				paroc_array<char> packeddataold = packeddata;
				paroc_connection * t = (paroc_connection *) s.Wait();
				if (t == NULL)
				{
					paroc_exception::paroc_throw(9999,
												 "[paroc_buffer_raw.cc] : Remote Object not alive\n");
				}
				if (!Recv(s, t))
					paroc_exception::paroc_throw(errno);
				Reset();
				header = h;
				unpackpos = unpackposold;
				packeddata = packeddataold;
				return false;
			}

		}
	}
}
#endif
