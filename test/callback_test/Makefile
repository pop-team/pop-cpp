all: app object

app:
	popcc -parclass-nobroker -c toto.ph
	popcc -o main toto.stub.o titi.ph titi.cc main.cc	

object:
	popcc -parclass-nobroker -c titi.ph
	popcc -object -o toto.obj titi.stub.o toto.cc toto.ph
	popcc -parclass-nobroker -c toto.ph
	popcc -object -o titi.obj toto.stub.o titi.cc titi.ph 
	./toto.obj -listlong > obj.map
	./titi.obj -listlong >> obj.map
	
clean:
	rm -f *.o *.obj main obj.map
	
run:
	popcrun obj.map ./main
