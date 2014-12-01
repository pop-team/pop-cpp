#include <mpi.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/un.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


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
        for(int i=0; i < 100; i++) {
            int data;
            MPI::COMM_WORLD.Recv(&data, 1, MPI_INT, 0, 0);
        }

        unlink("uds_0.0");
    }

    MPI::Finalize();
}

