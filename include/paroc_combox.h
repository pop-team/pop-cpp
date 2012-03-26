/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: POP-C++ communication abstraction
 */

#ifndef POPC_COMBOX_H
#define POPC_COMBOX_H

#include "paroc_string.h"
#include "paroc_buffer_factory_finder.h"

class paroc_combox;

/**
 * @class paroc_connection
 * @brief POP-C++ communication abstraction, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_connection
{
public:
	paroc_connection(paroc_combox *com);
	paroc_connection(paroc_combox *com, paroc_buffer_factory *f);
	virtual ~paroc_connection();

	virtual void SetBufferFactory(paroc_buffer_factory *fact);
	virtual paroc_buffer_factory *GetBufferFactory();

	paroc_combox *GetCombox();

	virtual paroc_connection *Clone()=0;

protected:
	paroc_buffer_factory * fact;
	paroc_combox *combox;
};


enum COMBOX_EVENTS {COMBOX_NEW=0, COMBOX_CLOSE=1};
typedef bool (*COMBOX_CALLBACK)(void *, paroc_connection *);


/**
 * @class paroc_combox
 * @brief POP-C++ combox, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_combox
{
public:
	paroc_combox();
protected:
	virtual ~paroc_combox();

public:
	virtual bool Create(int port, bool server)=0;
	virtual bool Connect(const char *url)=0;

	virtual int Send(const char *s,int len)=0;
	virtual int Send(const char *s,int len, paroc_connection *conn)=0;
	virtual bool SendAck(paroc_connection *conn);

	virtual int Recv(char *s,int len)=0;
	virtual int Recv(char *s,int len, paroc_connection *&peer)=0;
	virtual bool RecvAck(paroc_connection *conn=0);

	virtual paroc_connection *Wait()=0;

	virtual void Close()=0;

	void SetTimeout(int millisec);
	int  GetTimeout();

	virtual bool GetUrl(paroc_string & accesspoint)=0;
	virtual bool GetProtocol(paroc_string & protocolName)=0;

	virtual void Destroy();

	bool SetCallback(COMBOX_EVENTS ev, COMBOX_CALLBACK cb, void *arg);

	void SetBufferFactory(paroc_buffer_factory *fact);
	paroc_buffer_factory *GetBufferFactory();

protected:
	virtual bool OnNewConnection(paroc_connection *conn);
	virtual bool OnCloseConnection(paroc_connection *conn);

protected:
	int timeout;
	COMBOX_CALLBACK cblist[2];
	void *cbdata[2];

	paroc_buffer_factory *defaultFact;

};



#endif







