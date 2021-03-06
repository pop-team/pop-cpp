/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/28
 * @Brief Unix Domain Socket combox declaration
 *
 *
 */

#ifndef POP_CONNECTION_UNIX_DOMAIN_SOCKET_H
#define POP_CONNECTION_UNIX_DOMAIN_SOCKET_H

#include "pop_combox.h"

/**
 * Connection holding a file descriptor referencing a UDS communication
 */
class popc_connection_uds : public pop_connection {
public:
    popc_connection_uds(pop_combox* cb);
    popc_connection_uds(int fd, pop_combox* cb);
    popc_connection_uds(int fd, pop_combox* cb, bool init);
    popc_connection_uds(popc_connection_uds& me);

    virtual pop_connection* Clone();
    virtual void reset() {
    }

    void set_fd(int fd);
    int get_fd();

private:
    int _socket_fd;
};

#endif /* POPC_CONNECTION_UNIX_DOMAIN_SOCKET_H */
