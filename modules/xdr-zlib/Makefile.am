AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/popcc

POPC_FLAGS=-parocdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp -cxx=@CXX@ -D_POPC_RUNTIME_

AM_CXXFLAGS=$(POPC_FLAGS)

lib_LTLIBRARIES = paroc_xdr-zlib.la 

paroc_xdr_zlib_la_SOURCES=paroc_buffer_xdr-zlib_factory.cc paroc_buffer_xdr-zlib.cc xdr-zlib.cc paroc_buffer_xdr-zlib_factory.h  paroc_buffer_xdr-zlib.h
paroc_xdr_zlib_la_LDFLAGS=-paroc-nolib -module -shared  -avoid-version -lz


libdir=@libdir@/plugins


