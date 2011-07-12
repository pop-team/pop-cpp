AUTOMAKE_OPTIONS=no-dependencies

SUBDIRS= scripts parser include lib services modules model test

if MPISUPPORT
SUBDIRS+= mpi
endif

install-exec-hook:
	@if [ ! -f @prefix@/etc/paroc-runtime-env.sh ]; then cp @prefix@/etc/paroc-runtime-env.in @prefix@/etc/paroc-runtime-env.sh; fi
	@@sbindir@/paroc_setup -ask

