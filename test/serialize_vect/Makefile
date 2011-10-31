all: main myobj.obj

main: myobj.ph myobj.cc main.cc
	popcc -o main myobj.ph myobj.cc main.cc

myobj.obj: myobj.ph myobj.cc
	popcc -object -o myobj.obj myobj.ph myobj.cc

clean:
	rm -f *.o  *.obj main

#install: all 
#	if [ ! -d $(INSTDIR)/ ]; then mkdir $(INSTDIR)/; fi
#	p *.obj main  $(INSTDIR)/

obj.map: myobj.obj
	./myobj.obj -listlong > obj.map

run: main myobj.obj obj.map
	popcrun obj.map ./main 10000 100
