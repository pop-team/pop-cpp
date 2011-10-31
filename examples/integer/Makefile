all: app object

app:

	popcc -o main integer.ph integer.cc main.cc

object:
	popcc -object -o integer.obj integer.cc integer.ph main.cc
	./integer.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main

