all: object app

app:
	popcc -o main child.ph child.cc mother.ph mother.cc main.cc 

object: 
	popcc -c mother.ph mother.cc
	popcc -c child.ph child.cc
	popcc -object -o child.obj  child.o child.stub.o mother.stub.o mother.o	
run:
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main

clean:
	rm -f *.o *.obj main_seq main obj.map
