AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp -cxx=@CXX@ -D_PAROC_RUNTIME_

AM_CXXFLAGS=$(PAROC_FLAGS)

lib_LTLIBRARIES = paroc_xdr-zlib.la 

paroc_xdr_zlib_la_SOURCES=paroc_buffer_xdr-zlib_factory.cc paroc_buffer_xdr-zlib.cc xdr-zlib.cc paroc_buffer_xdr-zlib_factory.h  paroc_buffer_xdr-zlib.h
paroc_xdr_zlib_la_LDFLAGS=-paroc-nolib -module -shared  -avoid-version -lz


libdir=@libdir@/plugins


