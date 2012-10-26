/**
 * File : combox_socket.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the communication box for TCP/socket
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */


#include <unistd.h>
#include <stdio.h>
#include <string.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

#include "popc_combox_uds.h"

popc_connection_uds::popc_connection_uds(paroc_combox *cb): paroc_connection(cb)
{
	_socket_fd = -1;
	signal(SIGPIPE, SIG_IGN);
}

popc_connection_uds::popc_connection_uds(int fd, paroc_combox *cb): _socket_fd(fd), paroc_connection(cb)
{
}

popc_connection_uds::popc_connection_uds(int fd, paroc_combox *cb, bool init): _socket_fd(fd), paroc_connection(cb, init)
{
}

popc_connection_uds::popc_connection_uds(popc_connection_uds &me): paroc_connection(me.GetCombox(), me.GetBufferFactory())
{
  _socket_fd = me.get_fd();
}

paroc_connection *popc_connection_uds::Clone()
{
	return new popc_connection_uds(*this);
}


void popc_connection_uds::set_fd(int fd)
{
  _socket_fd = fd;
}

int popc_connection_uds::get_fd()
{
  return _socket_fd;
}




/**
 * Unix Domain Socket combox implementation starts here
 */




popc_combox_uds::popc_combox_uds() : _socket_fd(-1), _is_server(false), _active_connection_nb(0), 
  _connected(false), _timeout(-1), _is_first_connection(true)
{
}

popc_combox_uds::~popc_combox_uds()
{
  if(_connected) {
    Close();
  }
}

bool popc_combox_uds::Create(int port, bool server)
{
  return false;
}

bool popc_combox_uds::Create(const char* address, bool server)
{
  //printf("UDS: create %s\n", address);
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
  
  if(_is_server){   
    _timeout = -1; 
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
/*    printf("POLLIN %d\n", POLLIN);
    printf("POLLHUP %d\n", POLLHUP);
    printf("POLLPRI %d\n", POLLPRI);
    printf("POLLOUT %d\n", POLLOUT);
    printf("POLLERR %d\n", POLLERR);        
    printf("POLLNVAL %d\n", POLLNVAL);
    printf("POLLHUP | POLLIN %d\n", (POLLIN | POLLHUP));         */
    return true;
  }	
  return true;
}


bool popc_combox_uds::Connect(const char *url)
{
  if(connect(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
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

paroc_connection* popc_combox_uds::get_connection()
{
  if(!_connected)
    return NULL;
  return _connection;
}

int popc_combox_uds::Send(const char *s,int len)
{
  int wbytes = send(_socket_fd, s, len, 0); 
  return wbytes;
}

int popc_combox_uds::Send(const char *s,int len, paroc_connection *connection)
{
  if(connection == NULL){
    return -1;
  }

  int socket_fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();
//  printf("Send to %d\n", socket_fd);
  int wbytes = write(socket_fd, s, len); 
//  printf("Sent  %d\n", wbytes);
  if(wbytes < 0)
    perror("Sent");
  return wbytes;	
}

int popc_combox_uds::Recv(char *s,int len)
{
	
}

int popc_combox_uds::Recv(char *s,int len, paroc_connection *connection)
{
  int nbytes;
  int socket_fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();
  //printf("Recv fd=%d\n", socket_fd);
  do {
    nbytes = read(socket_fd, s, len);
  } while (nbytes < 0);
  
  //printf("recv %d\n", nbytes);
  return nbytes;	
}


paroc_connection* popc_combox_uds::Wait()
{
  if(_is_server){
    socklen_t address_length;
    int poll_back = poll(active_connection, _active_connection_nb, _timeout);
    if(poll_back > 0) {
      for(int i = 0; i < _active_connection_nb; i++){
        if (active_connection[i].revents & POLLIN) {  
          if(i == 0) {  // New connection
            // A new connection can be received
            int connection_fd;      
            connection_fd = accept(_socket_fd, (struct sockaddr *) &_sock_address, &address_length);        
            //printf("Connected %d\n", connection_fd);
            active_connection[_active_connection_nb].fd = connection_fd;
        		active_connection[_active_connection_nb].events = POLLIN;      
            active_connection[_active_connection_nb].revents = 0;  
            _active_connection_nb++;
            active_connection[i].revents = 0;    
            if(_is_first_connection){
              _is_first_connection = false;
              return new popc_connection_uds(connection_fd, this);                     
            } else {
              return new popc_connection_uds(connection_fd, this, true);       
            }                                    
          } else {
            if(active_connection[i].revents & POLLHUP) { // POLLIN and POLLHUP
              //printf("write and disconnect\n");
              int tmpfd = active_connection[i].fd;
              if(_active_connection_nb == 2){
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
              return new popc_connection_uds(tmpfd, this);
            } else { // Just POLLIN
              //printf("POLLIN\n");
              active_connection[i].revents = 0;                  
              return new popc_connection_uds(active_connection[i].fd, this);
            }
          }
        } else if (active_connection[i].revents & POLLHUP) {
          //printf("%d fd is disconnected\n", active_connection[i].fd);
          if(_active_connection_nb == 2){
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
    } else if (poll_back == 0) { 
      perror("combox: timeout");
      return NULL;
    } else {
      perror("poll");
      return NULL;
    }
  } else {
    int poll_back = poll(active_connection, 1, _timeout);
    if(poll_back > 0) {
      if(active_connection[0].revents & POLLIN){
        return new popc_connection_uds(active_connection[0].fd, this);
      }      
    } else if (poll_back == 0) { 
      printf("Timeout\n");
      return NULL;
    } else {
      perror("poll");
      return NULL;
    }
  }
}

void popc_combox_uds::Close()
{
  if(_is_server){
    // TODO close all connection fd

    close(_socket_fd);
    unlink(_uds_address.c_str());
  } else {
    close(_socket_fd);
    _connected = false;
  }
}

bool popc_combox_uds::GetProtocol(POPString & protocolName)
{
	protocolName="uds";
	return true;
}

bool popc_combox_uds::GetUrl(POPString & accesspoint)
{
	char elem[1024];
	sprintf(elem,"uds://%s", _uds_address.c_str());
	accesspoint = elem;
	return true;
}
