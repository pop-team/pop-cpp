AUTOMAKE_OPTIONS=no-dependencies

CXX=@top_srcdir@/parser/popcc

POPC_FLAGS=-popcpp-compilation -no-implicit-pack -popcdir=@top_srcdir@ -popcpp=@top_srcdir@/parser/popcpp -cxx=@CXX@ -D_PLUGINDIR=\"$(libdir)/plugins\" -D_POPC_RUNTIME_ 


#ADD VIX and LIBVIRT flags
if LINUX
AM_CXXFLAGS=-D_LINUX $(POPC_FLAGS) $(LIBVIRT_CFLAGS) $(LIBVIRT_LIBS) $(VIX_CFLAGS) $(VIX_LIBS)
else
AM_CXXFLAGS=$(POPC_FLAGS) $(LIBVIRT_CFLAGS) $(LIBVIRT_LIBS)
endif






paroc_infmain.%.o: paroc_infmain.%.cc
	$(CXX) -cxxmain $(POPC_FLAGS) $(CXXFLAGS) -DPIC -fPIC -c $< -o $@
paroc_objmain.%.o: paroc_objmain.%.cc
	$(CXX) -cxxmain $(POPC_FLAGS) $(CXXFLAGS) -DPIC -fPIC -c $< -o $@

%.ph.stub_client.o : %.ph
	$(CXX) -cxxmain $(POPC_FLAGS) $(CXXFLAGS) -parclass-nobroker -c $< -o $@

%.ph.stub.o : %.ph
	$(CXX) -cxxmain $(POPC_FLAGS) $(CXXFLAGS) -c $< -o $@

%.ph.stub_client.lo : %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) -cxxmain $(POPC_FLAGS) $(CXXFLAGS) -parclass-nobroker -c $< -o $@

%.ph.stub.lo : %.ph
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) -cxxmain $(POPC_FLAGS) $(CXXFLAGS) -c $< -o $@

lib_LTLIBRARIES = libparoc_common.la  libparoc_service_common.la

bin_PROGRAMS= testplugin alloctest combox_client combox_server combox_test popcipher

#compile popcipher if the version include virtualization
BUILT_SOURCES = generate.foo



##
# ViSaG : clementval
# Custom target - Generate new sources file with a key for virtual configuration file encryption
##
generate.foo: 
	../scripts/aes_generate


#Virtual version
if VIRTSUPPORT
libparoc_common_la_SOURCES=system.cc mutex.cc thread.cc string.cc od.cc event.cc buffer.cc buffer_utils.cc combox.cc  \
	broker.cc broker_receive.cc broker_serve.cc object.cc interface.cc allocobj.cc timer.cc accesspoint.cc memspool.cc \
	utils.cc debug.cc exception.cc benchmark.cc combox_factory.cc\
	combox.cc combox_socket.cc buffer_xdr.cc \
	buffer_factory.cc buffer_factory_finder.cc buffer_xdr_factory.cc\
	buffer_raw.cc buffer_raw_factory.cc broker_factory.cc\
	response.cc request.cc explorationList.cc popc_search_node_info.cc popwayback.cc popvm.cc\
	WrapperFactory.cc ESXWrapper.cc POPWrapper.cc nodethread.cc rijndael.cc

libparoc_common_la_LIBADD=paroc_service_base.ph.stub_client.lo virtual_popc_search_node.ph.stub_client.lo \
   popc_search_node.ph.stub_client.lo codemgr.ph.stub_client.lo remotelog.ph.stub_client.lo objectmonitor.ph.stub_client.lo \
   appservice.ph.stub_client.lo batchmgr.ph.stub_client.lo popcloner.ph.stub_client.lo
endif

if SECURESUPPORT
libparoc_common_la_SOURCES=system.cc mutex.cc thread.cc string.cc od.cc event.cc buffer.cc buffer_utils.cc combox.cc  \
	broker.cc broker_receive.cc broker_serve.cc object.cc interface.cc allocobj.cc timer.cc accesspoint.cc memspool.cc \
	utils.cc debug.cc exception.cc benchmark.cc combox_factory.cc\
	combox.cc combox_socket.cc buffer_xdr.cc \
	buffer_factory.cc buffer_factory_finder.cc buffer_xdr_factory.cc\
	buffer_raw.cc buffer_raw_factory.cc broker_factory.cc \
	response.cc request.cc explorationList.cc popc_search_node_info.cc popwayback.cc popc_security_manager.cc nodethread.cc

libparoc_common_la_LIBADD=paroc_service_base.ph.stub_client.lo popc_security_manager.ph.stub_client.lo\
   popc_search_node.ph.stub_client.lo codemgr.ph.stub_client.lo remotelog.ph.stub_client.lo objectmonitor.ph.stub_client.lo \
   appservice.ph.stub_client.lo batchmgr.ph.stub_client.lo secure_popc_search_node.ph.stub_client.lo
endif

if VIRTSECURESUPPORT
libparoc_common_la_SOURCES=system.cc mutex.cc thread.cc string.cc od.cc event.cc buffer.cc buffer_utils.cc combox.cc  \
	broker.cc broker_receive.cc broker_serve.cc object.cc interface.cc allocobj.cc timer.cc accesspoint.cc memspool.cc \
	utils.cc debug.cc exception.cc benchmark.cc combox_factory.cc\
	combox.cc combox_socket.cc buffer_xdr.cc \
	buffer_factory.cc buffer_factory_finder.cc buffer_xdr_factory.cc\
	buffer_raw.cc buffer_raw_factory.cc broker_factory.cc\
	response.cc request.cc explorationList.cc popc_search_node_info.cc popwayback.cc popvm.cc\
	WrapperFactory.cc ESXWrapper.cc POPWrapper.cc nodethread.cc popc_security_manager.cc rijndael.cc

libparoc_common_la_LIBADD=paroc_service_base.ph.stub_client.lo popc_security_manager.ph.stub_client.lo\
   popc_search_node.ph.stub_client.lo codemgr.ph.stub_client.lo remotelog.ph.stub_client.lo objectmonitor.ph.stub_client.lo \
   appservice.ph.stub_client.lo batchmgr.ph.stub_client.lo
endif

if STANDARDSUPPORT
libparoc_common_la_SOURCES=system.cc mutex.cc thread.cc string.cc od.cc event.cc buffer.cc buffer_utils.cc combox.cc  \
	broker.cc broker_receive.cc broker_serve.cc object.cc interface.cc allocobj.cc timer.cc accesspoint.cc memspool.cc \
	utils.cc debug.cc exception.cc benchmark.cc combox_factory.cc \
	combox.cc combox_socket.cc buffer_xdr.cc \
	buffer_factory.cc buffer_factory_finder.cc buffer_xdr_factory.cc \
	buffer_raw.cc buffer_raw_factory.cc broker_factory.cc \
	response.cc request.cc explorationList.cc popc_search_node_info.cc popwayback.cc nodethread.cc popc_logger.cpp
	
libparoc_common_la_LIBADD=paroc_service_base.ph.stub_client.lo popc_search_node.ph.stub_client.lo \
   codemgr.ph.stub_client.lo remotelog.ph.stub_client.lo objectmonitor.ph.stub_client.lo appservice.ph.stub_client.lo \
   batchmgr.ph.stub_client.lo popfilemanager.ph.stub_client.lo
endif

libparoc_common_la_LDFLAGS=-static
libparoc_common_la_CPPFLAGS=

#
# DIFFERENCE BETWEEN Virtual, Secure and Standard version
#

#Virtual version
if VIRTSUPPORT
libparoc_service_common_la_SOURCES=service_base.cc jobmgr.cc  virtual_popc_search_node.cc popc_search_node.cc codemgr.cc \
   remotelog.cc objectmonitor.cc appservice.cc batchmgr.cc virtual_jobmgr.cc WrapperFactory.cc ESXWrapper.cc popcloner.cc

libparoc_service_common_la_LIBADD=paroc_service_base.ph.stub.lo jobmgr.ph.stub.lo virtual_popc_search_node.ph.stub.lo \
   popc_search_node.ph.stub.lo codemgr.ph.stub.lo virtual_jobmgr.ph.stub.lo remotelog.ph.stub.lo  objectmonitor.ph.stub.lo \
   appservice.ph.stub.lo batchmgr.ph.stub.lo popcloner.ph.stub.lo 
endif

#Secure version
if SECURESUPPORT
libparoc_service_common_la_SOURCES=service_base.cc jobmgr.cc popc_search_node.cc codemgr.cc \
   remotelog.cc objectmonitor.cc appservice.cc batchmgr.cc \
   secure_jobmgr.cc secure_popc_search_node.cc popc_security_manager.cc 

libparoc_service_common_la_LIBADD=paroc_service_base.ph.stub.lo jobmgr.ph.stub.lo \
   popc_search_node.ph.stub.lo codemgr.ph.stub.lo remotelog.ph.stub.lo  objectmonitor.ph.stub.lo \
   appservice.ph.stub.lo batchmgr.ph.stub.lo popc_security_manager.ph.stub.lo \
   secure_jobmgr.ph.stub.lo secure_popc_search_node.ph.stub.lo
endif

if VIRTSECURESUPPORT
libparoc_service_common_la_SOURCES=service_base.cc jobmgr.cc  virtual_popc_search_node.cc popc_search_node.cc codemgr.cc \
   remotelog.cc objectmonitor.cc appservice.cc batchmgr.cc virtual_jobmgr.cc WrapperFactory.cc ESXWrapper.cc popcloner.cc \
   virtual_secure_jobmgr.cc virtual_secure_popc_search_node.cc popc_security_manager.cc POPWrapper.cc \
   virtual_popc_security_manager.cc secure_jobmgr.cc secure_popc_search_node.cc

libparoc_service_common_la_LIBADD=paroc_service_base.ph.stub.lo jobmgr.ph.stub.lo virtual_popc_search_node.ph.stub.lo \
   popc_search_node.ph.stub.lo codemgr.ph.stub.lo virtual_jobmgr.ph.stub.lo remotelog.ph.stub.lo  objectmonitor.ph.stub.lo \
   appservice.ph.stub.lo batchmgr.ph.stub.lo popcloner.ph.stub.lo popc_security_manager.ph.stub.lo \
   virtual_popc_security_manager.ph.stub.lo virtual_secure_jobmgr.ph.stub.lo virtual_secure_popc_search_node.ph.stub.lo \
   secure_jobmgr.ph.stub.lo secure_popc_search_node.ph.stub.lo
endif

if STANDARDSUPPORT
libparoc_service_common_la_SOURCES=service_base.cc jobmgr.cc popc_search_node.cc codemgr.cc \
   remotelog.cc objectmonitor.cc appservice.cc batchmgr.cc popfilemanager.cc popc_logger.cpp

libparoc_service_common_la_LIBADD=paroc_service_base.ph.stub.lo jobmgr.ph.stub.lo \
   popc_search_node.ph.stub.lo codemgr.ph.stub.lo remotelog.ph.stub.lo  objectmonitor.ph.stub.lo \
   appservice.ph.stub.lo batchmgr.ph.stub.lo popfilemanager.ph.stub.lo 
endif

libparoc_service_common_la_LDFLAGS=-static -version-info 1:2:0

main_DATA= paroc_objmain.std.o paroc_infmain.std.o
maindir=@libdir@

testplugin_SOURCES=testplugin.cc 
testplugin_LDFLAGS=-paroc-nolib -L./.libs/ -lparoc_common
testplugin_LDADD=
testplugin_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC


alloctest_SOURCES=alloctest.cc 
alloctest_LDFLAGS=-paroc-nolib -L./.libs/ -lparoc_service_common -lparoc_common
#alloctest_LDADD=paroc_infmain.std.o
alloctest_LDADD=
alloctest_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC

combox_client_SOURCES=combox_client.cc 
combox_client_LDFLAGS=-paroc-nolib -L./.libs/ -lparoc_common 
#combox_client_LDADD=paroc_infmain.std.o
combox_client_LDADD=
combox_client_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC

combox_server_SOURCES=combox_server.cc 
combox_server_LDFLAGS=-paroc-nolib -L./.libs/ -lparoc_common 
#combox_server_LDADD=paroc_infmain.std.o
combox_server_LDADD=
combox_server_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC

combox_test_SOURCES=combox_test.cc 
combox_test_LDFLAGS=-paroc-nolib -L./.libs/ -lparoc_common 
combox_test_LDADD=
#combox_test_LDADD=paroc_infmain.std.o
combox_test_CXXFLAGS=$(AM_CXXFLAGS) -DPIC -fPIC

#Compile the cipher module for virtual configuration file
popcipher: popcipher.cc rijndael.cc
	g++ -I../include -o popcipher popcipher.cc rijndael.cc


#Virtual version
if VIRTSUPPORT
EXTRA_DIST=paroc_infmain.std.cc paroc_objmain.std.cc appservice.ph virtual_popc_search_node.ph popc_search_node.ph codemgr.ph \
   jobmgr.ph objectmonitor.ph paroc_service_base.ph remotelog.ph batchmgr.ph  virtual_jobmgr.ph popcloner.ph

inst_HEADERS=paroc_service_base.ph appservice.ph virtual_popc_search_node.ph popc_search_node.ph codemgr.ph remotelog.ph \
   objectmonitor.ph batchmgr.ph jobmgr.ph virtual_jobmgr.ph popcloner.ph
endif 

#Secure version
if SECURESUPPORT
EXTRA_DIST=paroc_infmain.std.cc paroc_objmain.std.cc appservice.ph popc_search_node.ph codemgr.ph \
   jobmgr.ph objectmonitor.ph paroc_service_base.ph remotelog.ph batchmgr.ph \
   popc_security_manager.ph secure_jobmgr.ph secure_popc_search_node.ph

inst_HEADERS=paroc_service_base.ph appservice.ph popc_search_node.ph codemgr.ph remotelog.ph \
   objectmonitor.ph batchmgr.ph jobmgr.ph popc_security_manager.ph secure_jobmgr.ph secure_popc_search_node.ph
endif

if VIRTSECURESUPPORT
EXTRA_DIST=paroc_infmain.std.cc paroc_objmain.std.cc appservice.ph virtual_popc_search_node.ph popc_search_node.ph codemgr.ph \
   jobmgr.ph objectmonitor.ph paroc_service_base.ph remotelog.ph batchmgr.ph  virtual_jobmgr.ph popcloner.ph \
   popc_security_manager.ph virtual_popc_security_manager.ph virtual_secure_jobmgr.ph virtual_secure_popc_search_node.ph \
   secure_jobmgr.ph secure_popc_search_node.ph

inst_HEADERS=paroc_service_base.ph appservice.ph virtual_popc_search_node.ph popc_search_node.ph codemgr.ph remotelog.ph \
   objectmonitor.ph batchmgr.ph jobmgr.ph virtual_jobmgr.ph popcloner.ph popc_security_manager.ph \
   virtual_popc_security_manager.ph virtual_secure_jobmgr.ph virtual_secure_popc_search_node.ph secure_jobmgr.ph \
   secure_popc_search_node.ph
endif

if STANDARDSUPPORT
EXTRA_DIST=paroc_infmain.std.cc paroc_objmain.std.cc appservice.ph popc_search_node.ph codemgr.ph \
   jobmgr.ph objectmonitor.ph paroc_service_base.ph remotelog.ph batchmgr.ph popfilemanager.ph

inst_HEADERS=paroc_service_base.ph appservice.ph popc_search_node.ph codemgr.ph remotelog.ph \
   objectmonitor.ph batchmgr.ph jobmgr.ph popfilemanager.ph
endif

instdir=@includedir@
CLEANFILES=_paroc_*.cc _paroc_*.ph
