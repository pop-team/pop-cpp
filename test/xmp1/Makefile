POPC_PATH=$(POPC_LOCATION)

all: main pop_xmp_object.obj
object: pop_xmp_object.obj
xmp: main xmp_object

main: main.cpp pop_xmp_object.ph pop_xmp_object.cpp
	popcc -cxx=mpic++ -cpp="mpic++ -E" -xmp -noclean -popc-static -o main main.cpp pop_xmp_object.ph pop_xmp_object.cpp


pop_xmp_object.obj: pop_xmp_object.ph pop_xmp_object.cpp
	popcc -cxx=mpic++ -cpp="mpic++ -E" -xmp -noclean -popc-static -object -o pop_xmp_object.obj pop_xmp_object.ph pop_xmp_object.cpp

xmp_object:
	mpic++ -I${POPC_PATH}/include -I/home/clementval/xmp/include -D_XCALABLEMP -L/home/clementval/xmp/lib -o pop_xmp_object.obj pop_xmp_object_object.cpp pop_xmp_object_broker.cpp $(POPC_PATH)/lib/popc_objmain.xmp.o $(POPC_PATH)/lib/libpopc_common.a $(POPC_PATH)/lib/libpopc_advanced.a -lxmp

run: main pop_xmp_object.obj
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main

clean: 
	rm -rf *.o main pop_xmp_object.obj _popc*
