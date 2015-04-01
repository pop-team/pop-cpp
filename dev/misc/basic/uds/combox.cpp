#include "combox.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <errno.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

/*
popc_connection_uds::popc_connection_uds() : _socket_fd(-1)
{

}*/

popc_connection_uds::popc_connection_uds(int fd) {
    _socket_fd = fd;
}

void popc_connection_uds::set_fd(int fd) {
    _socket_fd = fd;
}

int popc_connection_uds::get_fd() {
    return _socket_fd;
}


popc_combox_uds::popc_combox_uds() : _socket_fd(-1), _is_server(false), _active_connection_nb(0), _connected(false), _timeout(-1) {

}

popc_combox_uds::~popc_combox_uds() {
    if(_connected) {
        Close();
    }
}


bool popc_combox_uds::Create(const char *address, bool server=false) {
    _is_server = server;
    _uds_address.clear();
    _uds_address.append(address);

    _socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(_socket_fd < 0) {
        printf("socket() failed\n");
        return false;
    }

    memset(&_sock_address, 0, sizeof(struct sockaddr_un));
    _sock_address.sun_family = AF_UNIX;
    strcpy(_sock_address.sun_path, address);

    if(_is_server) {
        unlink(address);

        if(bind(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
            printf("bind() failed\n");
            return false;
        }


        if(listen(_socket_fd, 5) != 0) {
            printf("listen() failed\n");
            return false;
        }

        active_connection[0].fd = _socket_fd;
        active_connection[0].events = POLLIN;
        active_connection[0].revents = 0;
        _active_connection_nb++;
        printf("POLLIN %d\n", POLLIN);
        printf("POLLHUP %d\n", POLLHUP);
        printf("POLLPRI %d\n", POLLPRI);
        printf("POLLOUT %d\n", POLLOUT);
        printf("POLLERR %d\n", POLLERR);
        printf("POLLNVAL %d\n", POLLNVAL);
        printf("POLLHUP | POLLIN %d\n", (POLLIN | POLLHUP));
    }
}

popc_connection_uds* popc_combox_uds::combox_connect() {
    if(connect(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
        printf("connect() failed\n");
        return NULL;
    }
    _connected = true;
    active_connection[0].fd = _socket_fd;
    active_connection[0].events = POLLIN;
    active_connection[0].revents = 0;

    return new popc_connection_uds(_socket_fd);
}

int popc_combox_uds::Send(const char *s, int len) {
    int wbytes = send(_socket_fd, s, len, 0);
    return wbytes;
}

int popc_combox_uds::Send(const char *s, int len, popc_connection_uds* connection) {
    if(connection == NULL) {
        std::cout << "combox connection is null" << std::endl;
        return -1;
    }

    int socket_fd = connection->get_fd();
    printf("Send to %d\n", socket_fd);
    int wbytes = write(socket_fd, s, len);
    printf("Sent  %d\n", wbytes);
    if(wbytes < 0) {
        perror("Sent");
    }
    return wbytes;
}

int popc_combox_uds::Recv(char *s,int len) {

}



int popc_combox_uds::Recv(char *s,int len, popc_connection_uds* connection) {
    int nbytes;
    printf("Recv fd=%d\n", connection->get_fd());

    /*
    popc_connection_uds* current_connection;

    do {
        if (connection == NULL) {
            current_connection = (popc_connection_uds*)Wait();
            if (current_connection == NULL)
              return -1;
            socket_fd = current_connection->get_fd();
        } else {
            socket_fd = connection->get_fd();
        }
        if (socket_fd < 0)
          return -1;

        while ((nbytes = recv(socket_fd, s, len, 0)) < 0 && errno == EINTR);
        if (nbytes == 0) {
      // if (CloseSock(fd) && iopeer==NULL) continue;
            return -1;
        }
    } while (nbytes <= 0);

    if (connection == NULL) {
      connection = current_connection;
    }
    if (nbytes <= 0)
      errno=EIO;
    */

    do {
        nbytes = read(connection->get_fd(), s, len);
    } while(nbytes < 0);

    printf("recv %d\n", nbytes);

    /* printf("should read %d\n", len);
    do {
      while((nbytes = read(conn->get_fd(), s, len)) < 0 && errno == EINTR);
      if(nbytes == 0){
        // close socket
        return -1;
      }
    } while(nbytes <= 0);
    printf("Read %d\n", nbytes);*/
    return nbytes;
}

popc_connection_uds* popc_combox_uds::Wait() {
    if(_is_server) {
        socklen_t address_length;
        int poll_back = poll(active_connection, _active_connection_nb, _timeout);
        if(poll_back > 0) {
            for(int i = 0; i < _active_connection_nb; i++) {
                if(active_connection[i].revents & POLLIN) {
                    if(i == 0) {  // New connection
                        // A new connection can be received
                        int connection_fd;
                        connection_fd = accept(_socket_fd, (struct sockaddr *) &_sock_address, &address_length);
                        printf("Connected %d\n", connection_fd);
                        active_connection[_active_connection_nb].fd = connection_fd;
                        active_connection[_active_connection_nb].events = POLLIN;
                        active_connection[_active_connection_nb].revents = 0;
                        _active_connection_nb++;
                        active_connection[i].revents = 0;
                        return new popc_connection_uds(connection_fd);
                    } else {
                        if(active_connection[i].revents & POLLHUP) { // POLLIN and POLLHUP
                            printf("write and disconnect\n");
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
                            return new popc_connection_uds(tmpfd);
                        } else { // Just POLLIN
                            printf("POLLIN\n");
                            active_connection[i].revents = 0;
                            return new popc_connection_uds(active_connection[poll_back-1].fd);
                        }
                    }
                } else if(active_connection[i].revents & POLLHUP) {
                    printf("%d fd is disconnected\n", active_connection[i].fd);
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
                }
            }
        } else if(poll_back == 0) {
            printf("Timeout\n");
            return NULL;
        } else {
            perror("poll");
            return NULL;
        }
    } else {
        int poll_back = poll(active_connection, 1, _timeout);
        if(poll_back > 0) {
            if(active_connection[0].revents & POLLIN) {
                return new popc_connection_uds(active_connection[0].fd);
            }
        } else if(poll_back == 0) {
            printf("Timeout\n");
            return NULL;
        } else {
            perror("poll");
            return NULL;
        }
    }






}

void popc_combox_uds::Close() {
    if(_is_server) {
        close(_socket_fd);
        unlink(_uds_address.c_str());
    } else {
        close(_socket_fd);
        _connected = false;
    }
}

void popc_combox_uds::set_timeout(int value) {
    _timeout = value;

}

