#include "mpiobject.ph"
#include <iostream>

int main(int argc, char* argv[])
{
  std::cout << "MPI Test case started ..." << std::endl;

  MPIObject mpi;
  mpi.initialize(2); 

  mpi.mpicalls();


  std::cout << "MPI Test case finished ..." << std::endl;

  return 0;
}

