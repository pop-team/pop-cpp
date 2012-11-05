AUTOMAKE_OPTIONS=no-dependencies

#CXX=mpic++
CXX=mpiFCCpx

bin_PROGRAMS = popc_mpi_communicator openmpi_check_support
bindir = @prefix@/mpi

popc_mpi_communicator_SOURCES = popc_mpi_communicator.cpp
popc_mpi_communicator_CCFLAGS = -I../include
popc_mpi_communicator_CXXFLAGS = -I../include
popc_mpi_communicator_LDFLAGS=-L@top_srcdir@/lib/.libs -lparoc_common

openmpi_check_support_SOURCES = openmpi_check_support.cpp
