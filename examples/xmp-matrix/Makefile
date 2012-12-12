mpi: mpi-matrix.c
	mpicc -o mpi-main mpi-matrix.c

mpirun: mpi
	mpiexec -np 5 ./mpi-main

