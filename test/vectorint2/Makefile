all: app object

app:
	popcc -o main popintvector.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj popintvector.cc ParObject.cc ParObject.ph

clean:
	rm -f *.o *.obj main obj.map


run:
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main
