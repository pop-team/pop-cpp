#ifndef _TestMPI
#define _TestMPI
#include "mpi.h"
parclass TestMPI {

public:
  classuid(12355);

  TestMPI() @{od.url("localhost");};
  async void ExecuteMPI();
  async void Set (int v);
  sync int Get();

private:
	int val;

};
#endif
