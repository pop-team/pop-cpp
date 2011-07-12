AUTOMAKE_OPTIONS=no-dependencies

export PAROC_CXX=@CXX@

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp 

AM_CXXFLAGS=$(PAROC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib/.libs

%.stub.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

pingpong_PROGRAMS=pingpong.main pingpong.obj
pingpong_SCRIPTS=test_script

pingpong_main_SOURCES=pingpong.ph pingpong.cc  
pingpong_main_LDADD=pingpong.stub.o
pingpong_main_LDFLAGS=

pingpong_obj_SOURCES=pingpong.ph pingpong.cc  
pingpong_obj_LDADD=pingpong.stub.o
pingpong_obj_LDFLAGS=-object

pingpongdir=@prefix@/test/pingpong
EXTRA_DIST=test_script Makefile.man

