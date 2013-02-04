all: app object

app:
	popcc -noclean -o main POPObject.ph POPObject.cc main.cc

object:
	popcc -noclean -object -o POPObject.obj POPObject.cc POPObject.ph main.cc
	
clean:
	rm -f *.o *.obj main obj.map _popc*

run:
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main
