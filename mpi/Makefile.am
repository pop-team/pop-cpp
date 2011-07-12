AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp -cxx=@CXX@ -D_PLUGINDIR=\"$(libdir)/plugins\" -D_PAROC_RUNTIME_

if LINUX
AM_CXXFLAGS= -D_LINUX $(PAROC_FLAGS)
else
AM_CXXFLAGS= $(PAROC_FLAGS)
endif

paroc_objmain.%.o: paroc_objmain.%.cc
	$(CXX) -cxxmain -cxx=mpicxx $(PAROC_FLAGS) $(CXXFLAGS) -DPIC -fPIC -c $< -o $@

inst_HEADERS=popc_mpi.h
instdir=@includedir@

mpi_DATA= paroc_objmain.mpi.o 
mpidir=@libdir@

EXTRA_DIST=paroc_objmain.mpi.cc 

CLEANFILES=_paroc_*.cc _paroc_*.ph *.o
