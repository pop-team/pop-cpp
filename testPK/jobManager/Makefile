main:
	popcc -o main POPCobject.ph POPCobject.cc main.cc

object:
	popcc -object -o POPCobject.obj POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > objmap

run:
	popcrun objmap ./main 2 localhost localhost

clean:
	rm *.o
	rm *.obj
	rm main
