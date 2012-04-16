DEP=popfile.h popfile.cpp main.cpp popfile_metadata.h popfile_metadata.cpp
SOURCES=main.cpp popfile.cpp popfile.h tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp popfile_metadata.h \
popfile_metadata.cpp popfile_datathread.h popfile_datathread.cpp
POPCC=popcc
POPCC_FLAG=-popc-static -I/usr/local/popc/include
POPCC_LIB=-L/usr/local/popc/lib/ -lparoc_service_common -lparoc_common
APPNAME=popfile_test_popc

all: popc

popc: $(DEP)
	$(POPCC) -o $(APPNAME) $(POPCC_FLAG) $(POPCC_LIB) $(SOURCES)
	
run:
	./$(APPNAME)
	
clean:
	rm -rf _paroc* *.o tinyxml/*.o $(APPNAME)