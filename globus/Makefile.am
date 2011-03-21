AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/popcc
POPC_FLAGS= -parocdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp -I@top_srcdir@/lib -cxx=@CXX@ -D_POPC_RUNTIME_

AM_CXXFLAGS=$(POPC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib -L@top_srcdir@/lib/.libs 


-include globus_header

GLOBUSCCFLAGS=-DPOPC_GLOBUS $(GLOBUS_CPPFLAGS)
GLOBUSLDFLAGS=$(GLOBUS_LDFLAGS) $(GLOBUS_PKG_LIBS)

%.stub_client.o: %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(POPC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(GLOBUSCCFLAGS) -parclass-nobroker -c $< -o $@

%.stub.o: %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(POPC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(GLOBUSCCFLAGS) -I../lib -c $< -o $@


%.stub_client.lo: %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(POPC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(GLOBUSCCFLAGS) -D__NO_POPC_BROKER -D__NO_POPC_SERVER -c $< -o $@

%.stub.lo: %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(POPC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(GLOBUSCCFLAGS) -I../lib -c $< -o $@


sbin_SCRIPTS=popc_setup_globus
script_DATA=SXXpopc_globus.in 

scriptdir=@sbindir@

globusexecservices_PROGRAMS= jobmgr_globus jobmgr_globus_launcher globusgram
globusexecservicesdir=@prefix@/services

jobmgr_globus_launcher_SOURCES=jobmgr_globus_launcher.cc
jobmgr_globus_launcher_CXXFLAGS=$(POPC_FLAGS) $(CXXFLAGS) $(GLOBUSCCFLAGS)
jobmgr_globus_launcher_LDADD=jobmgr_globus.stub_client.o -L. -L@top_srcdir@/lib -lparoc_service_common $(GLOBUSLDFLAGS)

globusgram_SOURCES= globusgram.cc
globusgram_CXXFLAGS=$(POPC_FLAGS) $(CXXFLAGS) $(GLOBUSCCFLAGS)
globusgram_LDADD=globusgram.stub.o -lparoc_service_common $(GLOBUSLDFLAGS)
globusgram_LDFLAGS=-object $(LDFLAGS) -L. -L@top_srcdir@/lib -L@top_srcdir@/lib/.libs


jobmgr_globus_SOURCES= jobmgr_globus.cc
jobmgr_globus_CXXFLAGS= $(POPC_FLAGS) $(CXXFLAGS) $(GLOBUSCCFLAGS)
jobmgr_globus_LDADD=jobmgr_globus.stub.o globusgram.stub_client.o -L. -L@top_srcdir@/lib -lparoc_service_common $(GLOBUSLDFLAGS)
jobmgr_globus_LDFLAGS=-object $(LDFLAGS) -L@top_srcdir@/lib -L@top_srcdir@/lib/.libs 


EXTRA_DIST=jobmgr_globus.ph globusgram.ph popc_setup_globus.in SXXpopc_globus.in 

CLEANFILES=_paroc_*.cc _paroc_*.ph
install-data-hook:
	@@sbindir@/popc_setup_globus -ask 
