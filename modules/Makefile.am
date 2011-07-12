AUTOMAKE_OPTIONS=no-dependencies
SUBDIRS=xdr-zlib raw-zlib 
if XMLBUILD
SUBDIRS+= xml
endif

if GMBUILD
SUBDIRS+= gm
endif

if HTTPBUILD
SUBDIRS+= http
endif

script_DATA=paroc_buffer.map paroc_combox.map
scriptdir=@libdir@/plugins



