#
# Autoconf tools configure.ac file
# Process this file with autoconf to produce a configure script.
# use the script popc_regenrate_configuration in /dev/script/ to 
# produce new files.
#

# Version of the tools required
# Do not update the value if not needed, older user of POP-C++ will not be able to 
# install the tool.

AC_PREREQ(2.61)

# Define the project and its version number
AC_INIT([popc], [2.5])
AM_INIT_AUTOMAKE(no-dependencies)

#
# Check for host architecture
# With this patch, Mac OS X user doesn't need to add the -DARCH_MAC flag to the
# configure line. It will be added automatically.
# 

AC_CANONICAL_HOST
case $host_os in
	darwin* )
		echo 'Darwin Architecture detected...'
		CPPFLAGS+="-DARCH_MAC "
		;;
	linux*)
		# Do something specific for linux
		;;
	*BSD*)
		# Do something specific for BSD
		;;
	*)
		#Default Case
		AC_MSG_ERROR([Your platform is not currently supported])
		;;
esac

#
# Define base language
#

AC_LANG(C++)

#
# Define base prefix if no --prefix is used
#

AC_PREFIX_DEFAULT(/usr/local/popc)

test -n "${prefix}" || prefix=/usr/local/popc

host_processor=`uname -m`
test -n "$host_processor" || host_processor="$host_cpu"

host_kernel=`uname -s`

test -n "$host_kernel" || host_kernel="$host_os"

AC_SUBST(host)
AC_SUBST(host_os)
AC_SUBST(host_vendor)
AC_SUBST(host_cpu)
AC_SUBST(host_kernel)

standard=true;


AC_ARG_ENABLE(globus,
[ --enable-globus=flavor  Enable Globus-support in Popc++],
[
test -n "${GLOBUS_LOCATION}" || AC_MSG_ERROR(GLOBUS_LOCATION environment variable not found); \
globusdir=${GLOBUS_LOCATION}; \
globusflavor="${enableval}"; \
test -n "$globusflavor" || globusflavor="gcc32dbg"; \
globus=true;
], [ globus=false])

AM_CONDITIONAL(GLOBUS, test x$globus = xtrue)
test x$globus = xfalse || AC_SUBST(globusdir)
test x$globus = xfalse || AC_SUBST(globusflavor)

echo '#buffer metrics' >  modules/paroc_buffer.map
echo "${prefix}/lib/plugins/paroc_raw-zlib.so 5 " >>  modules/paroc_buffer.map
echo "${prefix}/lib/plugins/paroc_xdr-zlib.so 6 " >>  modules/paroc_buffer.map


echo '#protocol metrics' >  modules/paroc_combox.map

AC_ARG_ENABLE(mpi,
[ --enable-mpi  Enable POP-C++ support for MPI],
[
mpi=true;
], [ mpi=false])



AM_CONDITIONAL(MPISUPPORT, test x$mpi = xtrue)

case $host in 
*-linux*) linux=true ;;
esac

AM_CONDITIONAL(LINUX, test x${linux} = xtrue)



#
# ViSaG : clementval
# Add virtual as configure option
#

AC_ARG_ENABLE(virtual,
[ --enable-virtual   Enable POP-C++ virtual mode],
[
virtual=true;
], [ virtual=false])


#
# Add secure as configure option
#

AC_ARG_ENABLE(secure,
[--enable-secure  Enable POP-C++ secure mode],
[
secure=true;
], [ secure=false])

virtsecure=false

if test x$virtual = xtrue
then
   standard=false;
   if test x$secure = xtrue
   then
      virtual=false;
      secure=false;
      virtsecure=true;
   fi
fi

if test x$secure = xtrue
then 
   standard=false;
fi

AC_SUBST(virtual)
AC_SUBST(secure)
AC_SUBST(virtsecure)

AM_CONDITIONAL(VIRTSUPPORT, test x$virtual = xtrue)
AM_CONDITIONAL(SECURESUPPORT, test x$secure = xtrue)
AM_CONDITIONAL(VIRTSECURESUPPORT, test x$virtsecure = xtrue)
AM_CONDITIONAL(STANDARDSUPPORT, test x$standard = xtrue)


AC_PROG_YACC
AC_PROG_CXX
#AC_PROG_CC
AC_PROG_CXXCPP
AC_PROG_LEX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
LT_PREREQ([2.2.4])
LT_INIT

# Checks for libraries.
AC_CHECK_LIB(pthread, pthread_create)
AC_CHECK_LIB(nsl, gethostbyname)
AC_CHECK_LIB(socket, socket)
AC_CHECK_LIB(dl, dlopen)

PKG_CONFIG=$(which pkg-config)

# ViSaG : clementval
# if virtual enabled, check for libvirt, vix and define POPC_VIRTUAL to 1
if test x$virtual = xtrue
then
 #  PKG_CHECK_MODULES([LIBVIRT], [libvirt >= 0.8.5])
   VIX_LIBS="-I/usr/include/vmware-vix"
   AC_SUBST([VIX_LIBS])
   VIX_CFLAGS="-lvixAllProducts -ldl"
   AC_SUBST([VIX_CFLAGS])   
   AC_DEFINE([POPC_VIRTUAL], [1], [Virtual version])
fi

#if secure enable, define POPC_SECURE to 1
if test x$secure = xtrue
then
   AC_DEFINE([POPC_SECURE], [1], [Secure version])
fi


if test x$virtsecure = xtrue
then
  # PKG_CHECK_MODULES([LIBVIRT], [libvirt >= 0.8.5])
   VIX_LIBS="-I/usr/include/vmware-vix"
   AC_SUBST([VIX_LIBS])
   VIX_CFLAGS="-lvixAllProducts -ldl"
   AC_SUBST([VIX_CFLAGS])   
   AC_DEFINE([POPC_SECURE_VIRTUAL], [1], [Secure Virtual Version])
fi

# ViSaG




AC_CHECK_TYPE(socklen_t)

AC_MSG_CHECKING([dynamic linking executable])
LDFLAGSOLD="$LDFLAGS"
LDFLAGS="$LDFLAGSOLD -rdynamic"

AC_LINK_IFELSE( 
[AC_LANG_PROGRAM([[const char hw[] = "Hello, World\n";]])],
[AC_MSG_RESULT([yes]);AC_DEFINE([POPC_EXTRA_LINK],["-rdynamic"],[Dynamic exec])], 
[ LDFLAGS="$LDFLAGSOLD -export-dynamic";\
  AC_LINK_IFELSE(
   [AC_LANG_PROGRAM([[const char hw[] = "Hello, World\n";]])],
   [AC_MSG_RESULT([yes]); AC_DEFINE([POPC_EXTRA_LINK],["-export-dynamic"],[Dynamic exec])], 
   [AC_MSG_RESULT([no])])]
)
LDFLAGS=$LDFLAGSOLD
#AC_SEARCH_LIBS(gethostbyname, -lnsl -lsocket)
#AC_SEARCH_LIBS(socket, -lnsl -lsocket)


# Checks for header files.
#AC_HEADER_STDC
#AC_HEADER_SYS_WAIT

# Checks for typedefs, structures, and compiler characteristics.
#AC_HEADER_STDBOOL
#AC_C_CONST
#AC_C_INLINE
#AC_TYPE_SIZE_T
#AC_HEADER_TIME

# Checks for library functions.
#AC_FUNC_FORK
#AC_FUNC_MALLOC
#AC_FUNC_MEMCMP
#AC_FUNC_REALLOC

#AC_FUNC_STAT
#AC_FUNC_VPRINTF

#AC_CHECK_FUNCS(alarm dup2 getcwd gethostbyname gethostname gettimeofday memset mkdir putenv socket strchr strdup strerror strrchr strstr sysinfo)

AC_SUBST(LIBS)


AC_CONFIG_LINKS(parser/debug.cc:lib/debug.cc parser/utils.cc:lib/utils.cc)

#Updated by clementval : add include/popc_search_node.ph:lib/popc_search_node.cc
AC_CONFIG_LINKS(include/jobmgr.ph:lib/jobmgr.ph include/popc_search_node.ph:lib/popc_search_node.cc include/codemgr.ph:lib/codemgr.ph)
#End of update
AC_CONFIG_LINKS(include/remotelog.ph:lib/remotelog.ph include/appservice.ph:lib/appservice.ph) 
AC_CONFIG_LINKS(include/batchmgr.ph:lib/batchmgr.ph)
AC_CONFIG_LINKS(include/objectmonitor.ph:lib/objectmonitor.ph)
AC_CONFIG_LINKS(include/paroc_service_base.ph:lib/paroc_service_base.ph)

AC_CONFIG_HEADER(config.h)
AC_CONFIG_FILES([parser/popcc.cc])
#AC_CONFIG_FILES([popcc], [chmod +x popcc])
AC_CONFIG_FILES([scripts/popcrun], [chmod +x scripts/popcrun])
AC_CONFIG_FILES([services/popcobjrun], [chmod +x services/popcobjrun])
AC_CONFIG_FILES([scripts/popc-user-env.sh], [chmod +x scripts/popc-user-env.sh])
AC_CONFIG_FILES([scripts/popc-user-env.csh], [chmod +x scripts/popc-user-env.csh])
AC_CONFIG_FILES([scripts/popc-runtime-env.in], [chmod +x scripts/popc-runtime-env.in])
AC_CONFIG_FILES([scripts/popc_setup], [chmod +x scripts/popc_setup])
AC_CONFIG_FILES([globus/popc_setup_globus], [chmod +x globus/popc_setup_globus])
AC_CONFIG_FILES([scripts/popc_script_setup], [chmod +x scripts/popc_script_setup])
AC_CONFIG_FILES(Makefile scripts/Makefile parser/Makefile include/Makefile lib/Makefile services/Makefile globus/Makefile mpi/Makefile)
AC_CONFIG_FILES(model/Makefile)
AC_CONFIG_FILES(modules/Makefile modules/raw-zlib/Makefile  modules/xdr-zlib/Makefile)

AC_CONFIG_MACRO_DIR([m4])

test x$globus = xfalse  || AC_CONFIG_FILES(globus/globus_header)
AC_OUTPUT
