#include <mpi.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/un.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void *mpireceivedthread(void *t) {
    printf("Forked process started\n");
    struct sockaddr_un _sock_address;
    int _socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(_socket_fd < 0) {
        perror("socket() failed\n");
    } else {
        memset(&_sock_address, 0, sizeof(struct sockaddr_un));
        _sock_address.sun_family = AF_UNIX;
        strcpy(_sock_address.sun_path, "./uds_0.0");
        if(connect(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
            perror("Connect failed");
            pthread_exit(NULL);
        } else {
            char* data = "message from uds client";
            int wbytes = write(_socket_fd, data, 25);
            if(wbytes < 0) {
                perror("UDS Socket: Cannot write to socket");
            }
            printf("Write %d - %s\n", wbytes, data);
        }
    }
    close(_socket_fd);
    pthread_exit(NULL);
    return NULL;
}


int main(int argc, char* argv[]) {
    MPI::Init();
    int rank = MPI::COMM_WORLD.Get_rank();
    int world = MPI::COMM_WORLD.Get_size();

    printf("Process %d, world size = %d\n", rank, world);

    if(rank == 1) {
        int data;
        MPI::COMM_WORLD.Recv(&data, 1, MPI_INT, 0, 0);
        printf("MPI Recv %d\n", data);
        MPI::Finalize();
    } else if(rank == 0) {
        int i = 10;
        MPI::COMM_WORLD.Isend(&i, 1, MPI_INT, 1, 0);

        struct sockaddr_un _sock_address;
        socklen_t address_length;
        int _socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);

        if(_socket_fd < 0) {
            perror("socket() failed\n");
        } else {
            memset(&_sock_address, 0, sizeof(struct sockaddr_un));
            _sock_address.sun_family = AF_UNIX;
            strcpy(_sock_address.sun_path, "./uds_0.0");
            unlink("uds_0.0");
            if(bind(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
                perror("bind() failed\n");
            } else {
                if(listen(_socket_fd, 10) != 0) {
                    perror("listen() failed\n");
                }
            }
        }

        pthread_t mpithread1, mpithread2;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_create(&mpithread1, &attr, mpireceivedthread, NULL);
        pthread_create(&mpithread2, &attr, mpireceivedthread, NULL);


        /*  pid_t allocatepid = fork();
          if(allocatepid == 0) {
            char* argv1[3];
            argv1[0] = (char*)"forkedprocess";
            argv1[1] = "1";
            argv1[2] = (char*)0;
            execv(argv1[0], argv1);
            perror("Execv failed");
          }

          allocatepid = fork();
          if(allocatepid == 0) {
            char* argv1[3];
            argv1[0] = (char*)"forkedprocess";
            argv1[1] = "2";
            argv1[2] = (char*)0;
            execv(argv1[0], argv1);
            perror("Execv failed");
          } */

        struct pollfd active_connection[5];
        int active_connection_number = 0;
        active_connection[active_connection_number].fd = _socket_fd;
        active_connection[active_connection_number].events = POLLIN;
        active_connection[active_connection_number].revents = 0;
        active_connection_number++;
        bool active = true;
        int cnt = 0;
        while(active) {
            int poll_back = poll(active_connection, active_connection_number, -1);
            for(int i = 0; i < active_connection_number; i++) {
                if(active_connection[i].revents & POLLIN) {
                    if(i == 0) {
                        printf("Wait for connection\n");
                        int connection_fd = accept(_socket_fd, (struct sockaddr *) &_sock_address, &address_length);
                        printf("New connection\n");
                        active_connection[active_connection_number].fd = connection_fd;
                        active_connection[active_connection_number].events = POLLIN;
                        active_connection[active_connection_number].revents = 0;
                        active_connection_number++;
                        active_connection[i].revents = 0;
                    } else {
                        printf("New data\n");
                        int tmpfd = active_connection[i].fd;
                        if(tmpfd != 0) {
                            char* data = new char[25];
                            int nbytes = read(tmpfd, data, 25);
                            printf("Receive %d %d - %s\n", i, nbytes, data);
                            cnt++;
                            if(cnt == 2) {
                                active = false;
                            }
                        }
                    }
                }
            }
        }

        for(int i = 0; i < active_connection_number; i++) {
            close(active_connection[i].fd);
        }



        unlink("uds_0.0");
        pthread_join(mpithread1, NULL);
        pthread_join(mpithread2, NULL);
        pthread_attr_destroy(&attr);
        MPI::Finalize();
    }

}

