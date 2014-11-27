all: app object

app:
	popcc -parclass-nobroker -c barrier.ph
	popcc -o main barrier.stub.o worker.ph worker.cc main.cc

object:
	popcc -parclass-nobroker -c barrier.ph
	popcc -object -o cworker.obj barrier.stub.o worker.cc worker.ph 
	popcc -object -o barrier.obj barrier.ph barrier.cc

	./cworker.obj -listlong > obj.map
	./barrier.obj -listlong >> obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main 10

