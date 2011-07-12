all: app object

app:
	popcc -o main data.cc parObject.ph parObject.cc main.cc 

object:
	popcc -object -o parObject.obj data.cc parObject.cc parObject.ph
	./parObject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
