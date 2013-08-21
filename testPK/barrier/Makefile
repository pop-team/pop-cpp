main:
	popcc -parclass-nobroker -c Barrier.ph Barrier.cc
	popcc -o main Barrier.stub.o worker.ph worker.cc main.cc

object:
	popcc -parclass-nobroker -c Barrier.ph Barrier.cc
	popcc -object -o Cworker.obj Barrier.stub.o worker.cc worker.ph 
	popcc -object -o Barrier.obj Barrier.ph Barrier.cc
	./Cworker.obj -listlong > objmap
	./Barrier.obj -listlong >> objmap

clean:
	rm -f *.o
	rm -f *.obj
	rm -f main
run:
	popcrun objmap ./main 10
