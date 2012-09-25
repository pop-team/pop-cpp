all: object app objmap

app:
	popcc -o main child.ph child.cc mother.ph mother.cc main.cc 

object: 
	popcc -c mother.ph mother.cc
	popcc -c child.ph child.cc
	popcc -object -o child.obj  child.o child.stub.o mother.stub.o mother.o
	
objmap:
	./child.obj -listlong > obj.map

run:
	popcrun obj.map ./main

clean:
	rm -f *.o *.obj main_seq main obj.map _paroc*
