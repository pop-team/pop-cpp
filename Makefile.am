AUTOMAKE_OPTIONS=no-dependencies

SUBDIRS= scripts parser include lib services modules model test

if MPISUPPORT
SUBDIRS+= mpi
endif
if GLOBUS
SUBDIRS+= globus
endif

#install-exec-hook:
#	@if [ ! -f @prefix@/etc/popc-runtime-env.sh ]; then cp @prefix@/etc/popc-runtime-env.in @prefix@/etc/popc-runtime-env.sh; fi
#	@@sbindir@/popc_setup -ask

documentation:
	doxygen
