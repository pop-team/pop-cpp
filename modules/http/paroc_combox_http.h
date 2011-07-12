#ifndef PAROC_COMBOX_HTTP_H
#define PAROC_COMBOX_HTTP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include "paroc_combox_socket.h"
#include "paroc_array.h"
#include "paroc_list.h"

//#define MAX_CHUNK_SIZE 10
#define NOT_CONNECTED 0
#define CONNECTED_SERVER 1
#define CONNECTED_CLIENT 2

#define HTTP_BUFFER_SIZE 10240

class http_conn_cookie
{
 public:
  http_conn_cookie();
  http_conn_cookie & operator =(http_conn_cookie &x);

  paroc_string cookie;
  paroc_buffer_factory *fact;
  int ref;
};

class paroc_connection_http: public  paroc_connection_sock
{
 public:
  paroc_connection_http(paroc_combox *cb);
  paroc_connection_http(int fd, paroc_combox *cb); 
  paroc_connection_http(paroc_connection_http &me); 
  virtual ~paroc_connection_http();

  virtual paroc_connection *Clone();

  http_conn_cookie *GetRef();
  void SetRef(http_conn_cookie *x);

  virtual void SetBufferFactory(paroc_buffer_factory *fact);
  virtual paroc_buffer_factory *GetBufferFactory();

  int messageLen;
  paroc_string myfile, myhost, mycookie;
  bool isChunkRecv;
  bool isChunkSend;
  
  bool sendHeader;
  bool recvHeader;
  bool closeConnection;
  bool reconnect;

 protected:
  http_conn_cookie *connref;
};


class paroc_combox_http:public paroc_combox_socket
{
public:
	paroc_combox_http();
	virtual ~paroc_combox_http();

	virtual bool Connect(const char *url);
	
	virtual int Send(const char *s,int len);
	virtual int Send(const char *s,int len, paroc_connection *conn);

	virtual int Recv(char *s,int len);
	virtual int Recv(char *s,int len, paroc_connection *&iopeer);

	virtual bool SendAck(paroc_connection *conn);
	virtual bool RecvAck(paroc_connection *conn);

	virtual paroc_connection *Wait();
	virtual void Close();

	virtual bool GetUrl(paroc_string & accesspoint);
	virtual bool GetProtocol(paroc_string & protocolName);
		
protected:

	virtual paroc_connection_sock *CreateConnection(int fd);
	bool RecvHeader(paroc_connection_http *thisconn);
	bool ReadChunkSize(paroc_connection_http * conn);
	bool SendHeader(paroc_connection_http * conn, int msgsize);
	bool ReadLine(paroc_connection *conn, char *aline, int sz);
	bool FinalizeSend(paroc_connection_http *conn);
	bool ReConnect();

	http_conn_cookie *CreateCookie();
	http_conn_cookie *FindCookie(const paroc_string &cookie);
	bool RemoveCookie(const paroc_string &cookie);
	
	int cookie_count;
	int rcount,scount;

	paroc_string myurl;
	
	paroc_list<http_conn_cookie> cookie_list;

 protected:
  virtual bool OnNewConnection(paroc_connection *conn);
  virtual bool OnCloseConnection(paroc_connection *conn);
};


#endif







