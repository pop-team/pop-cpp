/**
 * Small program to check the thread support of an OpenMPI installation.
 *
 * @author Valentin Clement
 * @date 2012/11/05
 * @file openmpi_check_support.cpp
 */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int required_support, provided_support;
    // Initialize the local variable of the communicator
    if(!MPI::Is_initialized()) {
        // Init MPI for multithread support
        required_support = MPI_THREAD_SERIALIZED; // Maximum supported by the K Computer
        provided_support = MPI::Init_thread(required_support);
    }

    printf("MPI rank=%d size=%d\n", MPI::COMM_WORLD.Get_rank(), MPI::COMM_WORLD.Get_size());

    printf("MPI thread support available values:\n");
    printf("\tMPI_THREAD_SINGLE=%d\n", MPI_THREAD_SINGLE);
    printf("\tMPI_THREAD_FUNNELED=%d\n", MPI_THREAD_FUNNELED);
    printf("\tMPI_THREAD_SERIALIZED=%d\n", MPI_THREAD_SERIALIZED);
    printf("\tMPI_THREAD_MULTIPLE=%d\n", MPI_THREAD_MULTIPLE);


    printf("MPI thread support required = %d\n", required_support);
    printf("MPI thread support supported = %d\n", provided_support);

    printf("RESULTS =========>\n");
    if(provided_support < required_support) {
        printf("MPI thread support is too low\n");
    } else {
        printf("MPI thread support is sufficient\n");
    }

    MPI::Finalize();
    return 0;
}
