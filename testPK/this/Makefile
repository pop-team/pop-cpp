main:
	popcc -parclass-nobroker -c titi.ph titi.cc
	popcc -o main titi.o titi.stub.o toto.ph toto.cc main.cc	

object:
	popcc -parclass-nobroker -c titi.ph titi.cc
	popcc -object -o toto.obj titi.stub.o toto.cc toto.ph
	popcc -parclass-nobroker -c toto.ph toto.cc
	popcc -object -o titi.obj toto.stub.o titi.ph titi.cc 
	./toto.obj -listlong > objmap
	./titi.obj -listlong >> objmap
	
clean:
	rm -f *.o
	rm -f main

	rm -f *.obj
	
run:
	popcrun objmap ./main
