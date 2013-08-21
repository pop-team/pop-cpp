main:
	popcc -o main exception.ph exception.cc IOExceptions.cc main.cc

object:
	popcc -object -o exception.obj IOExceptions.cc exception.ph exception.cc
	./exception.obj -listlong > objmap

clean:
	rm -f *.o _p*.* *.obj main

run:
	popcrun objmap ./main

