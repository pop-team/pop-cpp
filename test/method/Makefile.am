AUTOMAKE_OPTIONS=no-dependencies

export POPC_CXX=@CXX@

CXX=@top_srcdir@/parser/popcc

POPC_FLAGS=-parocdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp 

AM_CXXFLAGS=$(POPC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib/.libs

%.stub.o : %.ph
	$(CXX) $(POPC_FLAGS) $(CXXFLAGS) -c $< -o $@

method_PROGRAMS=method.main method.obj
method_SCRIPTS=test_script

method_main_SOURCES=method.ph method.cc  
method_main_LDADD=method.stub.o
method_main_LDFLAGS=-L@top_srcdir@/lib/.libs

method_obj_SOURCES=method.ph method.cc  
method_obj_LDADD=method.stub.o
method_obj_LDFLAGS=-object -L@top_srcdir@/lib/.libs

methoddir=@prefix@/test/method
EXTRA_DIST=test_script

obj.map:
	./method.obj -listlong > obj.map
run: obj.map
	popcrun obj.map ./method.main 
