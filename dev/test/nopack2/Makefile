all: app object

app:
	popcc -parclass-nobroker -c secondobject.ph secondobject.cc
	popcc -o main secondobject.stub.o popobject.ph popobject.cc main.cc

object:
	popcc -parclass-nobroker -c secondobject.ph secondobject.cc
	popcc -object -o POPObject.obj secondobject.stub.o popobject.cc popobject.ph
	popcc -object -o SecondObject.obj secondobject.cc secondobject.ph	
	./POPObject.obj -listlong > obj.map
	./SecondObject.obj -listlong >> obj.map
	
clean:
	rm -f *.o *.obj main obj.map _paroc*

run:
	popcrun obj.map ./main