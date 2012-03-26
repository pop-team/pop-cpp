all: app object

app:
	popcc -o main child.ph child.cc mother.ph mother.cc main.cc 

object: 
	popcc -c mother.ph mother.cc
	popcc -c child.ph child.cc
	popcc -object -o child.obj  child.o child.stub.o mother.stub.o mother.o

	./child.obj -listlong > obj.map
	
clean:
	rm -f *.o *.obj obj.map

run:
	popcrun obj.map ./main

