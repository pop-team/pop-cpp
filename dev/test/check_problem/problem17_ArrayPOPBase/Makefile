all: app object objmap

compile: app object

app:
	popcc -o main POPData.cc POPObject.ph POPObject.cc  main.cc

object:
	popcc -object -o POPObject.obj POPData.cc POPObject.cc POPObject.ph main.cc

objmap:
	./POPObject.obj -listlong > obj.map
	
clean:
	rm -f *.o *.obj main obj.map _paroc*

run:
	popcrun obj.map ./main
