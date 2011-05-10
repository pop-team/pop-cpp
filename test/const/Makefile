all: app object

app:
	popcc -o main const.cc const.ph 

object:
	popcc -object -o const.obj const.cc const.ph
	./const.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main

debug: 
	../../parser/popcc -noclean -verbose -no-pipe -o main const.cc const.ph
	../../parser/popcc -noclean -verbose -object -o const.obj const.cc const.ph
	./const.obj -listlong > obj.map
