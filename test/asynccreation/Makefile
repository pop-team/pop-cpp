all: app object

noasync:
	popcc -no-async-allocation -o main POPObject.ph POPObject.cc main.cc
	popcc -no-async-allocation -object -o POPObject.obj POPObject.cc POPObject.ph main.cc 
	./POPObject.obj -listlong > obj.map

app:
	popcc -o main POPObject.ph POPObject.cc main.cc

object:
	popcc -object -o POPObject.obj POPObject.cc POPObject.ph main.cc
	./POPObject.obj -listlong > obj.map
	
clean:
	rm -f *.o *.obj main.exe obj.map _paroc*

run:
	popcrun obj.map ./main
