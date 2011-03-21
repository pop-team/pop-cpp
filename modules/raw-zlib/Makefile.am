AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/popcc
POPC_FLAGS=-parocdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp -cxx=@CXX@ -D_POPC_RUNTIME_

AM_CXXFLAGS=$(POPC_FLAGS)


lib_LTLIBRARIES = paroc_raw-zlib.la 

paroc_raw_zlib_la_SOURCES=paroc_buffer_raw-zlib_factory.cc paroc_buffer_raw-zlib.cc raw-zlib.cc paroc_buffer_raw-zlib.h paroc_buffer_raw-zlib_factory.h
paroc_raw_zlib_la_LDFLAGS=-paroc-nolib -module -shared -avoid-version -lz 
libdir=@libdir@/plugins

# paroc_buffer.cc paroc_buffer_factory.cc 
