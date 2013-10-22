/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief socket declaration of combox
 *
 */

#ifndef POPC_COMBOX_SOCKET_H
#define POPC_COMBOX_SOCKET_H
#include "popc_intface.h"
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <poll.h>
//#include <ctype.h>

#include <paroc_array.h>

#include "paroc_combox.h"
/**
 * @class paroc_connection_sock
 * @brief Socket connection, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_connection_sock: public  paroc_connection
{
public:
	paroc_connection_sock(paroc_combox *cb);
	paroc_connection_sock(int fd, paroc_combox *cb);
	paroc_connection_sock(paroc_connection_sock &me);

	virtual paroc_connection *Clone();
  virtual void reset() {};	

	int sockfd;
};

/**
 * @class paroc_combox_socket
 * @brief Socket declaration of combox, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_combox_socket:public paroc_combox
{
public:
	paroc_combox_socket();

	virtual ~paroc_combox_socket();

	virtual bool Create(int port=0, bool server=false);
	virtual bool Create(const char *address, bool server=false) { return false; };	

	virtual bool Connect(const char *url);

	virtual int Send(const char *s,int len);
	virtual int Send(const char *s,int len, paroc_connection *connection);
	virtual paroc_connection* get_connection() { if(!peer){ return NULL;} return peer; };


	virtual int Recv(char *s,int len);
	virtual int Recv(char *s,int len, paroc_connection *connection);

	virtual paroc_connection *Wait();

	virtual void Close();

	/**
	 * @brief Returns URL of object
	 * @param accesspoint Returned URL (protocol://host:port)
	 * @return true if success
	 */
	virtual bool GetUrl(paroc_string & accesspoint);
	virtual bool GetProtocol(paroc_string & protocolName);

protected:
	virtual paroc_connection_sock *CreateConnection(int fd);
	bool CloseSock(int fd);
	bool Connect(const char *host,int port);

	int GetSockInfo(sockaddr &info,socklen_t &len);
	int GetPort();

	int GetOpt(int level, int opt, char *buf, socklen_t &len);
	int SetOpt(int level, int opt, char *buf, socklen_t len);

protected:
	int sockfd;
	bool isServer;
	bool isCanceled;
#ifdef __WIN32__
   	int highsockfd;
    fd_set readfds, activefdset;
#else
	paroc_array<pollfd> pollarray;
#endif	    
	paroc_connection_sock *peer;

	//Only used by combox server...
	paroc_array<paroc_connection_sock *> connarray;
	int index;
	int nready;
};



#endif







