all: main popgroup.obj

object: popgroup.obj

main: main.cpp popgroup.ph popgroup.cpp
	popcc -cxx=mpic++ -cpp="mpic++ -E" -popc-static -xmp -noclean -o main main.cpp popgroup.ph popgroup.cpp

popgroup.obj: popgroup.ph popgroup.cpp
	popcc -cxx=mpic++ -cpp="mpic++ -E" -popc-static -xmp -noclean -object -o popgroup.obj popgroup.ph popgroup.cpp

run: main popgroup.obj 
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main

clean: 
	rm -rf main popgroup.obj _popc* *.o
