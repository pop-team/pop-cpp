AUTOMAKE_OPTIONS=no-dependencies

export PAROC_CXX=@CXX@

CXX=@top_srcdir@/parser/parocc
PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp 

AM_CXXFLAGS=-cxxmain  $(PAROC_FLAGS)

%.stub.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) -I../lib -c $<

lib_LIBRARIES = libparoc_tcmodel.a 
inst_HEADERS=modelgene.h model.h 
model_DATA=probobj.ph 

instdir=@includedir@
modeldir=@includedir@

libparoc_tcmodel_a_SOURCES=model.cc modelgene.cc probobj.cc 
libparoc_tcmodel_a_LIBADD=probobj.stub.o

EXTRA_DIST= probobj.ph

CLEANFILES=


