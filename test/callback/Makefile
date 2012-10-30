all: main object

main:
	popcc -parclass-nobroker -c titi.ph titi.cc
	popcc -o main titi.stub.o toto.ph toto.cc main.cc	

object:
	popcc -noclean -object -o toto.obj titi.stub.o toto.cc toto.ph
	popcc -noclean -parclass-nobroker -c toto.ph toto.cc
	popcc -noclean -object -o titi.obj toto.stub.o titi.ph titi.cc 
	./toto.obj -listlong > obj.map
	./titi.obj -listlong >> obj.map
	
clean:
	rm -f *.o
	rm -f main
	rm -f *.obj
	rm -f obj.map
	
run:
	mpiexec -np 2 ../../communicator/popc_mpi_communicator -app=./main
