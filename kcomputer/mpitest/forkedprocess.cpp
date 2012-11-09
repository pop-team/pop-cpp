#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
  printf("Forked process started\n");
  struct sockaddr_un _sock_address;  
  int _socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
  if(_socket_fd < 0) {
    perror("socket() failed\n");
  } else {
    memset(&_sock_address, 0, sizeof(struct sockaddr_un));    
    _sock_address.sun_family = AF_UNIX;    
    strcpy(_sock_address.sun_path, "uds_0.0");  
    if(connect(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
      perror("Connect failed");
      return 1;
    } else {
      char* data = "message from uds client";
      int wbytes = write(_socket_fd, data, 25); 
      printf("Write %d - %s\n", wbytes, data); 
    }
  } 
}
