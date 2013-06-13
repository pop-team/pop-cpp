# Makefile for the POPFile demo application	

# Check POP-C++ installation directory
ifeq ($(POPC_LOCATION),)
	POPLOCATION=/usr/local/popc	
else
	POPLOCATION=$(POPC_LOCATION)
endif


POPCC=popcc
POPCRUN=popcrun
DEPENDENCIES=main.cpp
SOURCES=main.cpp
APPNAME=popfile_test


all: $(DEPENDENCIES)
	$(POPCC) -o $(APPNAME) $(SOURCES) -I$(POPLOCATION)/include -L$(POPLOCATION)/lib -lpopfile

run:	
	$(POPCRUN) $(POPLOCATION)/objects/objmap ./$(APPNAME)

clean: 
	rm -rf $(APPNAME) *.o