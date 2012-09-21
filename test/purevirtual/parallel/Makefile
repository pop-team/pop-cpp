all: object app objmap

app:
	popcc -no-implicit-pack -noclean -o main child.ph child.cc mother.ph mother.cc main.cc 

object: 
	popcc -no-implicit-pack -noclean -c mother.ph mother.cc
	popcc -noclean -c child.ph child.cc
	popcc -noclean -object -o child.obj  child.o child.stub.o mother.stub.o mother.o
	
objmap:
	./child.obj -listlong > obj.map

run:
	popcrun obj.map ./main

clean:
	rm -f *.o *.obj main_seq main obj.map _paroc*
