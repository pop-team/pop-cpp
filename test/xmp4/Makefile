POPC_PATH=$(POPC_LOCATION)
XMP_LIB=-lxmp
XMP_LIB_PATH=/home/clementval/xmp/lib

all: main pop_xmp_object.obj
object: pop_xmp_object.obj
xmp: main xmp_object

main: main.cpp pop_xmp_object.ph pop_xmp_object.cpp test.o
	popcc -xmp -popc-static -o main main.cpp pop_xmp_object.ph pop_xmp_object.cpp test.o $(XMP_LIB_PATH)/libxmp.a


pop_xmp_object.obj: pop_xmp_object.ph pop_xmp_object.cpp test.o
	popcc -xmp -popc-static -object -o pop_xmp_object.obj pop_xmp_object.ph pop_xmp_object.cpp test.o $(XMP_LIB_PATH)/libxmp.a

test.o: test.h test.c
	popc-xmpcc test.c

run: main pop_xmp_object.obj
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main

clean: 
	rm -rf *.o main pop_xmp_object.obj _popc* uds_* 
