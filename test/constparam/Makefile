all: main object

main:
	popcc -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc

object:
	popcc -object -o POPCobject.obj  data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map

run:
	popcrun obj.map ./main

clean:
	rm -f *.o
	rm -f *.obj
	rm -f main
	rm -f ob*
	rm -f _paroc*
	
debug: 
	../../parser/popcc -noclean -no-pipe -verbose -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc
	../../parser/popcc -noclean -verbose -object -o POPCobject.obj data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map
	
debug_spezial:
	../../parser/popcc -popcdir=../.. -popcpp=../../parser/popcpp -DHAVE_CONFIG_H -I. -I../.. -noclean -verbose -no-pipe -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc
	../../parser/popcc -popcdir=../.. -popcpp=../../parser/popcpp -noclean -verbose -no-pipe -object -o POPCobject.obj data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map
