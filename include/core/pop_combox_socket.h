/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief socket declaration of combox
 *
 */

#ifndef POP_COMBOX_SOCKET_H
#define POP_COMBOX_SOCKET_H

#include <vector>

#include "pop_intface.h"
#include "pop_combox.h"
/**
 * @class pop_connection_sock
 * @brief Socket connection, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class pop_connection_sock : public pop_connection {
public:
    pop_connection_sock(pop_combox* cb);
    pop_connection_sock(int fd, pop_combox* cb);
    pop_connection_sock(pop_connection_sock& me);

    virtual pop_connection* Clone();
    virtual void reset() {
    }

    int sockfd;
};

/**
 * @class pop_combox_socket
 * @brief Socket declaration of combox, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class pop_combox_socket : public pop_combox {
public:
    pop_combox_socket();

    virtual ~pop_combox_socket();

    virtual bool Create(int port = 0, bool server = false);
    virtual bool Create(const char* /*address*/, bool /*server*/) {
        return false;
    }

    virtual bool Connect(const char* url);

    virtual int Send(const char* s, int len);
    virtual int Send(const char* s, int len, pop_connection* connection);
    virtual pop_connection* get_connection() {
        if (!peer) {
            return NULL;
        }
        return peer;
    }

    virtual int Recv(char* s, int len);
    virtual int Recv(char* s, int len, pop_connection* connection);

    virtual pop_connection* Wait();

    virtual void Close();

    /**
     * @brief Returns URL of object
     * @param accesspoint Returned URL (protocol://host:port)
     * @return true if success
     */
    virtual std::string GetUrl();
    virtual std::string GetProtocol();

protected:
    virtual pop_connection_sock* CreateConnection(int fd);
    bool CloseSock(int fd);
    bool Connect(const char* host, int port);

    int GetSockInfo(sockaddr& info, socklen_t& len);
    int GetPort();

    int GetOpt(int level, int opt, char* buf, socklen_t& len);
    int SetOpt(int level, int opt, char* buf, socklen_t len);

protected:
    int sockfd;
    bool isServer;
    bool isCanceled;
#ifdef __WIN32__
    int highsockfd;
    fd_set readfds, activefdset;
#else
    std::vector<pollfd> pollarray;
#endif
    pop_connection_sock* peer;

    // Only used by combox server...
    std::vector<pop_connection_sock*> connarray;
    int index;
    int nready;
};

#endif
