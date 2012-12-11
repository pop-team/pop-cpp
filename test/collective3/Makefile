all: popgroup-interface main popobject.obj popgroup.obj

object: popgroup.obj popobject.obj

main: main.cpp popgroup.ph popgroup.cpp
	popcc -cxx=mpic++ -cpp="mpic++ -E" -popc-static -xmp -noclean -o main main.cpp popobject.ph popobject.cpp popgroup.stub.o

popgroup-interface: 
	popcc -parclass-nobroker -cxx=mpic++ -cpp="mpic++ -E" -popc-static -xmp -noclean -object -o popgroup-nouse.obj popgroup.ph popgroup.cpp

popgroup.obj: popgroup.ph popgroup.cpp
	popcc -cxx=mpic++ -cpp="mpic++ -E" -popc-static -xmp -noclean -object -o popgroup.obj popgroup.ph popgroup.cpp

popobject.obj: popobject.ph popobject.cpp
	popcc -cxx=mpic++ -cpp="mpic++ -E" -popc-static -verbose -advanced -object -o popobject.obj popobject.ph popobject.cpp popgroup.stub.o

run: main popgroup.obj 
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main

clean: 
	rm -rf main *.obj _popc* *.o
