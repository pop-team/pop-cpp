POP_FLAGS = ${FLAGS} -g
all: main object

main:
	popcc ${POP_FLAGS} -parclass-nobroker -c titi.ph titi.cc
	popcc ${POP_FLAGS} -o main titi.stub.o toto.ph toto.cc main.cc

object:
	popcc ${POP_FLAGS} -object -o toto.obj titi.stub.o toto.cc toto.ph
	popcc ${POP_FLAGS} -parclass-nobroker -c toto.ph toto.cc
	popcc ${POP_FLAGS} -object -o titi.obj toto.stub.o titi.ph titi.cc
	./toto.obj -listlong > obj.map
	./titi.obj -listlong >> obj.map

clean:
	rm -f *.o
	rm -f main
	rm -f *.obj
	rm -f obj.map

run:
	popcrun obj.map ./main
