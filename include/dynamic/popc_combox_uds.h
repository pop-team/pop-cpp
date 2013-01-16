/**
 * @author Valentin Clement
 * @Brief Unix Domain Socket combox declaration
 */

#ifndef POPC_COMBOX_UNIX_DOMAIN_SOCKET_H
#define POPC_COMBOX_UNIX_DOMAIN_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <poll.h>
#include <ctype.h>

#include <paroc_array.h>

#include "paroc_combox.h"
#include "popc_connection_uds.h"

/**
 * @class paroc_combox_socket
 * @brief Socket declaration of combox, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class popc_combox_uds: public paroc_combox
{
public:
	popc_combox_uds();
	virtual ~popc_combox_uds();

	virtual bool Create(int port=0, bool server=false);
	virtual bool Create(const char *address, bool server=false);	

	virtual bool Connect(const char *url);

	virtual int Send(const char *s,int len);
	virtual int Send(const char *s,int len, paroc_connection *connection);

	virtual int Recv(char *s,int len);
	virtual int Recv(char *s,int len, paroc_connection *connection);

	virtual paroc_connection *Wait();

	virtual paroc_connection* get_connection();

	virtual void Close();

	virtual bool GetUrl(paroc_string & accesspoint);
	virtual bool GetProtocol(paroc_string & protocolName);

  void set_timeout(int value);
  
  void add_fd_to_poll(int fd);

  static const char* UDS_PROTOCOL_NAME;

private:
	int _socket_fd;
  struct sockaddr_un _sock_address;
	bool _is_server;
	std::string _uds_address;
	struct pollfd active_connection[200];
	int _active_connection_nb;
	int _timeout;
	bool _connected;
	bool _is_first_connection;
	popc_connection_uds* _connection;
	
};



#endif // POPC_COMBOX_UNIX_DOMAIN_SOCKET_H







