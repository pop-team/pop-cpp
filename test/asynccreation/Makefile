all: async 

sync: app object

async:
	popcc -async-allocation -o main POPObject.ph POPObject.cc main.cc
	popcc -async-allocation -object -o POPObject.obj POPObject.cc POPObject.ph main.cc 

app:
	popcc -o main POPObject.ph POPObject.cc main.cc

object:
	popcc -object -o POPObject.obj POPObject.cc POPObject.ph main.cc
	
clean:
	rm -f *.o *.obj main obj.map _popc*

run:
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main
