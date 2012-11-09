AUTOMAKE_OPTIONS=no-dependencies

#CXX=mpicxx
#CXX=mpiFCCpx
CXX=mpicxx
#CXX=mpiicpc


bin_PROGRAMS = popc_mpi_interconnector openmpi_check_support
bindir = @prefix@/mpi

popc_mpi_interconnector_SOURCES = popc_mpi_interconnector.cpp
popc_mpi_interconnector_CCFLAGS = -I../include
popc_mpi_interconnector_CXXFLAGS = -I../include
popc_mpi_interconnector_LDFLAGS=-L@top_srcdir@/lib/.libs -lparoc_common

openmpi_check_support_SOURCES = openmpi_check_support.cpp
