all: object app

app:
	popcc -o main child.ph child.cc mother.ph mother.cc main.cc 
#	g++ -o main_seq main.cc mother.cc child.cc

object: 
	popcc -c mother.ph mother.cc
	popcc -c child.ph child.cc
	popcc -object -o child.obj  child.o child.stub.o mother.stub.o mother.o	
	./child.obj -listlong > obj.map
	

run:
	popcrun obj.map ./main

#run_seq:
#	./main_seq

clean:
	rm -f *.o *.obj main_seq main obj.map
