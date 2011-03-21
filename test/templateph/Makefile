all: app object

app:
	popcc ClassA.cc X.cc toto.ph toto.cc main.cc -o main

object:
	popcc -object -o toto.obj ClassA.cc X.cc toto.ph toto.cc
	./toto.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
