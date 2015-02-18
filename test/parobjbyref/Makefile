all: app object

app:
	popcc -verbose -noclean -g -o main POPObject.ph POPObject.cc main.cc

object:
	popcc -verbose -noclean -g -object -o POPObject.obj POPObject.cc POPObject.ph main.cc
	./POPObject.obj -listlong > obj.map
	
clean:
	rm -f *.o *.obj main obj.map _paroc*

run:
	popcrun obj.map ./main
