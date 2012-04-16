DEP=popfile.h popfile.cpp main.cpp popfile_metadata.h popfile_metadata.cpp
SOURCES=main.cpp popfile.cpp popfile.h tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp popfile_metadata.h \
popfile_metadata.cpp popfile_datathread.h popfile_datathread.cpp

GCC=g++
POPCC=popcc
POPCC_FLAG=-popc-static -I/usr/local/popc/include
APP1=popfile_test_alone
APP2=popfile_test_popc

all: popc

cc: $(DEP)
	$(GCC) -o $(APP1)  $(SOURCES)
	
popc: $(DEP)
	$(POPCC) -o $(APP2) $(POPCC_FLAG) $(SOURCES)
	
clean:
	rm -rf _paroc* *.o $(APP1) $(APP2)