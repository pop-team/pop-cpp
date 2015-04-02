/**
*
* Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
* http://gridgroup.hefr.ch/popc
*
* @author Valentin Clement
* @date 2012/11/28
* @Brief Unix Domain Socket combox declaration
*
*/

#ifndef POPC_COMBOX_UNIX_DOMAIN_SOCKET_H
#define POPC_COMBOX_UNIX_DOMAIN_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <poll.h>
#include <ctype.h>

#include "pop_combox.h"
#include "popc_connection_uds.h"

class popc_combox_uds: public pop_combox {
public:
    popc_combox_uds();
    virtual ~popc_combox_uds();

    virtual bool Create(int port=0, bool server=false);
    virtual bool Create(const char *address, bool server=false);
    virtual bool need_address(){ return true; }

    virtual bool Connect(const char *url);
    virtual void Close();

    virtual pop_connection *Wait();
    virtual pop_connection* get_connection();

    virtual int Send(const char *s,int len);
    virtual int Send(const char *s,int len, pop_connection *connection);

    virtual int Recv(char *s,int len);
    virtual int Recv(char *s,int len, pop_connection *connection);

    virtual std::string GetUrl();
    virtual std::string GetProtocol();

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
