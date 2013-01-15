all: main xmp.o

xmp.o: xmp.c
	gcc -c xmp.c

main: main.cpp xmp.o
	popcc -o main main.cpp xmp.o

run:
	mpiexec -np 1 ../../interconnector/popc_mpi_interconnector -app=./main

clean: 
	rm -f *.o main
