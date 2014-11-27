/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of a XDR buffer aware of MPI receive and send process. 
 *
 *
 */

#ifndef _POPC_BUFFER_XDR_MPI_H
#define _POPC_BUFFER_XDR_MPI_H

#include "paroc_array.h"
#include "paroc_buffer.h"

/**
 * @class paroc_buffer_xdr
 * @brief Buffer in XDR format used for heterogeneous platform communication, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class popc_buffer_xdr_mpi : public paroc_buffer
{
public:
	popc_buffer_xdr_mpi();
	~popc_buffer_xdr_mpi();
	virtual void Reset();

  using paroc_buffer::Pack;
  using paroc_buffer::UnPack;  
	virtual void Pack(const int *data, int n);
	virtual void UnPack(int *data, int n);

	virtual void Pack(const unsigned *data, int n);
	virtual void UnPack(unsigned *data, int n);

	virtual void Pack(const long *data, int n);
	virtual void UnPack(long *data, int n);

	virtual void Pack(const unsigned long *data, int n);
	virtual void UnPack(unsigned long *data, int n);

	virtual void Pack(const short *data, int n);
	virtual void UnPack(short *data, int n);

	virtual void Pack(const unsigned short *data, int n);
	virtual void UnPack(unsigned short *data, int n);

	virtual void Pack(const bool *data, int n);
	virtual void UnPack(bool *data, int n);

	virtual void Pack(const char *data, int n);
	virtual void UnPack(char *data, int n);

	virtual void Pack(const unsigned char *data, int n);
	virtual void UnPack(unsigned char *data, int n);

	virtual void Pack(const float *data, int n);
	virtual void UnPack(float *data, int n);

	virtual void Pack(const double *data, int n);
	virtual void UnPack(double *data, int n);

	virtual void Pack(const signed char *data, int n);
	virtual void UnPack(signed char *data, int n);

	using paroc_buffer::Send;
	virtual bool Send(paroc_combox &s, paroc_connection *conn);
	using paroc_buffer::Recv;	
	virtual bool Recv(paroc_combox &s, paroc_connection *conn);
	
	virtual int get_size();
	virtual char* get_load();
	virtual void load(char* data, int length);	
	
	

#ifdef OD_DISCONNECT	
	virtual bool RecvCtrl(paroc_combox &s, paroc_connection *conn=0);
#endif

protected:
	void CheckUnPack(int sz);

	int unpackpos;
	paroc_array<char> packeddata;
};

#endif /* _POPC_BUFFER_XDR_MPI_H */
