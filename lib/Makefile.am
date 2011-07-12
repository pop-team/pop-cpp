AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/parocc

PAROC_FLAGS=-parocdir=@top_srcdir@ -parocpp=@top_srcdir@/parser/parocpp -cxx=@CXX@ -D_PLUGINDIR=\"$(libdir)/plugins\" -D_PAROC_RUNTIME_

if LINUX
AM_CXXFLAGS= -D_LINUX $(PAROC_FLAGS)
else
AM_CXXFLAGS= $(PAROC_FLAGS)
endif

paroc_infmain.%.o: paroc_infmain.%.cc
	$(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -DPIC -fPIC -c $< -o $@
paroc_objmain.%.o: paroc_objmain.%.cc
	$(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -DPIC -fPIC -c $< -o $@

%.ph.stub_client.o : %.ph
	$(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -parclass-nobroker -c $< -o $@

%.ph.stub.o : %.ph
	$(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

%.ph.stub_client.lo : %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -parclass-nobroker -c $< -o $@

%.ph.stub.lo : %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -c $< -o $@

lib_LTLIBRARIES = libparoc_common.la  libparoc_service_common.la
#lib_LTLIBRARIES = libparoc_plugin.la

bin_PROGRAMS= testplugin alloctest combox_client combox_server

libparoc_common_la_SOURCES=paroc_system.cc mutex.cc thread.cc string.cc od.cc event.cc paroc_buffer.cc buffer_utils.cc paroc_combox.cc  \
	broker.cc broker_receive.cc broker_serve.cc object.cc interface.cc timer.cc accesspoint.cc memspool.cc \
	utils.cc debug.cc exception.cc benchmark.cc paroc_combox_factory.cc \
	paroc_combox.cc paroc_combox_socket.cc paroc_buffer_xdr.cc \
	paroc_buffer_factory.cc paroc_buffer_factory_finder.cc paroc_buffer_xdr_factory.cc\
	paroc_buffer_raw.cc paroc_buffer_raw_factory.cc
libparoc_common_la_LIBADD=paroc_service_base.ph.stub_client.lo codemgr.ph.stub_client.lo \
remotelog.ph.stub_client.lo objectmonitor.ph.stub_client.lo appservice.ph.stub_client.lo jobmgr.ph.stub_client.lo
libparoc_common_la_LDFLAGS=-static
libparoc_common_la_CPPFLAGS=

libparoc_service_common_la_SOURCES=paroc_service_base.cc jobmgr.cc codemgr.cc remotelog.cc objectmonitor.cc appservice.cc
libparoc_service_common_la_LIBADD=paroc_service_base.ph.stub.lo jobmgr.ph.stub.lo codemgr.ph.stub.lo \
remotelog.ph.stub.lo  objectmonitor.ph.stub.lo appservice.ph.stub.lo 
libparoc_service_common_la_LDFLAGS=-static -version-info 2:3:0

main_DATA= paroc_objmain.std.o paroc_infmain.std.o
maindir=@libdir@


#paroc_objmain_std.o: paroc_objmain_std.cc
#	$(CXX) -cxxmain $(PAROC_FLAGS) $(CXXFLAGS) -DPIC -fPIC -c $< -o $@

testplugin_SOURCES=testplugin.cc 
testplugin_LDFLAGS=-paroc-nolib -L./ -lparoc_common 
testplugin_LDADD=paroc_infmain.std.o
testplugin_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC


alloctest_SOURCES=alloctest.cc 
alloctest_LDFLAGS=-paroc-nolib -L./ -lparoc_service_common -lparoc_common
alloctest_LDADD=paroc_infmain.std.o
alloctest_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC

combox_client_SOURCES=combox_client.cc 
combox_client_LDFLAGS=-paroc-nolib -L./ -lparoc_common 
combox_client_LDADD=paroc_infmain.std.o
combox_client_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC

combox_server_SOURCES=combox_server.cc 
combox_server_LDFLAGS=-paroc-nolib -L./ -lparoc_common 
combox_server_LDADD=paroc_infmain.std.o
combox_server_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC



#libparoc_plugin_la_SOURCES=common.cc mutex.cc string.cc od.cc event.cc combox.cc comset.cc \
#	interface.cc timer.cc accesspoint.cc memspool.cc \
#	utils.cc debug.cc exception.cc \
#	paroc_protocol_factory_finder.cc paroc_protocol_factory.cc \
#	paroc_protocol_socket_factory.cc paroc_combox.cc paroc_combox_socket.cc paroc_comset_socket.cc\
#	paroc_buffer.cc paroc_buffer_factory.cc paroc_buffer_factory_finder.cc \
#        paroc_buffer_xdr.cc paroc_buffer_xdr_factory.cc\
#	paroc_buffer_raw.cc paroc_buffer_raw_factory.cc
#libparoc_plugin_la_LIBADD=paroc_service_base.ph.stub_client.lo jobmgr.ph.stub_client.lo codemgr.ph.stub_client.lo \
#remotelog.ph.stub_client.lo objectmonitor.ph.stub_client.lo appservice.ph.stub_client.lo
#libparoc_plugin_la_CPPFLAGS=




EXTRA_DIST=paroc_infmain.std.cc paroc_objmain.std.cc appservice.ph  codemgr.ph  jobmgr.ph  objectmonitor.ph  paroc_service_base.ph   remotelog.ph

inst_HEADERS=paroc_service_base.ph appservice.ph codemgr.ph remotelog.ph objectmonitor.ph jobmgr.ph
instdir=@includedir@

CLEANFILES=_paroc_*.cc _paroc_*.ph
