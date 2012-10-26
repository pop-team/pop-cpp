AUTOMAKE_OPTIONS=no-dependencies

CXX=mpic++

bin_PROGRAMS = popc_mpi_communicator 
bindir = @prefix@/mpi

popc_mpi_communicator_SOURCES = popc_mpi_communicator.cpp
popc_mpi_communicator_CCFLAGS = -I../include
popc_mpi_communicator_CXXFLAGS = -I../include
popc_mpi_communicator_LDFLAGS=-L@top_srcdir@/lib/.libs -lparoc_common
