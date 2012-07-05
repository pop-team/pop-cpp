# 
# Makefile for the POP-C++ POPFile library
# Author: Clement Valentin
# Creation Date: 03.25.2012
#

# Check POP-C++ installation directory
ifeq ($(POPC_LOCATION),)
	POPLOCATION=/usr/local/popc	
else
	POPLOCATION=$(POPC_LOCATION)
endif

# Define dependencies and source files
POPOBJECTDEPENDENCIES=popfilereader.cc popfilereader.ph
DEPENDENCIES=popfile.h popfile.cpp main.cpp popfile_metadata.h popfile_metadata.cpp popfilebuffer.h popfilebuffer.cpp popfile_grip.h popfile_grip.cpp
SOURCES=main.cpp popfile.cpp popfile.h tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp popfile_metadata.h \
popfile_metadata.cpp popfilebuffer.h popfilebuffer.cpp popfile_grip.h popfile_grip.cpp


# Define POP-C++ tools and libs path
AR=ar rcs
POPCC=popcc
POPCRUN=popcrun
POPCC_FLAG=-popc-static -I$(POPLOCATION)/include
POPCC_LIB=-L$(POPLOCATION)/lib/ -lparoc_service_common -lparoc_common

APPNAME=popfile_test_popc
LIBNAME=libpopfile.a
OBJNAME=popfilereader.obj
OBJMAP=objmap

all: popc $(OBJNAME) objmap lib

popc: $(DEPENDENCIES) $(POPOBJECTDEPENDENCIES)
	$(POPCC) -o $(APPNAME) $(POPCC_FLAG) $(POPCC_LIB) $(SOURCES) $(POPOBJECTDEPENDENCIES)
	
$(LIBNAME): lib
	
$(OBJNAME): $(POPOBJECTDEPENDENCIES) popfilebuffer.h popfilebuffer.cpp
	$(POPCC) $(POPCC_FLAG) $(POPCC_LIB) -object -o $(OBJNAME) $(POPOBJECTDEPENDENCIES) popfilebuffer.h popfilebuffer.cpp

objmap: $(POPOBJECTDEPENDENCIES) $(OBJNAME)
	./$(OBJNAME) -listlong > $(OBJMAP)

lib:
	$(AR) $(LIBNAME) *.o tinyxml/*.o
	
	
	
install: $(LIBNAME) $(OBJNAME)
ifeq ($(POPC_LOCATION),)
	@echo "[POPFILE-INSTALL] Copying lib to destination path"
	cp $(LIBNAME) /usr/local/popc/lib/
	
	@echo "[POPFILE-INSTALL] Copying headers to destination path"
	cp popfile.h /usr/local/popc/include/
	cp popfile_grip.h /usr/local/popc/include/	
	
	@echo "[POPFILE-INSTALL] Copying parallel objects to destination path"
	mkdir -p /usr/local/popc/objects/
	cp $(OBJNAME) /usr/local/popc/objects/
	
	@echo "[POPFILE-INSTALL] Creating base object map for popfile"
	$(POPC_LOCATION)/objects/$(OBJNAME) -listlong > /usr/local/popc/objects/$(OBJMAP)

	@echo "[POPFILE-INSTALL] Copying script helper to destination file"
	cp popfile-config /usr/local/popc/sbin/
else
	@echo "[POPFILE-INSTALL] Copying lib to destination path"
	cp $(LIBNAME) $(POPC_LOCATION)/lib/
	
	@echo "[POPFILE-INSTALL] Copying headers to destination path"
	cp popfile.h $(POPC_LOCATION)/include/
	cp popfile_grip.h $(POPC_LOCATION)/include/	
	cp popfile_metadata.h $(POPC_LOCATION)/include/	
	cp popfilebuffer.h $(POPC_LOCATION)/include/			
	
	@echo "[POPFILE-INSTALL] Copying parallel objects to destination path"
	mkdir -p $(POPC_LOCATION)/objects/
	cp $(OBJNAME) $(POPC_LOCATION)/objects/
	
	@echo "[POPFILE-INSTALL] Creating base object map for popfile"
	$(POPC_LOCATION)/objects/$(OBJNAME) -listlong > $(POPC_LOCATION)/objects/$(OBJMAP)

	@echo "[POPFILE-INSTALL] Copying script helper to destination file"
	cp popfile-config $(POPC_LOCATION)/sbin/
endif
	
clean:
	rm -rf _paroc* *.o tinyxml/*.o $(APPNAME) $(APPNAME_STD) $(OBJMAP) $(OBJNAME) $(LIBNAME)