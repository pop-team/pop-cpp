/**
 *
 * @author Valentin Clement
 * @date 2012/11/29
 *
 */

#include <mpi.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    int rank;

    if(!MPI::Is_initialized()) {
        int required_support = MPI_THREAD_SERIALIZED;
        int provided_support = MPI::Init_thread(required_support);

        rank = MPI::COMM_WORLD.Get_rank();

        if(provided_support < required_support) {
            printf("POP-C++ Warning: Support of multithread in MPI is lower than required. Deadlock can block your application\n");
        } else {
            printf("POP-C++ XMP process started %d\n", rank);
        }
    }

    int nb_node = 2;

    const char* argv0[] = { (char*)0 };
    const char* commands[nb_node];
    const char **aargv[nb_node];
    int maxprocs[nb_node];
    int errcodes[nb_node];
    MPI::Info infos[nb_node];

    for(int i = 0; i < nb_node; i++) {
        commands[i] = (char*)"./spawned";
        aargv[i] = argv0;
        maxprocs[i] = 1;
    }

    MPI::Intercomm comm_xmp = MPI::COMM_WORLD.Spawn_multiple(nb_node, commands, aargv, maxprocs, infos, rank);


    int data1 = 10;
    comm_xmp.Send(&data1, 1, MPI_INT, 0, 0);

    int data2 = 11;
    comm_xmp.Send(&data2, 1, MPI_INT, 1, 0);

    int data3 = 12;
    comm_xmp.Send(&data3, 1, MPI_INT, 0, 0);

    int data4 = 13;
    comm_xmp.Send(&data4, 1, MPI_INT, 1, 0);

    MPI::Finalize();
}

