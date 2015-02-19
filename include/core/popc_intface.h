/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 27/08/2013
 * @popc interface platform
 *
 *
 */

#ifndef POPC_INTFACE_H
#define POPC_INTFACE_H

#ifdef __WIN32__
#include "popc_intface_win.h"
#else
#include "popc_intface_lin.h"
#endif

// functions below are derivated from <unistd.h>

void popc__exit(int);

//

int popc_access(const char *,int);

//

unsigned int popc_alarm(unsigned int);

//

int popc_chdir(const char *);

//

int popc_close(int);

// // dup2 to: see fcntl

int popc_dup2(int, int);

//

int popc_execvp(const char *, char * const[]);

//

popc_pid_t popc_fork(void);

//

char * popc_getcwd(char *, popc_size_t);

//

int popc_getdtablesize(void);

//

int popc_gethostname(char *, popc_size_t);

//

popc_pid_t popc_getpid(void);

//

int popc_isatty(int);

//

int popc_pipe(int [2]);

//

int popc_read(int, void *, int);

//

int popc_setpgid(popc_pid_t, popc_pid_t);

//

int popc_setuid(popc_uid_t);

//

unsigned int popc_sleep(unsigned int t);

//

int popc_unlink(const char *);

//

int popc_usleep(unsigned long);

//

popc_pid_t popc_vfork(void);

//

int popc_write(int, const void *, int);

// functions are extending standard <string.h>

//

char * popc_strdup(const char *);

//

char * popc_strtok_r(char *, const char *, char **);

// functions below are derivated from <sys/wait.h>

//#include <sys/wait.h>

popc_pid_t popc_wait(int *);

//

popc_pid_t popc_waitpid(int, int *, int);

// functions below are derivated from <stdarg.h>

// popc_va_start(popc_va_list, char *); // attention va_start is a macro!!!

// functions below are derivated from <netdb.h>

//

#ifndef __WIN32__
popc_hostent * popc_gethostbyname(const char *);
#endif

//

popc_in_addr_t popc_inet_addr(const char *);

//

void popc_endhostent(void);

//

//functions below are derivated from <sys/time.h>
int popc_gettimeofday(popc_timeval *, __timezone_ptr_t);

//functions below are derivated from <pthread.h>

// int popc_pthread_kill(popc_pthread_t, int);

// popc_pthread_t popc_pthread_self(void);

//functions below are derivated from <signal.h>

//

popc_sighandler_t popc_signal(int, popc_sighandler_t);

int popc_kill(pid_t, int);

//functions below are derivated from <dirent.h>
/*
DIR popc_opendir(const char *);

int popc_closedir(DIR *);

popc_dirent * popc_readdir(DIR *);
*/

// dlfcn

//

void * popc_dlopen(const char *, int);

//

char * popc_dlerror(void);

//

void * popc_dlsym(void *, const char *);

//

int popc_dlclose(void *);

//

int popc_fcntl(int, int, int);

// xdr
//
//

// fcntl

int popc_open(const char *, int);

//

int popc_open(const char *, int, mode_t);

//

int popc_creat(const char *, mode_t);

// times

#ifndef __WIN32__
popc_clock_t popc_times(popc_tms *);

// pwd

popc_passwd * popc_getpwnam(const char *);
#endif

// sys/socket

//functions below are derivated from <sys/socket.h>

int popc_accept(int , __SOCKADDR_ARG, socklen_t *);

//

int popc_bind(int, __CONST_SOCKADDR_ARG, socklen_t);

//

int popc_connect(int, __CONST_SOCKADDR_ARG, socklen_t);

//

int popc_getsockname(int, __SOCKADDR_ARG, socklen_t *);
//

int popc_getsockopt(int, int, int, void *, socklen_t *);

//

int popc_listen(int, int);

//

int popc_socket(int, int, int);

//
// arpa/inet.h

uint32_t    popc_htonl(uint32_t);

//

uint16_t    popc_htons(uint16_t);

//

uint32_t    popc_ntohl(uint32_t);

//

uint16_t    popc_ntohs(uint16_t);

int popc_sysinfo(int command, char *buf, long count);

// stdlib.h
#ifndef __WIN32__
int popc_mkstemp(char *);
#endif

// poll.h

int popc_poll(struct pollfd *, int, int);

// strings.h

int popc_strcasecmp(const char *, const char *);

//

int popc_strncasecmp(const char *, const char *, popc_size_t);

//errno.h

void Verbose(int argc, char *argv[]);


/*! \brief Run a command using fork
 * This method simply calls a command by creating a fork.
 * @param argv Command and arguments
 * @param env
 * @return Zero */
int RunCmd(int argc, char **argv, char *env[], int *status=NULL);
int RunCmd(int argc, const char *argv[]);
int RunPipe(int argc1, const char *argv1[], int argc2, const char *argv2[]);

//setenv
#ifndef __LINUX__
int popc_setenv(const char *name, const char *value, int replace);
#endif

#endif
