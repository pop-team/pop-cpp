/**
 * @file buffer_xdr_factory.cc
 * @author Valentin Clement
 * Description : Implementation of SUN-XDR message buffer
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */


#include <string.h>
#include <arpa/inet.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include "paroc_interface.h"
#include "popc_buffer_xdr_mpi.h"
#include "paroc_exception.h"


popc_buffer_xdr_mpi::popc_buffer_xdr_mpi(): packeddata(0,1024)
{
	Reset();
}

popc_buffer_xdr_mpi::~popc_buffer_xdr_mpi()
{
}

void popc_buffer_xdr_mpi::Reset()
{
	unpackpos=20;
	packeddata.RemoveAll();
	packeddata.SetSize(unpackpos);
}

void popc_buffer_xdr_mpi::Pack(const int *data, int n)
{
	if (n<=0) return;
	int oldsize=packeddata.GetSize();
	packeddata.SetSize(n*4+oldsize);
	char *dest=packeddata+oldsize;

	XDR xdr;
	xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(int),(xdrproc_t)xdr_int);
	xdr_destroy(&xdr);

}
void popc_buffer_xdr_mpi::UnPack(int *data, int n)
{
	if (n<=0) return;
	char *dest=packeddata+unpackpos;

	int sz=4*n;

	CheckUnPack(sz);

	XDR xdr;
	xdrmem_create(&xdr,dest,sz,XDR_DECODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(int),(xdrproc_t)xdr_int);
	xdr_destroy(&xdr);

	unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const unsigned *data, int n)
{
	if (n<=0) return;
	int oldsize=packeddata.GetSize();
	packeddata.SetSize(n*4+oldsize);
	char *dest=packeddata+oldsize;

	XDR xdr;
	xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(int),(xdrproc_t)xdr_u_int);
	xdr_destroy(&xdr);

}
void popc_buffer_xdr_mpi::UnPack(unsigned *data, int n)
{
	if (n<=0) return;

	int sz=4*n;
	CheckUnPack(sz);

	char *dest=packeddata+unpackpos;
	XDR xdr;
	xdrmem_create(&xdr,dest,sz,XDR_DECODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(unsigned),(xdrproc_t)xdr_u_int);
	xdr_destroy(&xdr);

	unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const long *data, int n)
{
	if (n<=0) return;
	int oldsize=packeddata.GetSize();
	packeddata.SetSize(n*4+oldsize);
	char *dest=packeddata+oldsize;

	XDR xdr;
	xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(long),(xdrproc_t)xdr_long);
	xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(long *data, int n)
{
	if (n<=0) return;
	char *dest=packeddata+unpackpos;

	int sz=4*n;
	CheckUnPack(sz);

	XDR xdr;
	xdrmem_create(&xdr,dest,sz,XDR_DECODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(long),(xdrproc_t)xdr_long);
	xdr_destroy(&xdr);

	unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const unsigned long *data, int n)
{
	if (n<=0) return;
	int oldsize=packeddata.GetSize();
	packeddata.SetSize(n*4+oldsize);
	char *dest=packeddata+oldsize;

	XDR xdr;
	xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(long),(xdrproc_t)xdr_u_long);
	xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(unsigned long *data, int n)
{
	if (n<=0) return;
	char *dest=packeddata+unpackpos;

	int sz=n*4;
	CheckUnPack(sz);

	XDR xdr;
	xdrmem_create(&xdr,dest,sz,XDR_DECODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(long),(xdrproc_t)xdr_u_long);
	xdr_destroy(&xdr);

	unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const short *data, int n)
{
	if (n<=0) return;
	int oldsize=packeddata.GetSize();
	packeddata.SetSize( ((n-1)/2+1)*4+oldsize);
	char *dest=packeddata+oldsize;

	XDR xdr;
	xdrmem_create(&xdr,dest,n*2,XDR_ENCODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(short),(xdrproc_t)xdr_short);
	xdr_destroy(&xdr);

}

void popc_buffer_xdr_mpi::UnPack(short *data, int n)
{
	if (n<=0) return;
	char *dest=packeddata+unpackpos;

	int sz=2*n;
	CheckUnPack(sz);
	XDR xdr;
	xdrmem_create(&xdr,dest,sz,XDR_DECODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(short),(xdrproc_t)xdr_short);
	xdr_destroy(&xdr);

	unpackpos+=((n-1)/2+1)*4;

}

void popc_buffer_xdr_mpi::Pack(const unsigned short *data, int n)
{
	if (n<=0) return;
	int oldsize=packeddata.GetSize();
	packeddata.SetSize( ((n-1)/2+1)*4+oldsize);
	char *dest=packeddata+oldsize;

	XDR xdr;
	xdrmem_create(&xdr,dest,n*2,XDR_ENCODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(short),(xdrproc_t)xdr_u_short);
	xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(unsigned short *data, int n)
{
	if (n<=0) return;
	char *dest=packeddata+unpackpos;

	int sz=2*n;
	CheckUnPack(sz);

	XDR xdr;
	xdrmem_create(&xdr,dest,sz,XDR_DECODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(short),(xdrproc_t)xdr_u_short);
	xdr_destroy(&xdr);

	unpackpos+=((n-1)/2+1)*4;
}

void popc_buffer_xdr_mpi::Pack(const bool *data, int n)
{
	if (n<=0) return;
	int t=packeddata.GetSize();
	packeddata.SetSize(t+((n-1)/4+1)*4);
	char *dat=((char *)packeddata)+t;
	while (n-->0)
	{
		*dat=(*data==true);
		dat++; data++;
	}
}
void popc_buffer_xdr_mpi::UnPack(bool *data, int n)
{
	if (n <= 0) {
	  return;
	}
	CheckUnPack(n);
  packeddata.GetSize();

	char *dat = ((char *)packeddata) + unpackpos;
	while (n-->0) {
		*data = (*dat != 0);
		dat++; 
		data++;
	}
	unpackpos += ((n-1)/4+1) * 4;
}

void popc_buffer_xdr_mpi::Pack(const char *data, int n)
{
	if (n<=0) return;
	int t=packeddata.GetSize();
	packeddata.SetSize(t+((n-1)/4+1)*4);
	memcpy(( (char *)packeddata)+t,data,n);
}

void popc_buffer_xdr_mpi::UnPack(char *data, int n)
{
	if (n<=0) return;
	CheckUnPack(n);
  packeddata.GetSize();
	memcpy(data, ((char *)packeddata)+unpackpos,n);
	unpackpos+=((n-1)/4+1)*4;
}

void popc_buffer_xdr_mpi::Pack(const unsigned char *data, int n)
{
	Pack((char *)data,n);
}

void popc_buffer_xdr_mpi::UnPack(unsigned char *data, int n)
{
	UnPack((char *)data,n);
}

void popc_buffer_xdr_mpi::Pack(const float *data, int n)
{
	if (n<=0) return;
	int oldsize=packeddata.GetSize();
	packeddata.SetSize(n*4+oldsize);
	char *dest=packeddata+oldsize;

	XDR xdr;
	xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(float),(xdrproc_t)xdr_float);
	xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(float *data, int n)
{
	if (n<=0) return;
	char *dest=packeddata+unpackpos;

	int sz=n*4;
	CheckUnPack(sz);

	XDR xdr;
	xdrmem_create(&xdr,dest,sz,XDR_DECODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(float),(xdrproc_t)xdr_float);
	xdr_destroy(&xdr);

	unpackpos+=sz;

}

void popc_buffer_xdr_mpi::Pack(const double *data, int n)
{
	if (n<=0) return;
	int oldsize=packeddata.GetSize();
	packeddata.SetSize(n*8+oldsize);
	char *dest=packeddata+oldsize;

	XDR xdr;
	xdrmem_create(&xdr,dest,n*8,XDR_ENCODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(double),(xdrproc_t)xdr_double);
	xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(double *data, int n)
{
	if (n<=0) return;
	char *dest=packeddata+unpackpos;

	int sz=8*n;
	CheckUnPack(sz);

	XDR xdr;
	xdrmem_create(&xdr,dest,sz,XDR_DECODE);
	xdr_vector(&xdr,(char *)data,n,sizeof(double),(xdrproc_t)xdr_double);
	xdr_destroy(&xdr);

	unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const signed char *data, int n)
{
	Pack((char *)data,n);
}

void popc_buffer_xdr_mpi::UnPack(signed char *data, int n)
{
	UnPack((char *)data,n);
}

void popc_buffer_xdr_mpi::CheckUnPack(int sz)
{
	if (sz+unpackpos > packeddata.GetSize()) paroc_exception::paroc_throw(POPC_BUFFER_FORMAT);
}

bool popc_buffer_xdr_mpi::Send(paroc_combox &s, paroc_connection *conn)
{
  // Pack the header (20 bytes)
  char *dat=(char *)packeddata;

  if (dat == NULL) { 
    printf("fail 1\n");
    return false;
  }
  int n = packeddata.GetSize();
	int h[5];
	memset(h, 0, 5 * sizeof(int));

	int type = header.GetType();

	h[0] = htonl(n);
	h[1] = htonl(type);

	switch (type) {
  	case TYPE_REQUEST:
	  	h[2] = htonl(header.GetClassID());
		  h[3] = htonl(header.GetMethodID());
  		h[4] = htonl(header.GetSemantics());
	  	break;
  	case TYPE_EXCEPTION:
	  	h[2] = htonl(header.GetExceptionCode());
		  break;
  	case TYPE_RESPONSE:
	  	h[2] = htonl(header.GetClassID());
		  h[3] = htonl(header.GetMethodID());
  		break;
	  default:
		  return false;
	}
	memcpy(dat, h, 20);

	if (s.Send(dat, n, conn) < 0) {
		return false;
	}
	return true;
}

/**
 *
 */
bool popc_buffer_xdr_mpi::Recv(paroc_combox &s, paroc_connection *conn)
{
	int h[5];
	int n, i;


 /* MPI::Request req = communicator.Irecv(&length, 1, MPI_INT, 0, 0); 

  bool done = false; 
  while(!done) {
    done = req.Test(status); 
  }
  
  int data_length; 
  req = communicator.Irecv(&data_length, 1, MPI_INT, 0, 1); 

  done = false; 
  while(!done) {
    done = req.Test(status); 
  }    

//    char* load = new char[data_length];
  req = communicator.Irecv(packeddata, data_length, MPI_CHAR, 0, 2); 
    
  done = false; 
  while(!done) {
    done = req.Test(status); 
  }*/

	// Recv the header
	char *dat = (char *)h;
//	n = 20;
/*	do {
	  if(conn == NULL)
	    printf("XDR: recv connection is null\n");
		if ((i = s.Recv(dat, n, conn)) <= 0) {
			return false;
		}
		n -= i;
		dat += i;
	} while (n);
*/

	Reset();
	n = ntohl(h[0]);
	if (n < 20) {
	  printf("POP-C++ Error [CORE]: XDR Buffer - Bad message header (size error:%d)\n", n);
		return false;
	}

	int type = ntohl(h[1]);
	header.SetType(type);
	switch (type) {
  	case TYPE_REQUEST:
	  	header.SetClassID(ntohl(h[2]));
		  header.SetMethodID(ntohl(h[3]));
  		header.SetSemantics(ntohl(h[4]));
	  	break;
  	case TYPE_EXCEPTION:
	  	header.SetExceptionCode(ntohl(h[2]));
		  break;
  	case TYPE_RESPONSE:
	  	header.SetClassID(ntohl(h[2]));
		  header.SetMethodID(ntohl(h[3]));
  		break;
	  default:
		  return false;
	}

	packeddata.SetSize(n);
	dat = (char *)packeddata+20;
	n -= 20;

	i = 0;
	while (n) {
		if ((i = s.Recv(dat,n, conn)) <= 0) {
			return false;
		}
		dat += i;
		n -= i;
	}
	return true;
}

int popc_buffer_xdr_mpi::get_size()
{
  return packeddata.GetSize();
}

char* popc_buffer_xdr_mpi::get_load()
{
	char *dat = (char*)packeddata;

	if (dat == NULL) { 
	  return NULL;
	}
	int n = packeddata.GetSize();
	int h[5];
	memset(h,0, 5*sizeof(int));

	int type=header.GetType();

	h[0]=htonl(n);
	h[1]=htonl(type);

	switch (type) {
  	case TYPE_REQUEST:
	  	h[2]=htonl(header.GetClassID());
		  h[3]=htonl(header.GetMethodID());
  		h[4]=htonl(header.GetSemantics());
	  	break;
  	case TYPE_EXCEPTION:
	  	h[2]=htonl(header.GetExceptionCode());
		  break;
  	case TYPE_RESPONSE:
	  	h[2]=htonl(header.GetClassID());
		  h[3]=htonl(header.GetMethodID());
  		break;
	  default:
  	  printf("fail 2\n");	  
		  return NULL;
	}
	memcpy(dat, h, 20);



  return (char *)packeddata;
}

void popc_buffer_xdr_mpi::load(char* data, int length)
{ 
	int h[5];	
	Reset();
	memcpy(packeddata, data, length); 
	memcpy(h, packeddata, 20); 
	int n = ntohl(h[0]);
	if (n < 20) {
	  printf("POP-C++ Error [CORE]: XDR Buffer - Bad message header (size error:%d)\n", n);
		return;
	}	
	
  int type = ntohl(h[1]);
	header.SetType(type);
	switch (type) {
  	case TYPE_REQUEST:
	  	header.SetClassID(ntohl(h[2]));
		  header.SetMethodID(ntohl(h[3]));
  		header.SetSemantics(ntohl(h[4]));
	  	break;
  	case TYPE_EXCEPTION:
	  	header.SetExceptionCode(ntohl(h[2]));
		  break;
  	case TYPE_RESPONSE:
	  	header.SetClassID(ntohl(h[2]));
		  header.SetMethodID(ntohl(h[3]));
  		break;
	  default:
		  return;
	}	
	
	packeddata.SetSize(length);	
}


#ifdef OD_DISCONNECT
bool popc_buffer_xdr_mpi::RecvCtrl(paroc_combox &s, paroc_connection *conn) {
	while (true) {
		paroc_connection * t = (paroc_connection *) s.Wait();
		if (t == NULL) {
			paroc_exception::paroc_throw(9998,
										 "[paroc_buffer_xdr.cc] : Remote Object not alive\n");
		}
		if (!Recv(s, t))
			paroc_exception::paroc_throw(errno);
		if (header.GetType() == TYPE_RESPONSE) {
			if (header.GetClassID() == 0 && header.GetMethodID() == 6) {
				return true;
			} else {
				paroc_message_header h = header;
				int unpackposold = unpackpos;
				paroc_array<char> packeddataold = packeddata;
				paroc_connection * t = (paroc_connection *) s.Wait();
				if (t == NULL) {
					paroc_exception::paroc_throw(9998,
												 "[paroc_buffer_xdr.cc] : Remote Object not alive\n");
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
