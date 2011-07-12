AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/parocc
PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp -cxx=@CXX@ -D_PAROC_RUNTIME_

AM_CXXFLAGS=$(PAROC_FLAGS)


lib_LTLIBRARIES = paroc_buffer_xml.la 

paroc_buffer_xml_la_SOURCES=paroc_buffer_xml_factory.cc paroc_buffer_xml.cc xml.cc paroc_buffer_xml.h paroc_buffer_xml_factory.h
paroc_buffer_xml_la_LDFLAGS=-module -shared -avoid-version -lz -L@top_srcdir@/lib -L/home/nicolas/xerces-c-src_2_6_0/lib -lxerces-c -lc
libdir=@libdir@/plugins

# paroc_buffer.cc paroc_buffer_factory.cc 
