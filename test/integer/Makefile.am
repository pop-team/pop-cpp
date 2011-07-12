AUTOMAKE_OPTIONS=no-dependencies

export PAROC_CXX=@CXX@

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp 

AM_CXXFLAGS=$(PAROC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib/.libs

%.stub.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

integer_PROGRAMS=integer.main integer.obj
integer_SCRIPTS=test_script

integer_main_SOURCES=integer.ph integer.cc main.cc 
integer_main_LDADD=integer.stub.o
integer_main_LDFLAGS=

integer_obj_SOURCES=integer.ph integer.cc
integer_obj_LDADD=integer.stub.o
integer_obj_LDFLAGS=-object

integerdir=@prefix@/test/integer
EXTRA_DIST=test_script

