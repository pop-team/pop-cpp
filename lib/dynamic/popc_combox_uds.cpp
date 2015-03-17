/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Implementation of the abstraction of a UDS communication
 *
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

#include "popc_combox_uds.h"
#include "popc_logger.h"

// Constant declaration
const char* popc_combox_uds::UDS_PROTOCOL_NAME = "uds";


/**
 * UDS Combox constructor initialize internal values
 */
popc_combox_uds::popc_combox_uds() : _socket_fd(-1), _is_server(false), _active_connection_nb(0),
    _timeout(-1), _connected(false), _is_first_connection(true) {
}

/**
 * UDS Combox destructor: Close the connection in case this combox has been connected.
 */
popc_combox_uds::~popc_combox_uds() {
    if(_connected) {
        Close();
    }
}

/**
 * Create a combox client or server with a port number. NOT USED FOR UDS COMBOX
 * @param port    Port number on which the combox should be create
 * @param server  FALSE for a client combox and TRUE for a server combox
 * @return FALSE in any cases
 */
bool popc_combox_uds::Create(int , bool) {
    return false;
}

/**
 * Create a combox with a string address. In the case of UDS combox, the string represent the path of the file representing the
 * socket.
 * @param address A path to the file representing the socket
 * @param server  FALSE for a client combox and TRUE for a server combox
 * @return TRUE if the combox has been created successfully, FALSE in any other cases.
 */
bool popc_combox_uds::Create(const char* address, bool server) {
    LOG_DEBUG_T("UDS", "Create %s", address);

    _is_server = server;
    _uds_address.clear();
    _uds_address.append(address);

    _socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(_socket_fd < 0) {
        LOG_ERROR_T("UDS", "socket() failed");
        return false;
    }

    LOG_DEBUG_T("UDS", "socket created");

    memset(&_sock_address, 0, sizeof(struct sockaddr_un));
    _sock_address.sun_family = AF_UNIX;
    strcpy(_sock_address.sun_path, address);

    if(_is_server) {
        _timeout = -1;
        unlink(address);

        if(bind(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
            LOG_WARNING_T("UDS", "bind() failed");
            return false;
        }

        if(listen(_socket_fd, 10) != 0) {
            LOG_WARNING_T("UDS", "listen() failed");
            return false;
        }

        active_connection[0].fd = _socket_fd;
        active_connection[0].events = POLLIN;
        active_connection[0].revents = 0;
        _active_connection_nb++;
    }

    return true;
}

/**
 * Connect to a server combox with its path
 * @param url Path to the file representing the socket to connect to.
 * @return TRUE if the connection is successful. FALSE in any other cases.
 */
bool popc_combox_uds::Connect(const char*) {
    if(connect(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
        LOG_WARNING("Connect failed: %s",_uds_address.c_str());
        perror("Connect failed");
        return false;
    }
    _connected = true;
    active_connection[0].fd = _socket_fd;
    active_connection[0].events = POLLIN;
    active_connection[0].revents = 0;
    _connection = new popc_connection_uds(_socket_fd, this);
    return true;
}

/**
 * Return the connection initialized with "Connect(const char* url)"
 * @return A pointer to the connection or NULL if this combox has no connection
 */
paroc_connection* popc_combox_uds::get_connection() {
    if(!_connected) {
        return NULL;
    }
    return _connection;
}

/**
 * Send bytes to another combox without connection. NOT USED IN UDS COMBOX
 */
int popc_combox_uds::Send(const char*,int) {
    return 0;
}

/**
 * Send bytes to another combox represented by a connection.
 * @param s           Pointer to the bytes to be written.
 * @param len         Number of bytes to write.
 * @param connection  Connection representing the endpoint to write bytes.
 * @return Number of bytes sent
 */
int popc_combox_uds::Send(const char *s, int len, paroc_connection *connection) {
    if(connection == NULL) {
        return -1;
    }
    int socket_fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();
    int wbytes = write(socket_fd, s, len);
    if(wbytes < 0) {
        perror("UDS Combox: Cannot write to socket");
    }

    return wbytes;
}

/**
 * Receive bytes from another combox without connection. NOT USED IN UDS COMBOX
 */
int popc_combox_uds::Recv(char*,int) {
    return 0;
}

/**
 * Receive bytes from another combox represented by a connection.
 * @param s           Pointer to the buffer where bytes must be written.
 * @param len         Number of bytes to read.
 * @param connection  Connection representing the endpoint from where to read bytes.
 * @return Number of bytes read
 */
int popc_combox_uds::Recv(char *s, int len, paroc_connection *connection) {
    int nbytes;
    int socket_fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();
    do {
        nbytes = read(socket_fd, s, len);
        if(nbytes < 0) {
            perror("Read");
        }
    } while(nbytes < 0);

    return nbytes;
}

/**
 * Add a file descriptor to the poll fd array
 * @param fd  File descriptor to add.
 */
void popc_combox_uds::add_fd_to_poll(int fd) {
    active_connection[_active_connection_nb].fd = fd;
    active_connection[_active_connection_nb].events = POLLIN;
    active_connection[_active_connection_nb].revents = 0;
    _active_connection_nb++;
}

/**
 * Wait for a new connection or data from an existing connection
 * @return A pointer to the ready connection
 */
paroc_connection* popc_combox_uds::Wait() {
    if(_is_server) {
        socklen_t address_length;
        address_length = sizeof(_sock_address);
        int poll_back;
        _timeout = timeout;
        do {
            poll_back = poll(active_connection, _active_connection_nb, _timeout);
            if(_active_connection_nb >= 199) {
                LOG_WARNING("TOO MANY CONNECTIONS");
            }
        } while((poll_back == -1) && (errno == EINTR));
        LOG_DEBUG("Poll %s", _uds_address.c_str());
        if(poll_back > 0) {
            for(int i = 0; i < _active_connection_nb; i++) {
                if(active_connection[i].revents & POLLIN) {
                    if(i == 0) {  // New connection
                        // A new connection can be received
                        int connection_fd;
                        connection_fd = accept(_socket_fd, (struct sockaddr *) &_sock_address, &address_length);
                        if(connection_fd < 0) {
                            perror("UDS Combox accept:");
                        } else {
                            active_connection[_active_connection_nb].fd = connection_fd;
                            active_connection[_active_connection_nb].events = POLLIN;
                            active_connection[_active_connection_nb].revents = 0;
                            _active_connection_nb++;
                            active_connection[i].revents = 0;
                            return new popc_connection_uds(connection_fd, this, true);
                        }
                    } else {
                        if(active_connection[i].revents & POLLHUP) { // POLLIN and POLLHUP
                            LOG_DEBUG("write and disconnect");
                            int tmpfd = active_connection[i].fd;
                            if(_active_connection_nb == 2) {
                                _active_connection_nb = 1;
                                active_connection[i].fd = 0;
                                active_connection[i].events = 0;
                                active_connection[i].revents = 0;
                            } else {
                                // Modify connection tab
                                _active_connection_nb--;
                                active_connection[i].fd = active_connection[_active_connection_nb].fd;
                                active_connection[i].events = active_connection[_active_connection_nb].events;
                                active_connection[i].revents = active_connection[_active_connection_nb].revents;
                            }
                            LOG_DEBUG("POLLON %s %d", _uds_address.c_str(), active_connection[i].fd);
                            return new popc_connection_uds(tmpfd, this);
                        } else { // Just POLLIN
                            LOG_DEBUG("POLLIN %s %d", _uds_address.c_str(), active_connection[i].fd);
                            active_connection[i].revents = 0;
                            return new popc_connection_uds(active_connection[i].fd, this);
                        }
                    }
                } else if(active_connection[i].revents & POLLHUP) {
                    LOG_DEBUG("%d fd is disconnected", active_connection[i].fd);
                    if(_active_connection_nb == 2) {
                        _active_connection_nb = 1;
                        active_connection[i].fd = 0;
                        active_connection[i].events = 0;
                        active_connection[i].revents = 0;
                        return NULL;
                    } else {
                        // Modify connection tab
                        _active_connection_nb--;
                        active_connection[i].fd = active_connection[_active_connection_nb].fd;
                        active_connection[i].events = active_connection[_active_connection_nb].events;
                        active_connection[i].revents = active_connection[_active_connection_nb].revents;
                        return NULL;
                    }
                }
            }
        } else if(poll_back == 0) {
            perror("combox: timeout");
            return NULL;
        } else {
            perror("poll");
            return NULL;
        }
    } else {
        int poll_back = poll(active_connection, 1, _timeout);
        if(poll_back > 0) {
            if(active_connection[0].revents & POLLIN) {
                return new popc_connection_uds(active_connection[0].fd, this);
            }
        } else if(poll_back == 0) {
            perror("timeout");
            return NULL;
        } else {
            perror("poll");
            return NULL;
        }
    }
    return NULL;
}

/**
 * Close the combox
 * For server: Close all open connection to this combox
 * For client: Close its own connection
 */
void popc_combox_uds::Close() {
    if(_is_server) {
        // TODO close all connection fd

        close(_socket_fd);
        unlink(_uds_address.c_str());
    } else {
        close(_socket_fd);
        _connected = false;
    }
}

/**
 * Get the protocol name for this combox
 * @param Reference to a std::string object to store the protocol name
 * @return TRUE in any cases.
 */
bool popc_combox_uds::GetProtocol(std::string & protocolName) {
    protocolName = UDS_PROTOCOL_NAME;
    return true;
}

/**
 * Get the current url of this combox. Format of the url is uds://uds_rank.object_id
 * @param Reference to a string object to store the url.
 * @return FALSE if the combox has no url. TRUE otherwise.
 */
bool popc_combox_uds::GetUrl(std::string & accesspoint) {
    if(_uds_address.length() == 0) {
        return false;
    }
    char elem[1024];
    sprintf(elem,"%s%s%s", UDS_PROTOCOL_NAME, paroc_combox::PROTOCOL_SEPARATOR, _uds_address.c_str());
    accesspoint = elem;
    return true;
}
