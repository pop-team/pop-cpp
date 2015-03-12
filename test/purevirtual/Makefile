FLAGS=-g
all: object app objmap

app:
	popcc ${FLAGS} -o main child.ph child.cc mother.ph mother.cc main.cc 

object: 
	popcc ${FLAGS} -c mother.ph mother.cc
	popcc ${FLAGS} -c child.ph child.cc
	popcc ${FLAGS} -object -o child.obj  child.o child.stub.o mother.stub.o mother.o
	
objmap:
	./child.obj -listlong > obj.map

run:
	popcrun obj.map ./main

clean:
	rm -f *.o *.obj main_seq main obj.map _paroc*
