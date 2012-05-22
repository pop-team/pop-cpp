POBJECTDEP=popfilereader.cc popfilereader.ph
DEP=popfile.h popfile.cpp main.cpp popfile_metadata.h popfile_metadata.cpp popfilebuffer.h popfilebuffer.cpp popfile_grip.h popfile_grip.cpp
SOURCES=main.cpp popfile.cpp popfile.h tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp popfile_metadata.h \
popfile_metadata.cpp popfilebuffer.h popfilebuffer.cpp popfile_grip.h popfile_grip.cpp
SOURCES_STD=main2.cpp

AR=ar rcs

GCC=g++

# Define POP-C++ tools and libs
POPCC=popcc
POPCRUN=popcrun
POPCC_FLAG=-popc-static -I/usr/local/popc/include
POPCC_LIB=-L/usr/local/popc/lib/ -lparoc_service_common -lparoc_common

# Define POP-C++ POPFile lib
POPFILE_LIB=-L./ -lpopfile

APPNAME=popfile_test_popc
LIBO=popfile.o
LIBNAME=libpopfile.a
APPNAME_STD=standard_test
OBJNAME=popfilereader.obj
OBJMAP=objmap

all: object popc objmap



popc: $(DEP) $(POPOBJECTDEP)
	$(POPCC) -o $(APPNAME) $(POPCC_FLAG) $(POPCC_LIB) $(SOURCES) $(POBJECTDEP)
	
lib: $(DEP) $(POPOBJECTDEP)
	$(POPCC) -c $(SOURCES) $(POBJECTDEP) -o $(LIBO) $(POPCC_FLAG) $(POPCC_LIB) 
	$(AR) $(LIBNAME) $(LIBO)

main:
	$(POPCC) -o $(APPNAME) main.cpp $(POPFILE_LIB)
	
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
	rm -rf _paroc* *.o tinyxml/*.o $(APPNAME) $(APPNAME_STD) $(OBJMAP) $(OBJNAME) hugefile testfile
	
clean-test:
	rm -rf hugefile testfile .popfile_hugefile.xml /tmp/.hugefile_strip* /tmp/.testfile_strip*