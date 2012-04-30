DEP=popfile.h popfile.cpp main.cpp popfile_metadata.h popfile_metadata.cpp popfilebuffer.h popfilebuffer.cpp
SOURCES=main.cpp popfile.cpp popfile.h tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp popfile_metadata.h \
popfile_metadata.cpp popfile_datathread.h popfile_datathread.cpp popfilebuffer.h popfilebuffer.cpp
SOURCES_STD=main2.cpp
POPCC=popcc
GCC=g++
POPCC_FLAG=-popc-static -I/usr/local/popc/include
POPCC_LIB=-L/usr/local/popc/lib/ -lparoc_service_common -lparoc_common
APPNAME=popfile_test_popc
APPNAME_STD=standard_test

all: popc

popc: $(DEP)
	$(POPCC) -o $(APPNAME) $(POPCC_FLAG) $(POPCC_LIB) $(SOURCES)
	
	
std:
	$(GCC) -o $(APPNAME_STD) $(SOURCES_STD)
	
runstd:
	./$(APPNAME_STD)
	
run:
	./$(APPNAME) 
	
clean:
	rm -rf _paroc* *.o tinyxml/*.o $(APPNAME) $(APPNAME_STD) testfile