#include "popc_mpi.h"
#include "TestMPI.ph"


int main(int argc, char **argv) {

	POPMPI<TestMPI> mpi(2);

	mpi[0].Set(100);

	printf("Values before: proc0=%d, proc1=%d\n", mpi[0].Get(), mpi[1].Get());

	mpi.ExecuteMPI();

	printf("Values after: proc0=%d, proc1=%d\n", mpi[0].Get(), mpi[1].Get());
}

