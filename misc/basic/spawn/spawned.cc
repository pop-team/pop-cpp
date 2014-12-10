/**
 *
 * @author Valentin Clement
 * @date 2012/11/29
 *
 */

#include <mpi.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    MPI::Intercomm communicator;
    int rank;

    if(!MPI::Is_initialized()) {
        int required_support = MPI_THREAD_SERIALIZED;
        int provided_support = MPI::Init_thread(required_support);

        communicator = MPI::COMM_WORLD.Get_parent();
        rank = MPI::COMM_WORLD.Get_rank();

        if(provided_support < required_support) {
            printf("POP-C++ Warning: Support of multithread in MPI is lower than required. Deadlock can block your application\n");
        } else {
            printf("POP-C++ XMP spawned process started %d\n", rank);
        }
    }

    int data1;
    communicator.Recv(&data1, 1, MPI_INT, 0, 0);
    printf("%d recv %d\n", MPI::COMM_WORLD.Get_rank(), data1);

    int data2;
    communicator.Recv(&data2, 1, MPI_INT, 0, 0);
    printf("%d recv %d\n", MPI::COMM_WORLD.Get_rank(), data2);


    MPI::Finalize();
}

