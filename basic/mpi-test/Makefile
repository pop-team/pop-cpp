all: main side

main: mpi_example.cpp
	mpic++ -o main mpi_example.cpp

side: mpi_example_side.cpp
	mpic++ -o side mpi_example_side.cpp

run: main side
	mpiexec -np 1 main

clean:
	rm -rf main side
