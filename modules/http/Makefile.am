AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/parocc
PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp -cxx=@CXX@ -D_PAROC_RUNTIME_

AM_CXXFLAGS=$(PAROC_FLAGS)


lib_LTLIBRARIES = paroc_combox_http.la 
paroc_combox_http_la_SOURCES=paroc_combox_http.cc paroc_combox_http.h 
paroc_combox_http_la_LDFLAGS=-module -shared -avoid-version -lz -L@top_srcdir@/lib
libdir=@libdir@/plugins
EXTRA_DIST=servlet.tar.gz

