main:
	popcc -o main POPCobject.ph POPCobject.cc bytedata.cc main.cc

object:
	popcc -object -o POPCobject.obj POPCobject.ph POPCobject.cc bytedata.cc
	./POPCobject.obj -listlong > objmap

run:
	popcrun objmap ./main

clean:
	rm *.o
	rm *.obj
	rm main
