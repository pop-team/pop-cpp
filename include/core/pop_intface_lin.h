/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 27/08/2013
 * @popc interface platform for linux
 *
 *
 */
#ifndef POP_INTFACE_LIN_H
#define POP_INTFACE_LIN_H

// definitions for access ()

#define R_OK 4 /* Test for read permission.  */
#define W_OK 2 /* Test for write permission.  */
#define X_OK 1 /* Test for execute permission.  */
#define F_OK 0 /* Test for existence.  */

// definitions for process

#define popc_pid_t int

//

#define popc_size_t int

#define popc_uid_t int

#define popc_gid_t int

// inclusion of headers needed for linux

#include <unistd.h>

#include <assert.h>

#include <netdb.h>

#define popc_hostent hostent

#include <netinet/in.h>
#include <arpa/inet.h>

/* Internet address.  */
typedef uint32_t popc_in_addr_t;
struct popc_in_addr {
    popc_in_addr_t s_addr;
};

#include <string.h>

#include <sys/time.h>

#define popc_timeval timeval

#define popc_timezone __timezone_ptr_t

// pthread

#include <pthread.h>

// #define popc_pthread_t  pthread_t

// signal

typedef void (*popc_sighandler_t)(int);

#define popc_SIGHUP 1
#define popc_SIGINT 2
#define popc_SIGTERM 15
#define popc_SIGINT 2
#define popc_SIGQUIT 3
#define popc_SIGILL 4
#define popc_SIGABRT 6
#define popc_SIGKILL 9
#define popc_SIGPIPE 13
#define popc_SIGCHLD 17
#define popc_SIG_DFL ((popc_sighandler_t)0)
#define popc_SIG_IGN ((popc_sighandler_t)1)

// stdarg !!!

#include <stdarg.h>

#define popc_va_list va_list
#define popc_va_start va_start
#define popc_va_end va_end

// dirent
/*
problem if we wrapper with features!
highly dependent on the system!
port exists with mingw where the normal inclusion. "h"

*/

#include <dirent.h>

// dlfcn

#include <dlfcn.h>

// define bits

// xdr

#ifdef __APPLE__
#ifndef bool_t
#define bool_t bool
#endif
#endif

#ifdef __APPLE__
#ifndef enum_t
#define enum_t int
#endif
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#include <rpc/xdr.h>

#define popc_XDR XDR

#define popc_xdrmem_create xdrmem_create
#define popc_xdr_vector xdr_vector
#define popc_xdr_destroy xdr_destroy

// fcntl

#include <fcntl.h>

// times

#include <sys/times.h>

//Not used for now
//#include <sys/sysinfo.h>

#define popc_clock_t unsigned int

#define popc_tms tms

// pwd

#include <pwd.h>

#define popc_passwd passwd

#include <signal.h>

// sys/socket
#include <sys/types.h>

#include <sys/socket.h>

// stdlib
#include <stdio.h>

#include <stdlib.h>

// strings

#include <strings.h>

// poll

#include <poll.h>

#include <sys/stat.h>

// errno

#include <errno.h>

//#include <config.h>

#include <ctype.h>

#endif
