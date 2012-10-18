#include <mpi.h>
#include <stdio.h>


int main(int argc, char **argv)
{
  MPI::Init();
  int rank = MPI::COMM_WORLD.Get_rank();
  printf("Node %d started\n", rank);
  if(rank == 0){
    printf("Size of the network is %d\n", MPI::COMM_WORLD.Get_size());
  }

  MPI::Finalize();
}
