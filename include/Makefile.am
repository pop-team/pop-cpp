AUTOMAKE_OPTIONS=no-dependencies

IDLC=@top_srcdir@/popccpp

if VIRTSUPPORT
include_HEADERS=paroc_base.h paroc_array.h paroc_list.h paroc_utils.h paroc_od.h paroc_string.h\
	debug.h paroc_sys.h paroc_system.h paroc_mutex.h paroc_thread.h  paroc_buffer.h paroc_buffer_utils.h priolist.h\
	paroc_accesspoint.h  paroc_event.h paroc_memspool.h\
	paroc_combox.h paroc_combox_socket.h paroc_combox_factory.h \
	paroc_buffer_factory.h paroc_buffer_factory_finder.h\
	paroc_buffer_xdr_factory.h paroc_buffer_xdr.h\
	paroc_buffer_raw.h paroc_buffer_raw_factory.h\
	paroc_exception.h sysinfodef.h\
	paroc_broker.h paroc_broker_factory.h paroc_object.h paroc_interface.h paroc_allocobj.h timer.h\
	VPopCWrapper.h WrapperFactory.h ESXWrapper.h POPWrapper.h popwayback.h popvm.h  nodethread.h rijndael.h request.h explorationList.h response.h popc_search_node_info.h
endif

if SECURESUPPORT
include_HEADERS=paroc_base.h paroc_array.h paroc_list.h paroc_utils.h paroc_od.h paroc_string.h\
	debug.h paroc_sys.h paroc_system.h paroc_mutex.h paroc_thread.h  paroc_buffer.h paroc_buffer_utils.h priolist.h\
	paroc_accesspoint.h  paroc_event.h paroc_memspool.h\
	paroc_combox.h paroc_combox_socket.h paroc_combox_factory.h \
	paroc_buffer_factory.h paroc_buffer_factory_finder.h\
	paroc_buffer_xdr_factory.h paroc_buffer_xdr.h\
	paroc_buffer_raw.h paroc_buffer_raw_factory.h\
	paroc_exception.h sysinfodef.h\
	paroc_broker.h paroc_broker_factory.h paroc_object.h paroc_interface.h paroc_allocobj.h timer.h popwayback.h nodethread.h request.h explorationList.h response.h popc_search_node_info.h
endif

if VIRTSECURESUPPORT
include_HEADERS=paroc_base.h paroc_array.h paroc_list.h paroc_utils.h paroc_od.h paroc_string.h\
	debug.h paroc_sys.h paroc_system.h paroc_mutex.h paroc_thread.h  paroc_buffer.h paroc_buffer_utils.h priolist.h\
	paroc_accesspoint.h  paroc_event.h paroc_memspool.h\
	paroc_combox.h paroc_combox_socket.h paroc_combox_factory.h \
	paroc_buffer_factory.h paroc_buffer_factory_finder.h\
	paroc_buffer_xdr_factory.h paroc_buffer_xdr.h\
	paroc_buffer_raw.h paroc_buffer_raw_factory.h\
	paroc_exception.h sysinfodef.h\
	paroc_broker.h paroc_broker_factory.h paroc_object.h paroc_interface.h paroc_allocobj.h timer.h\
	VPopCWrapper.h WrapperFactory.h ESXWrapper.h POPWrapper.h popwayback.h popvm.h  nodethread.h rijndael.h request.h explorationList.h response.h popc_search_node_info.h
endif

if STANDARDSUPPORT
include_HEADERS=paroc_base.h paroc_array.h paroc_list.h paroc_utils.h paroc_od.h paroc_string.h\
	debug.h paroc_sys.h paroc_system.h paroc_mutex.h paroc_thread.h  paroc_buffer.h paroc_buffer_utils.h priolist.h\
	paroc_accesspoint.h  paroc_event.h paroc_memspool.h\
	paroc_combox.h paroc_combox_socket.h paroc_combox_factory.h \
	paroc_buffer_factory.h paroc_buffer_factory_finder.h\
	paroc_buffer_xdr_factory.h paroc_buffer_xdr.h\
	paroc_buffer_raw.h paroc_buffer_raw_factory.h\
	paroc_exception.h sysinfodef.h\
	paroc_broker.h paroc_broker_factory.h paroc_object.h paroc_interface.h paroc_allocobj.h timer.h\
	popwayback.h nodethread.h request.h explorationList.h response.h popc_search_node_info.h POPString.h popc_logger.h
endif

# paroc_DATA=	proxy.ph paroc_service_base.ph appservice.ph codemgr.ph remotelog.ph objectmonitor.ph jobmgr.ph popc_search_node.ph

#instdir=@includedir@
# popcdir=@includedir@

# parocfiles= jobmgr.ph codemgr.ph remotelog.ph appservice.ph objectmonitor.ph proxy.ph paroc_service_base.ph popc_search_node.ph

# $(parocfiles): %.ph : ../lib/%.ph
#	cp $< .

#CLEANFILES=$(parocfiles)
