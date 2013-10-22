all: app object

app:
	popcc -o main POPObject.ph POPObject.cc main.cc

object:
	popcc -object -o POPObject.obj POPObject.cc POPObject.ph main.cc
	./POPObject.obj -listlong > obj.map
	
clean:
	rm -f *.o *.obj main.exe obj.map _paroc*

run:
	popcrun obj.map ./main
