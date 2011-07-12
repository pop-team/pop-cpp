AUTOMAKE_OPTIONS=no-dependencies

export PAROC_CXX=@CXX@

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp 

AM_CXXFLAGS=$(PAROC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib/.libs

%.stub.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

matrix_PROGRAMS=matrix.main matrix.obj
matrix_SCRIPTS=test_script

matrix_main_SOURCES=matrix.ph matrix.cc main.cc
matrix_main_LDADD=matrix.stub.o
matrix_main_LDFLAGS=

matrix_obj_SOURCES=matrix.ph matrix.cc matrix_obj.cc  
matrix_obj_LDADD=matrix.stub.o
matrix_obj_LDFLAGS=-object

matrixdir=@prefix@/test/matrix
EXTRA_DIST=test_script

