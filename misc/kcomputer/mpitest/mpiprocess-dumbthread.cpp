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
    pthread_exit(NULL);
    return NULL;
}


int main(int argc, char* argv[]) {
    MPI::Init();
    int rank = MPI::COMM_WORLD.Get_rank();
    int world = MPI::COMM_WORLD.Get_size();

    printf("Process %d, world size = %d\n", rank, world);

    if(rank == 0) {
        for(int i=0; i < 100; i++) {
            MPI::COMM_WORLD.Send(&i, 1, MPI_INT, 1, 0);
        }
    } else if(rank == 1) {
        pthread_t mpithread1, mpithread2;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_create(&mpithread1, &attr, mpireceivedthread, NULL);
        pthread_create(&mpithread2, &attr, mpireceivedthread, NULL);
        for(int i=0; i < 100; i++) {
            int data;
            MPI::COMM_WORLD.Recv(&data, 1, MPI_INT, 0, 0);
        }

        pthread_join(mpithread1, NULL);
        pthread_join(mpithread2, NULL);
        pthread_attr_destroy(&attr);

    }

    MPI::Finalize();
}

