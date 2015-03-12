FLAGS=-g
all: main object

main: exception.ph exception.cc IOExceptions.cc main.cc
	popcc ${FLAGS} -o main exception.ph exception.cc IOExceptions.cc main.cc

object:
	popcc ${FLAGS} -object -o exception.obj IOExceptions.cc exception.ph exception.cc
	./exception.obj -listlong > obj.map

clean:
	rm -f *.o _p*.* *.obj main obj.map

run:
	popcrun obj.map ./main

