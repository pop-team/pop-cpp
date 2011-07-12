AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/parocc
PAROC_FLAGS= -parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp -I@top_srcdir@/lib -cxx=@CXX@ -D_PAROC_RUNTIME_

AM_CXXFLAGS=$(PAROC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib -L@top_srcdir@/lib/.libs 


if GLOBUS

-include globus_header

GLOBUSCCFLAGS=-DPAROC_GLOBUS $(GLOBUS_CPPFLAGS)
GLOBUSLDFLAGS=$(GLOBUS_LDFLAGS) $(GLOBUS_PKG_LIBS)

%globus.stub_client.o: %globus.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(GLOBUSCCFLAGS) -D__NO_PAROC_BROKER -D__NO_PAROC_SERVER -c $< -o $@

%globus.stub.o: %globus.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(PAROC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(GLOBUSCCFLAGS) -I../lib -c $< -o $@


%globus.stub_client.lo: %globus.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(PAROC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(GLOBUSCCFLAGS) -D__NO_PAROC_BROKER -D__NO_PAROC_SERVER -c $< -o $@

%globus.stub.lo: %globus.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(PAROC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) $(GLOBUSCCFLAGS) -I../lib -c $< -o $@

endif

%.stub_client.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) -I../lib -D__NO_PAROC_BROKER -D__NO_PAROC_SERVER -c $< -o $@

%.stub.o : %.ph
	$(CXX) $(PAROC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) -I../lib -c $< -o $@

%.ph.stub_client.lo : %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -D__NO_PAROC_BROKER -D__NO_PAROC_SERVER -c $< -o $@

%.ph.stub.lo : %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

execservices_PROGRAMS=jobmgr appservice localservice_launcher jobmgr_launcher 
execservices_SCRIPTS=webrun parojob.pbs
execservicesdir=@prefix@/services

conf_DATA=jobmgr.conf.in 
confdir=@prefix@/etc

bin_PROGRAMS= jobmgrpublish jobmgrquery dumpjobmgr benchmarktest

jobmgr_SOURCES=jobmgr_obj.cc
jobmgr_LDADD=-lparoc_service_common
jobmgr_LDFLAGS=-object

appservice_SOURCES=appservice_obj.cc
appservice_LDADD=-lparoc_service_common
appservice_LDFLAGS=-object

localservice_launcher_SOURCES=localservice_launcher.cc

jobmgr_launcher_SOURCES=jobmgr_launcher.cc


jobmgrpublish_SOURCES=jobmgrpublish.cc
jobmgrpublish_LDFLAGS=-L@top_srcdir@/lib/.libs
jobmgrpublish_DEPENDENCIES=

jobmgrquery_SOURCES=jobmgrquery.cc
#jobmgrquery_LDFLAGS=-L@top_srcdir@/lib/.libs
jobmgrquery_DEPENDENCIES=

dumpjobmgr_SOURCES=dumpjobmgr.cc
#dumpjobmgr_LDFLAGS=-L@top_srcdir@/lib/.libs
dumpjobmgr_DEPENDENCIES=

benchmarktest_SOURCES=test_benchmark.cc 
#benchmarktest_LDFLAGS=-L@top_srcdir@/lib/.libs

#proxy_SOURCES=proxy_obj.cc
#proxy_LDFLAGS=-object -lparoc_service_common
#proxy_LDADD=-lparoc_service_common
#proxy_CXXFLAGS=-object $(PAROC_FLAGS)

#launchproxy_SOURCES=proxymain.cc
#launchproxy_LDFLAGS=
#launchproxy_CXXFLAGS=$(PAROC_FLAGS)


CLEANFILES=_paroc_*.cc _paroc_*.ph

if GLOBUS

globusexecservices_PROGRAMS= localservice_launcher.globus jobmgr_launcher.globus appservice.globus jobmgr.globus
globuslib_LTLIBRARIES=libparoc_globus.la

globusexecservicesdir=@prefix@/services
globuslibdir=@libdir@

libparoc_globus_la_SOURCES=jobmgr_globus.cc appservice_globus.cc
libparoc_globus_la_LIBADD= appservice_globus.stub.lo jobmgr_globus.stub.lo
libparoc_globus_la_CXXFLAGS=$(PAROC_FLAGS) $(CXXFLAGS) $(GLOBUSCCFLAGS)
libparoc_globus_la_DEPENDENCIES=jobmgr_globus.stub.lo appservice_globus.stub.lo

localservice_launcher_globus_SOURCES=localservice_launcher.cc
localservice_launcher_globus_CXXFLAGS=$(PAROC_FLAGS) $(CXXFLAGS) $(GLOBUSCCFLAGS)
localservice_launcher_globus_LDADD=-L. -L../lib -lparoc_globus -lparoc_service_common $(GLOBUSLDFLAGS)
localservice_launcher_globus_DEPENDENCIES=libparoc_globus.la

jobmgr_launcher_globus_SOURCES=jobmgr_launcher.cc
jobmgr_launcher_globus_CXXFLAGS=$(PAROC_FLAGS) $(CXXFLAGS) $(GLOBUSCCFLAGS)
jobmgr_launcher_globus_LDADD=-L. -L../lib -lparoc_globus -lparoc_service_common $(GLOBUSLDFLAGS)
jobmgr_launcher_globus_DEPENDENCIES=libparoc_globus.la

appservice_globus_SOURCES=  appservice_globus_obj.cc
appservice_globus_CXXFLAGS=$(PAROC_FLAGS) $(CXXFLAGS) $(GLOBUSCCFLAGS)
appservice_globus_LDADD=-L. -L../lib  -lparoc_globus -lparoc_service_common $(GLOBUSLDFLAGS)
appservice_globus_LDFLAGS=-object $(LDFLAGS)
appservice_globus_DEPENDENCIES=libparoc_globus.la

jobmgr_globus_SOURCES= jobmgr_globus_obj.cc
jobmgr_globus_CXXFLAGS= $(PAROC_FLAGS) $(CXXFLAGS) $(GLOBUSCCFLAGS)
jobmgr_globus_LDADD=-L. -L../lib -lparoc_globus  -lparoc_service_common $(GLOBUSLDFLAGS)
jobmgr_globus_LDFLAGS=-object $(LDFLAGS) 
jobmgr_globus_DEPENDENCIES=libparoc_globus.la
endif

EXTRA_DIST=jobmgr.conf.in appservice_globus.ph  jobmgr_globus.ph  webrun parojob.pbs
