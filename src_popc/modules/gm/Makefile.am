AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/parocc
PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp -cxx=@CXX@

#AM_CXXFLAGS=$(PAROC_FLAGS) -I/home/nicolas/gm-2.1.9_Linux/binary/include
AM_CXXFLAGS=$(PAROC_FLAGS) -I/usr/local/gm/include

lib_LTLIBRARIES = paroc_combox_gm.la 

paroc_combox_gm_la_SOURCES=paroc_combox_gm.cc paroc_protocol_gm_factory.cc gm.cc paroc_combox_gm.h paroc_protocol_gm_factory.h\
			 paroc_comset_gm.cc paroc_comset_gm.h

paroc_combox_gm_la_LDFLAGS=-module -shared -avoid-version -lz -L@top_srcdir@/lib -L/usr/local/gm/lib -lgm
libdir=@libdir@/plugins

