all:
	
	popcc -object -o myobj4.obj myobj4.ph myobj4.cc
	
	popcc -c -parclass-nobroker myobj4.ph
	popcc -object -o myobj3.obj myobj3.ph myobj3.cc myobj4.stub.o

	popcc -c -parclass-nobroker myobj3.ph
	popcc -object -o myobj2.obj myobj2.ph myobj2.cc myobj3.stub.o

	popcc -c -parclass-nobroker myobj2.ph 
	popcc -object -o myobj1.obj myobj1.ph myobj1.cc myobj2.stub.o


	popcc -o main main.cc myobj1.ph myobj1.cc myobj2.stub.o

	./myobj1.obj -listlong > obj.map
	./myobj2.obj -listlong >> obj.map
	./myobj3.obj -listlong >> obj.map
	./myobj4.obj -listlong >> obj.map

clean:
	rm -f *.o *.obj main obj.map
	
run:
	popcrun obj.map ./main

