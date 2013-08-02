#include "mpiobject.ph"
#include <iostream>
#include <mpi.h>

MPIObject::MPIObject()
{
  std::cout << "MPI rank is:" << MPI::COMM_WORLD.Get_rank() << std::endl; 
}

MPIObject::~MPIObject()
{
  std::cout << "MPI Object is destroyed" << std::endl; 
}

void MPIObject::mpicalls()
{
  std::cout << "MPI communication" << std::endl;
  if(get_rank() == 0) {
    int data = 10; 
    MPI::COMM_WORLD.Send(&data, 1, MPI_INT, 1, 0);  
  } else {
    int data = 0; 
    MPI::COMM_WORLD.Recv(&data, 1, MPI_INT, 0, 0); 
    std::cout << "MPI recv: " << data  << std::endl; 
  }
}

