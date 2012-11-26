#include <popc_mpi.h>
#include <stdio.h>
#include <mpi.h>
#include "testmpi.ph"


int main(int argc, char **argv) {
  int nb_processes = 10; 
  POPMPI<TestMPI> mpi(nb_processes);
  mpi[0].Set(100); //Set on MPI process 0

  printf("Value before broadcast\n"); 
  for(int i = 0; i < nb_processes; i++) {
    printf("process %d = %d\n", i, mpi[i].Get()); 
  }
  mpi.ExecuteMPI(); //Call ExecuteMPI methods on all MPI processes
  
  printf("Values after complete\n");
  for(int i = 0; i < nb_processes; i++) {
    printf("process %d = %d\n", i, mpi[i].Get()); 
  }

}
