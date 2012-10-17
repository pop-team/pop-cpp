AUTOMAKE_OPTIONS=no-dependencies

CXX=mpic++

bin_PROGRAMS = popc_accept_broker popc_test_accept_broker
bindir = @prefix@/broker

popc_accept_broker_SOURCES = popc_accept_broker.cpp
popc_accept_broker_CCFLAGS = -I../include
popc_accept_broker_CXXFLAGS = -I../include

popc_test_accept_broker_SOURCES = popc_test_accept_broker.cpp
popc_test_accept_broker_CCFLAGS = -I../include
popc_test_accept_broker_CXXFLAGS = -I../include