all: main pop_xmp_object.obj
object: pop_xmp_object.obj

main: main.cc pop_xmp_object.o
	popcc -cxx=mpic++ -cpp="mpic++ -E" -o main main.cc pop_xmp_object.o

pop_xmp_object.o: pop_xmp_object.h pop_xmp_object.cc
	mpic++ -I../../include -c pop_xmp_object.cc  

pop_xmp_object.obj: pop_xmp_object.o 
	mpic++ -o pop_xmp_object.obj pop_xmp_object.o ../../xmp/popc_objmain.xmp.o ../../lib/libpopc_common.a

run: main pop_xmp_object.obj
	mpiexec -np 1 ../../interconnector/popc_mpi_interconnector -app=./main

clean: 
	rm -rf *.o main pop_xmp_object.obj
