POPC_PATH=$(POPC_LOCATION)

all: main pop_xmp_object.obj
object: pop_xmp_object.obj
xmp: main xmp_object

main: main.cpp pop_xmp_object.ph pop_xmp_object.cpp
	popcc -noclean -verbose -xmp -popc-static -o main main.cpp pop_xmp_object.ph pop_xmp_object.cpp


pop_xmp_object.obj: pop_xmp_object.ph pop_xmp_object.cpp
	popcc -noclean -verbose -xmp -popc-static -object -o pop_xmp_object.obj pop_xmp_object.ph pop_xmp_object.cpp

xmp_object:
	popcc -noclean -verbose -I/home/clementval/xmp/include -D_XCALABLEMP -L/home/clementval/xmp/lib -xmp -popc-static -object -o pop_xmp_object.obj pop_xmp_object.ph pop_xmp_object.cpp -lxmp

run: main pop_xmp_object.obj
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main

clean: 
	rm -rf *.o main pop_xmp_object.obj _popc* uds*
