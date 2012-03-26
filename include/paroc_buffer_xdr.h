/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: buffer in XDR format used for heterogeneous platform communication
 */

#ifndef _POPC_BUFFER_XDR_H
#define _POPC_BUFFER_XDR_H

#include "paroc_array.h"
#include "paroc_buffer.h"

/**
 * @class paroc_buffer_xdr
 * @brief Buffer in XDR format used for heterogeneous platform communication, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_buffer_xdr: public paroc_buffer
{
public:
	paroc_buffer_xdr();
	~paroc_buffer_xdr();
	virtual void Reset();

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

	//added by lwk
	virtual void Pack(const signed char *data, int n);
	virtual void UnPack(signed char *data, int n);

	/*virtual void Pack(const long long *data, int n);
	virtual void UnPack(long long *data, int n);

	virtual void Pack(const long double *data, int n);
	virtual void UnPack(long double *data, int n);*/

	virtual bool Send(paroc_combox &s, paroc_connection *conn);
	virtual bool Recv(paroc_combox &s, paroc_connection *conn);

#ifdef OD_DISCONNECT	
	virtual bool RecvCtrl(paroc_combox &s, paroc_connection *conn=0);
#endif

protected:
	void CheckUnPack(int sz);

	int unpackpos;
	paroc_array<char> packeddata;
};

#endif
