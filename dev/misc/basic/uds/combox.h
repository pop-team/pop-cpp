/**
 * @author Valentin Clement
 * @Brief Unix Domain Socket combox declaration
 */

#ifndef POP_COMBOX_UNIX_DOMAIN_SOCKET_H
#define POP_COMBOX_UNIX_DOMAIN_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <poll.h>
#include <ctype.h>
#include <string>

class popc_connection_uds {
public:
//  popc_connection_uds();
    popc_connection_uds(int fd);
    void set_fd(int fd);
    int get_fd();
//  popc_connection_uds(int fd, pop_combox *cb);
//  popc_connection_uds(popc_connection_uds &me);

//  virtual pop_connection *Clone();

private:
    int _socket_fd;
};


class popc_combox_uds {
public:
    popc_combox_uds();
    ~popc_combox_uds();

    bool Create(const char *address, bool server);
    popc_connection_uds* combox_connect();
    int Send(const char *s,int len);
    int Send(const char *s,int len, popc_connection_uds* connection);

    int Recv(char *s,int len);
    int Recv(char *s,int len, popc_connection_uds* connection);

    popc_connection_uds* Wait();

    void Close();

    void set_timeout(int value);

private:

    int _socket_fd;
    struct sockaddr_un _sock_address;
    bool _is_server;
    std::string _uds_address;
    struct pollfd active_connection[10];
    int _active_connection_nb;
    int _timeout;
    bool _connected;

};

#endif // POPC_COMBOX_UNIX_DOMAIN_SOCKET_H







