FLAGS=-g

all: main testobject.obj

main: testobject.ph testobject.cc main.cc
	popcc ${FLAGS} -o main testobject.ph testobject.cc main.cc

testobject.obj: testobject.cc testobject.ph
	popcc ${FLAGS} -object -o testobject.obj testobject.cc testobject.ph
	./testobject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main

run: all
	popcrun obj.map ./main > log.log
	# Comparing log with expected log
	diff log.log expected.log
