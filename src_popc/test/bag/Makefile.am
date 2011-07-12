AUTOMAKE_OPTIONS=no-dependencies

export PAROC_CXX=@CXX@

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp 

AM_CXXFLAGS=$(PAROC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib/.libs

%.stub.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

bag_PROGRAMS=bag.main bag.obj
bag_SCRIPTS=test_script

bag_main_SOURCES=bag.cc  
bag_main_LDADD=
bag_main_LDFLAGS=

bag_obj_SOURCES=bag.cc  
bag_obj_LDADD=
bag_obj_CPPFLAGS=
bag_obj_LDFLAGS=-object

bagdir=@prefix@/test/bag
EXTRA_DIST=test_script

