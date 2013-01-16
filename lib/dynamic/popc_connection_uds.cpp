#include <signal.h>

#include "popc_connection_uds.h"


/**
 * Constructor
 * @param cb    Combox which has created this connection
 * @param init  If true, the connection will be marke as init connection
 */
popc_connection_uds::popc_connection_uds(paroc_combox *cb): paroc_connection(cb)
{
	_socket_fd = -1;
	signal(SIGPIPE, SIG_IGN);
}


/**
 * Constructor
 * @param fd    The file descriptor to be associated with this connection
 * @param cb    Combox which has created this connection
 */
popc_connection_uds::popc_connection_uds(int fd, paroc_combox *cb): paroc_connection(cb), _socket_fd(fd)
{
}

/**
 * Constructor
 * @param fd    The file descriptor to be associated with this connection
 * @param cb    Combox which has created this connection
 * @param init  If true, the connection will be marke as init connection
 */
popc_connection_uds::popc_connection_uds(int fd, paroc_combox *cb, bool init): paroc_connection(cb, init), _socket_fd(fd)
{
}

/**
 * Copy constructor
 * @param me  The connection to be copied
 */
popc_connection_uds::popc_connection_uds(popc_connection_uds &me): paroc_connection(me.GetCombox(), me.GetBufferFactory())
{
  _socket_fd = me.get_fd();
}

/**
 * Clone a connection
 */
paroc_connection *popc_connection_uds::Clone()
{
	return new popc_connection_uds(this->get_fd(), this->GetCombox());
}

/**
 * Set the file descriptor associated with this connection
 * @param fd  A file descriptor to be associated with this connection
 */
void popc_connection_uds::set_fd(int fd)
{
  _socket_fd = fd;
}

/**
 * Get the file descriptor associated with this connection
 * @return A file descriptor
 */
int popc_connection_uds::get_fd()
{
  return _socket_fd;
}