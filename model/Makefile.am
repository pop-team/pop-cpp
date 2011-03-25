AUTOMAKE_OPTIONS=no-dependencies

export POPC_CXX=@CXX@

CXX=@top_srcdir@/parser/popcc
POPC_FLAGS=-parocdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp 

AM_CXXFLAGS=-cxxmain  $(POPC_FLAGS)

%.stub.o : %.ph
	$(CXX) $(POPC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) -I../lib -c $<

lib_LIBRARIES = libparoc_tcmodel.a 
inst_HEADERS=modelgene.h model.h 
model_DATA=probobj.ph 

instdir=@includedir@
modeldir=@includedir@

libparoc_tcmodel_a_SOURCES=model.cc modelgene.cc probobj.cc 
libparoc_tcmodel_a_LIBADD=probobj.stub.o

EXTRA_DIST= probobj.ph

CLEANFILES=


