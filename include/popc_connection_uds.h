/**
 * @author Valentin Clement
 * @Brief Unix Domain Socket combox declaration
 */
 
#ifndef POPC_CONNECTION_UNIX_DOMAIN_SOCKET_H
#define POPC_CONNECTION_UNIX_DOMAIN_SOCKET_H

#include "paroc_combox.h"

/**
 */
class popc_connection_uds: public  paroc_connection
{
public:
	popc_connection_uds(paroc_combox *cb);
	popc_connection_uds(int fd, paroc_combox *cb);
	popc_connection_uds(int fd, paroc_combox *cb, bool init);
	popc_connection_uds(popc_connection_uds &me);

	virtual paroc_connection *Clone();
  virtual void reset() {};	
  
  void set_fd(int fd);
  int get_fd();

private:
	int _socket_fd;
};

#endif /* POPC_CONNECTION_UNIX_DOMAIN_SOCKET_H */