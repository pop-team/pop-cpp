FLAGS=-g -noclean

all: main object

main:
	popcc ${FLAGS} -parclass-nobroker -c Barrier.ph Barrier.cc
	popcc ${FLAGS} -o main Barrier.stub.o worker.ph worker.cc main.cc

object:
	popcc ${FLAGS} -parclass-nobroker -c Barrier.ph Barrier.cc
	popcc ${FLAGS} -object -o Cworker.obj Barrier.stub.o worker.cc worker.ph
	popcc ${FLAGS} -object -o Barrier.obj Barrier.ph Barrier.cc
	./Cworker.obj -listlong > obj.map
	./Barrier.obj -listlong >> obj.map

clean:
	rm -f *.o
	rm -f *.obj
	rm -f main
	rm -f obj.map
run:
	popcrun obj.map ./main 10
