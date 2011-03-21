all: app object

app:
	popcc -parclass-nobroker -c Barrier.ph
	popcc -o main Barrier.stub.o worker.ph worker.cc main.cc

object:
	popcc -parclass-nobroker -c Barrier.ph
	popcc -object -o Cworker.obj Barrier.stub.o worker.cc worker.ph 
	popcc -object -o Barrier.obj Barrier.ph Barrier.cc
	./Cworker.obj -listlong > obj.map
	./Barrier.obj -listlong >> obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main 10
