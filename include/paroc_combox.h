/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: POP-C++ communication abstraction
 */

#ifndef INCLUDE_POPC_COMBOX_H_
#define INCLUDE_POPC_COMBOX_H_

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
  static const int POPC_CONNECTION_NULL_FD;
  
	paroc_connection(paroc_combox *com);
	paroc_connection(paroc_combox *com, paroc_buffer_factory *f);
	virtual ~paroc_connection();

	virtual void SetBufferFactory(paroc_buffer_factory *fact);
	virtual paroc_buffer_factory *GetBufferFactory();
	virtual void reset();

	paroc_combox *GetCombox();

	virtual paroc_connection *Clone()=0;

	bool is_connection_init();
	void set_as_connection_init();
	bool is_wait_unlock();
	void set_as_wait_unlock();

protected:
	paroc_buffer_factory *fact;
	paroc_combox *combox;
	
	
private: 
  bool _is_connection_init;	
  bool _is_wait_unlock;
};


enum COMBOX_EVENTS { COMBOX_NEW = 0, COMBOX_CLOSE = 1 };
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
  enum COMBOX_TYPE { POLLING, REQUESTBYREQUEST }; 

	virtual bool Create(char* host, int port, bool server)=0;
	virtual bool Connect(const char *url)=0;
	virtual bool connect_and_die(std::string &url)=0;
	virtual bool unlock_wait(bool rewait)=0;	
	virtual paroc_connection* get_connection()=0; // Will be modified later
	virtual paroc_connection* reconnect()=0;
	virtual bool disconnect(paroc_connection *connection) = 0;

	virtual int Send(const char *s,int len)=0;
	virtual void send_data_length(int length, paroc_connection *conn) = 0;
	virtual int Send(const char *s,int len, paroc_connection *conn, bool unlock)=0;
	virtual int init_send(paroc_connection *conn, bool unlock)=0;
	virtual bool SendAck(paroc_connection *conn);


  virtual int receive_data_length(paroc_connection *peer)=0;
	virtual int Recv(char *s,int len, bool unlock)=0;
	virtual int Recv(char *s,int len, paroc_connection *&peer, bool unlock)=0;
	virtual bool RecvAck(paroc_connection *conn=0);

	virtual paroc_connection *Wait()=0;
	
	virtual bool is_server()=0;

	virtual void Close()=0;

	void SetTimeout(int millisec);
	int  GetTimeout();

	virtual bool GetUrl(paroc_string & accesspoint) = 0;
	virtual bool GetProtocol(paroc_string & protocolName) = 0;
	virtual paroc_connection* CreateConnection(int fd) = 0;

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

#endif // INCLUDE_POPC_COMBOX_H_