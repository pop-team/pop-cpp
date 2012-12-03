POPC_PATH=/Users/clementval/popc



all: main pop_xmp_object.obj
object: pop_xmp_object.obj

main: main.cc pop_xmp_object.o
	popcc -cxx=mpic++ -cpp="mpic++ -E" -o main main.cc pop_xmp_object.o $(POPC_PATH)/lib/libpopc_common.a $(POPC_PATH)/lib/libpopc_advanced.a

pop_xmp_object.o: pop_xmp_object.h pop_xmp_object.cc
	mpic++ -I$(POPC_PATH)/include -c pop_xmp_object.cc  


pop_xmp_object.obj: pop_xmp_object_broker.h pop_xmp_object_broker.cpp
	mpic++ -I${POPC_PATH}/include -o pop_xmp_object.obj pop_xmp_object_object.cpp pop_xmp_object_broker.cpp $(POPC_PATH)/lib/popc_objmain.xmp.o $(POPC_PATH)/lib/libpopc_common.a $(POPC_PATH)/lib/libpopc_advanced.a

#pop_xmp_object.obj: pop_xmp_object_broker.h pop_xmp_object_broker.cpp
#	mpic++ -I${POPC_PATH}/include -o pop_xmp_object.obj pop_xmp_object_broker.cpp $(POPC_PATH)/lib/popc_objmain.xmp.o $(POPC_PATH)/lib/libpopc_common.a $(POPC_PATH)/lib/libpopc_advanced.a

run: main pop_xmp_object.obj
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main

clean: 
	rm -rf *.o main pop_xmp_object.obj
