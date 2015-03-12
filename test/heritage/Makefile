FLAGS=-g
all: app object

app:
	popcc ${FLAGS} -o main child.ph child.cc mother.ph mother.cc main.cc 

object: 
	popcc ${FLAGS} -c mother.ph mother.cc
	popcc ${FLAGS} -c child.ph child.cc
	popcc ${FLAGS} -object -o child.obj  child.o child.stub.o mother.stub.o mother.o
	./child.obj -listlong > obj.map
	
clean:
	rm -f *.o *.obj obj.map

run:
	popcrun obj.map ./main

