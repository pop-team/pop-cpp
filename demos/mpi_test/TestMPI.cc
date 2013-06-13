#include <mpi.h>
#include "TestMPI.ph"



TestMPI::TestMPI() {
	val=0;
}

void TestMPI::ExecuteMPI() {
	MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

void TestMPI::Set(int v) {
	val = v;
}

int TestMPI::Get() {
	return val;
}

@pack(TestMPI);
