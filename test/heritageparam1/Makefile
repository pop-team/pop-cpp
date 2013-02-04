all: app object

app:
	popcc -o main heritdata.cc data.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj heritdata.cc data.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map


run:
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main
