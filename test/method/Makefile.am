AUTOMAKE_OPTIONS=no-dependencies

export PAROC_CXX=@CXX@

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp 

AM_CXXFLAGS=$(PAROC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib/.libs

%.stub.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

method_PROGRAMS=method.main method.obj
method_SCRIPTS=test_script

method_main_SOURCES=method.ph method.cc  
method_main_LDADD=method.stub.o
method_main_LDFLAGS=

method_obj_SOURCES=method.ph method.cc  
method_obj_LDADD=method.stub.o
method_obj_LDFLAGS=-object

methoddir=@prefix@/test/method
EXTRA_DIST=test_script

