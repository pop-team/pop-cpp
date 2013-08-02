mpi: mpi-matrix.c
	mpicc -o mpi-main mpi-matrix.c

mpirun: mpi
	mpiexec -np 5 ./mpi-main

xmp: xmp-matrix.c
	xmpcc -o xmp-main xmp-matrix.c

