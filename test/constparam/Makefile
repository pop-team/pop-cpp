FLAGS=-g
all: main object

main:
	popcc ${FLAGS} -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc

object:
	popcc ${FLAGS} -object -o POPCobject.obj  data.cc structdata.cc POPCobject.ph POPCobject.cc
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
	popcc ${FLAGS} -noclean -no-pipe -verbose -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc
	popcc ${FLAGS} -noclean -verbose -object -o POPCobject.obj data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map

debug_spezial:
	popcc ${FLAGS} -popcdir=../.. -popcpp=../../parser/popcpp -DHAVE_CONFIG_H -I. -I../.. -noclean -verbose -no-pipe -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc
	popcc ${FLAGS} -popcdir=../.. -popcpp=../../parser/popcpp -noclean -verbose -no-pipe -object -o POPCobject.obj data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map
