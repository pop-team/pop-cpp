all: main POPObject.obj

main: main.cc POPObject.ph POPObject.cc
	popcc -noclean -o main POPObject.ph POPObject.cc main.cc

POPObject.obj: POPObject.ph POPObject.cc
	popcc -noclean -object -o POPObject.obj POPObject.cc POPObject.ph
	./POPObject.obj -listlong > obj.map
	
clean:
	rm -f *.o *.obj main obj.map _popc*

run:
	popcrun obj.map ./main
