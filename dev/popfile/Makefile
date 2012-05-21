POBJECTDEP=popfilereader.cc popfilereader.ph
DEP=popfile.h popfile.cpp main.cpp popfile_metadata.h popfile_metadata.cpp popfilebuffer.h popfilebuffer.cpp popfile_grip.h popfile_grip.cpp
SOURCES=main.cpp popfile.cpp popfile.h tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp popfile_metadata.h \
popfile_metadata.cpp popfile_datathread.h popfile_datathread.cpp popfilebuffer.h popfilebuffer.cpp popfile_grip.h popfile_grip.cpp
SOURCES_STD=main2.cpp
POPCC=popcc
POPCRUN=popcrun
GCC=g++
POPCC_FLAG=-popc-static -I/usr/local/popc/include
POPCC_LIB=-L/usr/local/popc/lib/ -lparoc_service_common -lparoc_common
APPNAME=popfile_test_popc
APPNAME_STD=standard_test
OBJNAME=popfilereader.obj
OBJMAP=objmap

all: object popc objmap

popc: $(DEP) $(POPOBJECTDEP)
	$(POPCC) -o $(APPNAME) $(POPCC_FLAG) $(POPCC_LIB) $(SOURCES) $(POBJECTDEP)
	
object: $(POBJECTDEP) popfilebuffer.h popfilebuffer.cpp
	$(POPCC) $(POPCC_FLAG) $(POPCC_LIB) -object -o $(OBJNAME) $(POBJECTDEP) popfilebuffer.h popfilebuffer.cpp

objmap: $(POBJECTDEP) $(OBJNAME)
	./$(OBJNAME) -listlong > $(OBJMAP)
	
std:
	$(GCC) -o $(APPNAME_STD) $(SOURCES_STD)
	
runstd:
	./$(APPNAME_STD)
	
run:
	$(POPCRUN) $(OBJMAP) ./$(APPNAME) 
	
clean:
	rm -rf _paroc* *.o tinyxml/*.o $(APPNAME) $(APPNAME_STD) $(OBJMAP) $(OBJNAME)