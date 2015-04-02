/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 27/08/2013
 * @popc interface platform for windows
 *
 *
 */
#ifndef POP_INTFACE_WIN_H
#define POP_INTFACE_WIN_H

// definitions for access ()

#define R_OK    4       /* Test for read permission.  */
#define W_OK    2       /* Test for write permission.  */
//#define   X_OK    1       /* Test for execute permission.  */
#define F_OK    0       /* Test for existence.  */

#define SI_SYSNAME              1    /* return name of operating system */
#define SI_ARCHITECTURE         6    /* return instruction set arch   */

#define popc_size_t  int

// definitions for process

#define popc_pid_t int

#define popc_uid_t int


// definitions for sockets

#define socklen_t int

// inclusion of headers necessary for windows

#include <unistd.h>

#include <string.h>

#include <stdlib.h>

#include <assert.h>

#include <stdio.h>

#include <sys/types.h>

#include <ctype.h>

#define __SOCKADDR_ARG struct sockaddr*

#define __CONST_SOCKADDR_ARG const struct sockaddr*

// #define uint32_t u_long
#define uint32_t unsigned long

//#define uint16_t u_short
#define uint16_t unsigned int

//#define popc_hostent hostent

typedef uint32_t popc_in_addr_t;
/*struct popc_in_addr
{
  popc_in_addr_t s_addr;
};*/

#include <sys/time.h>

#define popc_timeval timeval

#define __timezone_ptr_t void *

#define popc_timezone  __timezone_ptr_t

// signal

typedef void(* popc_sighandler_t)(int);

//#define popc_SIGHUP   1
#define popc_SIGINT   2
#define popc_SIGTERM   15
//#define popc_SIGQUIT   3
#define popc_SIGILL   4
#define popc_SIGABRT       6
#define popc_SIGKILL   9
//#define popc_SIGPIPE   13
//#define popc_SIGCHLD   17
#define popc_SIG_DFL   ((popc_sighandler_t) 0)
#define popc_SIG_IGN   ((popc_sighandler_t) 1)

#include <signal.h>

// fcntl

#include <fcntl.h>
#define S_IRWXU 00700
#define S_IRGRP 00040
//#define FOPEN           0x01    /* file handle open */
//#define FNOINHERIT      0x10    /* file handle opened _O_NOINHERIT */
#define FAPPEND         02000    /* file handle opened O_APPEND */
//#define FTEXT           0x80    /* file handle is in text mode */
#define F_GETFL 3       /* Get file flags */
#define F_SETFL 4       /* Set file flags */
#define O_NONBLOCK    04000


#include <sys/stat.h>

// dirent

#include <dirent.h>

// errno

#include <errno.h>

#endif
