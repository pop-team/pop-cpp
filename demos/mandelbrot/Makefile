#POPCDIR=/usr/local/popc
#INSTDIR=$(POPCDIR)/test/mandelbrot
QTCC=g++
QTCCFLAGS=-Wall -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -I/usr/include/qt3 -I/usr/qt/3/include
#QTMOC=/usr/qt/3/bin/moc
QTMOC=moc
QTLD=g++
#QTLDFLAGS=-L/usr/qt/3/lib -L/usr/X11R6/lib -lqt-mt -lXext -lX11 -lm
QTLDFLAGS=-L/usr/qt/3/lib -L/usr/X11R6/lib -lqt-mt

POPCC=popcc

QTOBJS=widget.o tile.o moc_widget.o chrono.o
POPOBJS=fractal.o screen.o main.o
POPPHS=fractal.ph screen.ph
TEMP=moc*.cpp _*paroc* *.stub.o
TARGET=fractal.master fractal.obj screen.obj obj.map

all:	$(TARGET)
	@echo "-----------------------------------------------"
	@echo "run it with:"
	@echo "popcrun obj.map ./fractal.master <options>"

.cpp.o:
	$(QTCC) -c $(QTCCFLAGS) $<

.cc.o:
	$(POPCC) -c $(POPCCFLAGS) $*.ph $<

fractal.master: $(POPOBJS) $(QTOBJS)
	rm -f fractal.o fractal.stub.o
	$(POPCC) -parclass-nobroker -c  fractal.ph fractal.cc
	$(POPCC) -o $@ $(POPPHS) $(POPOBJS) $(QTOBJS) $(QTLDFLAGS)

fractal.obj: screen.o screen.ph screen.cc fractal.cc fractal.ph
	rm -f screen.o screen.stub.o
	$(POPCC) -parclass-nobroker -c  screen.ph screen.cc
	$(POPCC) -object -o fractal.obj fractal.cc fractal.ph screen.stub.o

screen.obj: fractal.ph fractal.cc screen.cc screen.ph tile.o widget.o moc_widget.o chrono.o
	rm -f fractal.o fractal.stub.o
	$(POPCC) -parclass-nobroker -c  fractal.ph fractal.cc
	$(POPCC) -object -o screen.obj screen.cc screen.ph fractal.stub.o tile.o widget.o moc_widget.o chrono.o -lqt-mt  -I/usr/include/qt3


obj.map: fractal.obj screen.obj
	./fractal.obj -listlong > obj.map
	./screen.obj -listlong >> obj.map
moc_%.cpp: %.h
	$(QTMOC) -o $@ $<

clean:
	rm -f $(QTOBJS) $(POPOBJS) $(TEMP) $(TARGET)

depend:
	makedepend *.cc *.cpp 2>/dev/null

#install: fractal.master screen.obj fractal.obj
#	@if [ ! -d $(INSTDIR)/ ]; then mkdir $(INSTDIR)/; fi
#	cp *.obj fractal.master $(INSTDIR)/

run: obj.map machines.ip
	popcrun obj.map ./fractal.master 2 -1.743650449 1.043635821 -1.131818649 1.131833277 1

machines.ip:
	echo "localhost\nlocalhost\nlocalhost\nlocalhost" > machines.ip

# DO NOT DELETE

fractal.o: fractal.ph screen.ph tile.h /usr/include/math.h
fractal.o: /usr/include/features.h /usr/include/sys/cdefs.h
fractal.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
fractal.o: /usr/include/gnu/stubs-32.h /usr/include/bits/huge_val.h
fractal.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
main.o: screen.ph tile.h
screen.o: screen.ph tile.h fractal.ph chrono.h /usr/include/sys/time.h
screen.o: /usr/include/features.h /usr/include/sys/cdefs.h
screen.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
screen.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
screen.o: /usr/include/bits/typesizes.h /usr/include/time.h
screen.o: /usr/include/bits/time.h /usr/include/sys/select.h
screen.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
chrono.o: /usr/include/stdio.h /usr/include/features.h
chrono.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
chrono.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
chrono.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
chrono.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
chrono.o: /usr/include/bits/wchar.h /usr/include/gconv.h
chrono.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
chrono.o: /usr/include/string.h chrono.h /usr/include/sys/time.h
chrono.o: /usr/include/time.h /usr/include/bits/time.h
chrono.o: /usr/include/sys/select.h /usr/include/bits/select.h
chrono.o: /usr/include/bits/sigset.h
tile.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
tile.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
tile.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
tile.o: /usr/include/bits/typesizes.h /usr/include/libio.h
tile.o: /usr/include/_G_config.h /usr/include/wchar.h
tile.o: /usr/include/bits/wchar.h /usr/include/gconv.h
tile.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h tile.h
tile.o: widget.h
widget.o: tile.h widget.h
