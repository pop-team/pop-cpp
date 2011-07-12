AUTOMAKE_OPTIONS=no-dependencies

export POPC_CXX=@CXX@

CXX=@top_srcdir@/parser/popcc

POPC_FLAGS=-parocdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp 

AM_CXXFLAGS=$(POPC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib/.libs

%.stub.o : %.ph
	$(CXX) $(POPC_FLAGS) $(CXXFLAGS) -c $< -o $@

tree_PROGRAMS=tree.main tree.obj
tree_SCRIPTS=test_script

tree_main_SOURCES=tree.ph tree.cc  
tree_main_LDADD=tree.stub.o
tree_main_LDFLAGS=-L@top_srcdir@/lib/.libs

tree_obj_SOURCES=tree.ph tree.cc  
tree_obj_LDADD=tree.stub.o
tree_obj_LDFLAGS=-object -L@top_srcdir@/lib/.libs

treedir=@prefix@/test/tree
EXTRA_DIST=test_script

obj.map:
	./tree.obj -listlong > obj.map
run: obj.map
	popcrun obj.map ./tree.main 2 3
