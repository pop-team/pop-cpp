POP_FLAGS =-g ${FLAGS}

all: main object

main:
	popcc ${POP_FLAGS} -parclass-nobroker -c Barrier.ph Barrier.cc
	popcc ${POP_FLAGS} -o main Barrier.stub.o worker.ph worker.cc main.cc

object:
	popcc ${POP_FLAGS} -parclass-nobroker -c Barrier.ph Barrier.cc
	popcc ${POP_FLAGS} -object -o Cworker.obj Barrier.stub.o worker.cc worker.ph
	popcc ${POP_FLAGS} -object -o Barrier.obj Barrier.ph Barrier.cc
	./Cworker.obj -listlong > obj.map
	./Barrier.obj -listlong >> obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main 10

