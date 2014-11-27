all: app object

app:
	popcc -o main -parclass-nobroker main.cc classA.cc classA.ph classB.cc classB.ph	

object:
	popcc -c -parclass-nobroker classB.ph
	popcc -object -o classA.obj classA.cc classA.ph classB.stub.o
	popcc -object -o classB.obj classB.ph classB.cc
	./classA.obj -listlong > obj.map
	./classB.obj -listlong >> obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
