AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/popcc

POPC_FLAGS=-parocdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp -cxx=@CXX@ -D_PLUGINDIR=\"$(libdir)/plugins\" -D_POPC_RUNTIME_

if LINUX
AM_CXXFLAGS= -D_LINUX $(POPC_FLAGS)
else
AM_CXXFLAGS= $(POPC_FLAGS)
endif

paroc_objmain.%.o: paroc_objmain.%.cc
	$(CXX) -cxxmain -cpp="mpicxx -E" $(POPC_FLAGS) $(CXXFLAGS) -DPIC -fPIC -c $< -o $@

inst_HEADERS=popc_mpi.h
instdir=@includedir@

mpi_DATA= paroc_objmain.mpi.o 
mpidir=@libdir@

EXTRA_DIST=paroc_objmain.mpi.cc 

CLEANFILES=_paroc_*.cc _paroc_*.ph *.o
