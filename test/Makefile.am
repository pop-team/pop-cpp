AUTOMAKE_OPTIONS=no-dependencies

AM_LDFLAGS=-L@top_srcdir@/lib/.libs
SUBDIRS= method tree

##
# ViSaG : clementval
# Custom target - Generate new sources file with a key for virtual configuration file encryption
##
BUILT_SOURCES = generate.foo
generate.foo: 
	../scripts/aes_clean
