AUTOMAKE_OPTIONS=no-dependencies

export PAROC_CXX=@CXX@

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp 

AM_CXXFLAGS=$(PAROC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib/.libs

%.stub.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

tree_PROGRAMS=tree.main tree.obj
tree_SCRIPTS=test_script

tree_main_SOURCES=tree.ph tree.cc  
tree_main_LDADD=tree.stub.o
tree_main_LDFLAGS=

tree_obj_SOURCES=tree.ph tree.cc  
tree_obj_LDADD=tree.stub.o
tree_obj_LDFLAGS=-object

treedir=@prefix@/test/tree
EXTRA_DIST=test_script

