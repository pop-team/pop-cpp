#Code added by clementval begins with #Added by clementval, ends with #End of add
#Code modified by clementval begins with #Modified by clementval, ends with #End of modification
AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/popcc
POPC_FLAGS=-popcpp-compilation -no-implicit-pack -popcdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp -I@top_srcdir@/lib -cxx=@CXX@ -D_POPC_RUNTIME_

AM_CXXFLAGS=$(POPC_FLAGS)
AM_LDFLAGS=-L@top_srcdir@/lib -L@top_srcdir@/lib/.libs 

%.stub_client.o : %.ph
	$(CXX) $(POPC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) -I../lib -parclass-nobroker -c $< -o $@

%.stub.o : %.ph
	$(CXX) $(POPC_FLAGS) $(CXXFLAGS) $(CPPFLAGS) -I../lib -c $< -o $@

%.ph.stub_client.lo : %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) -cxxmain $(POPC_FLAGS) $(CXXFLAGS) -parclass-nobroker -c $< -o $@

%.ph.stub.lo : %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) -cxxmain $(POPC_FLAGS) $(CXXFLAGS) -c $< -o $@

#Standard version
if STANDARDSUPPORT
execservices_PROGRAMS=popc_search_node jobmgr appservice localservice_launcher jobmgr_launcher popfilemanager
endif


#Virtual version
if VIRTSUPPORT
execservices_PROGRAMS=popc_search_node virtual_popc_search_node jobmgr virtual_jobmgr virtual_jobmgr appservice \
   localservice_launcher jobmgr_launcher popcloner
endif

#Virtual Secure version
if VIRTSECURESUPPORT
execservices_PROGRAMS=popc_search_node virtual_popc_search_node jobmgr virtual_jobmgr virtual_jobmgr appservice \
   localservice_launcher jobmgr_launcher popcloner virtual_secure_popc_search_node popc_security_manager secure_jobmgr \
   secure_popc_search_node virtual_secure_jobmgr virtual_popc_security_manager
endif

#Secure version
if SECURESUPPORT
execservices_PROGRAMS=popc_search_node jobmgr secure_jobmgr appservice \
   localservice_launcher jobmgr_launcher popc_security_manager secure_popc_search_node 
endif

execservices_SCRIPTS= popcobjrun popcobjrun.pbs popcobjrun.lsf popcobjrun.sge popcobjrun.smscg
execservicesdir=@prefix@/services

conf_DATA=jobmgr.conf.in 
confdir=@prefix@/etc

bin_PROGRAMS= jobmgrpublish jobmgrquery dumpjobmgr benchmarktest
bin_SCRIPTS=popcjob.pbs popcjob.lsf popcjob.sge

popc_search_node_SOURCES=popc_search_node_obj.cc
popc_search_node_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
popc_search_node_LDFLAGS=-object

jobmgr_SOURCES=jobmgr_obj.cc
jobmgr_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
jobmgr_LDFLAGS=-object

popfilemanager_SOURCES=popfilemanager_obj.cc
popfilemanager_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
popfilemanager_LDFLAGS=-object

#
# ViSaG : clementval
# Add conditional compiling libraries for the different version of POP-C++
#


#VIRTUAL SECURE VERSION
if VIRTSECURESUPPORT
virtual_popc_search_node_SOURCES=virtual_popc_search_node_obj.cc
virtual_popc_search_node_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
virtual_popc_search_node_LDFLAGS=-object

virtual_secure_popc_search_node_SOURCES=virtual_secure_popc_search_node_obj.cc
virtual_secure_popc_search_node_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
virtual_secure_popc_search_node_LDFLAGS=-object

virtual_jobmgr_SOURCES=virtual_jobmgr_obj.cc
virtual_jobmgr_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
virtual_jobmgr_LDFLAGS=-object

virtual_secure_jobmgr_SOURCES=virtual_secure_jobmgr_obj.cc
virtual_secure_jobmgr_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
virtual_secure_jobmgr_LDFLAGS=-object

popcloner_SOURCES=popcloner_obj.cc
popcloner_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
popcloner_LDFLAGS=-object

popc_security_manager_SOURCES=popc_security_manager_obj.cc
popc_security_manager_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
popc_security_manager_LDFLAGS=-object

virtual_popc_security_manager_SOURCES=virtual_popc_security_manager_obj.cc
virtual_popc_security_manager_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
virtual_popc_security_manager_LDFLAGS=-object

secure_jobmgr_SOURCES=secure_jobmgr_obj.cc
secure_jobmgr_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
secure_jobmgr_LDFLAGS=-object

secure_popc_search_node_SOURCES=secure_popc_search_node_obj.cc
secure_popc_search_node_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
secure_popc_search_node_LDFLAGS=-object
endif

#VIRTUAL VERSION
if VIRTSUPPORT
virtual_popc_search_node_SOURCES=virtual_popc_search_node_obj.cc
virtual_popc_search_node_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
virtual_popc_search_node_LDFLAGS=-object

virtual_jobmgr_SOURCES=virtual_jobmgr_obj.cc
virtual_jobmgr_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
virtual_jobmgr_LDFLAGS=-object

popcloner_SOURCES=popcloner_obj.cc
popcloner_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
popcloner_LDFLAGS=-object
endif

#SECURE VERSION
if SECURESUPPORT
popc_security_manager_SOURCES=popc_security_manager_obj.cc
popc_security_manager_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
popc_security_manager_LDFLAGS=-object

secure_jobmgr_SOURCES=secure_jobmgr_obj.cc
secure_jobmgr_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
secure_jobmgr_LDFLAGS=-object

secure_popc_search_node_SOURCES=secure_popc_search_node_obj.cc
secure_popc_search_node_LDADD=-L@top_srcdir@/lib/.libs -lparoc_service_common
secure_popc_search_node_LDFLAGS=-object
endif

appservice_SOURCES=appservice_obj.cc
appservice_LDADD=
appservice_LDFLAGS=-object -L@top_srcdir@/lib/.libs -lparoc_service_common

localservice_launcher_SOURCES=localservice_launcher.cc
localservice_launcher_LDFLAGS=-L@top_srcdir@/lib/.libs -lparoc_service_common

jobmgr_launcher_SOURCES=jobmgr_launcher.cc
jobmgr_launcher_LDFLAGS=-L@top_srcdir@/lib/.libs -lparoc_service_common

jobmgrpublish_SOURCES=jobmgrpublish.cc
jobmgrpublish_LDFLAGS=-L@top_srcdir@/lib/.libs -lparoc_service_common
jobmgrpublish_DEPENDENCIES=

jobmgrquery_SOURCES=jobmgrquery.cc
jobmgrquery_LDFLAGS=-L@top_srcdir@/lib/.libs -lparoc_service_common
jobmgrquery_DEPENDENCIES=

dumpjobmgr_SOURCES=dumpjobmgr.cc
dumpjobmgr_LDFLAGS=-L@top_srcdir@/lib/.libs -lparoc_service_common
dumpjobmgr_DEPENDENCIES=

benchmarktest_SOURCES=test_benchmark.cc 


CLEANFILES=_paroc_*.cc _paroc_*.ph


install-data-hook:
	@if [ ! -f @prefix@/etc/popc-runtime-env.sh ]; then cp @prefix@/etc/popc-runtime-env.in @prefix@/etc/popc-runtime-env.sh; fi
	@ln -sf popcc @prefix@/bin/parocc
	@ln -sf popcrun @prefix@/bin/parocrun
	@ln -sf popcobjrun @prefix@/services/webrun
	@ln -sf popc-user-env.csh @prefix@/bin/paroc-user-env.csh
	@ln -sf popc-user-env.sh @prefix@/bin/paroc-user-env.sh
	@ln -sf SXXpopc @prefix@/sbin/SXXparoc
	@@sbindir@/popc_setup -ask

EXTRA_DIST=jobmgr.conf.in  popcobjrun.in
