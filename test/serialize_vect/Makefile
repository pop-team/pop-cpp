all: main myobj.obj

main: myobj.ph myobj.cc main.cc
	popcc -o main myobj.ph myobj.cc main.cc

myobj.obj: myobj.ph myobj.cc
	popcc -object -o myobj.obj myobj.ph myobj.cc

clean:
	rm -f *.o  *.obj main obj.map

run: main myobj.obj 
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main 10000 100
