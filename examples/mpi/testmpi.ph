#include <mpi.h>

parclass TestMPI {

classuid(2000); 

public:
  TestMPI();
  async void ExecuteMPI();
  async void Set(int v);
  sync int Get();
private:
   int val;
};
