all: app object

app:

	popcc -noclean -cxx=mpic++ -o main integer.ph integer.cc main.cc

object:
	popcc -noclean -cxx=mpic++ -object -o integer.obj integer.cc integer.ph main.cc
	./integer.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main

