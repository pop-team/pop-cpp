POPCC=popcc

CFLAGS=
LFLAGS=

POPCCOMPILE=$(CFLAGS) $(LFLAGS)

all: main testobject.obj

main: testobject.ph testobject.cc main.cc
	$(POPCC) -o main testobject.ph testobject.cc main.cc $(POPCCOMPILE)

testobject.obj: testobject.cc testobject.ph
	$(POPCC) -object -o testobject.obj testobject.cc testobject.ph $(POPCCOMPILE)
	./testobject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main log.log

run: all
	popcrun obj.map ./main > log.log
	# Comparing log with expected log
	diff log.log expected.log
