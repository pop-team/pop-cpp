POPC_PATH=$(POPC_LOCATION)
POPC_LIB_PATH=$(POPC_PATH)/lib/dynamic
POPC_INCLUDE_PATH=$(POPC_PATH)/include/dynamic

all: main pop_xmp_object.obj
object: pop_xmp_object.obj
xmp: main xmp_object

main: main.cc pop_xmp_object.o
	popcc -cxx=mpic++ -cpp="mpic++ -E" -o main main.cc pop_xmp_object.o $(POPC_LIB_PATH)/libpopc_common.a $(POPC_LIB_PATH)/libpopc_advanced.a

pop_xmp_object.o: pop_xmp_object.h pop_xmp_object.cc
	mpic++ -I$(POPC_INCLUDE_PATH) -c pop_xmp_object.cc  


pop_xmp_object.obj: pop_xmp_object_broker.h pop_xmp_object_broker.cpp
	mpic++ -I$(POPC_INCLUDE_PATH) -o pop_xmp_object.obj pop_xmp_object_object.cpp pop_xmp_object_broker.cpp $(POPC_LIB_PATH)/popc_objmain.xmp.o $(POPC_LIB_PATH)/libpopc_common.a $(POPC_LIB_PATH)/libpopc_advanced.a

xmp_object:
	mpic++ -I$(POPC_INCLUDE_PATH) -I/home/clementval/xmp/include -D_XCALABLEMP -L/home/clementval/xmp/lib -o pop_xmp_object.obj pop_xmp_object_object.cpp pop_xmp_object_broker.cpp $(POPC_LIB_PATH)/popc_objmain.xmp.o $(POPC_LIB_PATH)/libpopc_common.a $(POPC_LIB_PATH)/libpopc_advanced.a -lxmp

run: main pop_xmp_object.obj
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main

runsafe: main pop_xmp_object.obj
	mpiexec -mca oob_tcp_if_exclude en1 -mca btl_tcp_if_exclude en1 -np 2 $(POPC_INTERCONNECTOR) -app=./main
	

clean: 
	rm -rf *.o main pop_xmp_object.obj uds_*
