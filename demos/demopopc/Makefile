all: app object

app:
	popcc -o main demopopc.ph demopopc.cc main.cc
   echo "POPCobject i686-pc-Linux http://valentin.clement.home.hefr.ch/demopopc.obj" > obj.map
object:
	popcc -object -o demopopc.obj demopopc.cc demopopc.ph main.cc
clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main 2 - -
rund:
	POPC_DEBUG=1 popcrun obj.map ./main 2 - -
