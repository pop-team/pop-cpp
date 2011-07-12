AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/parocc
PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp -cxx=@CXX@ -D_PAROC_RUNTIME_

AM_CXXFLAGS=$(PAROC_FLAGS)


lib_LTLIBRARIES = paroc_raw-zlib.la 

paroc_raw_zlib_la_SOURCES=paroc_buffer_raw-zlib_factory.cc paroc_buffer_raw-zlib.cc raw-zlib.cc paroc_buffer_raw-zlib.h paroc_buffer_raw-zlib_factory.h
paroc_raw_zlib_la_LDFLAGS=-paroc-nolib -module -shared -avoid-version -lz 
libdir=@libdir@/plugins

# paroc_buffer.cc paroc_buffer_factory.cc 
