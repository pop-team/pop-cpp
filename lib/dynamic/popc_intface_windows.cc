
#include "popc_intface.h"

// pthread

#include <pthread.h>

#include <windows.h>

#include <winsock2.h>

#define __SOCKADDR_ARG struct sockaddr*  

#define __CONST_SOCKADDR_ARG const struct sockaddr*

// functions below are derivated from <stdlib.h>

static int dtablesize;

void popc__exit(int a)
{
	_exit(a);
}

// functions below are derivated from <unistd.h>

int popc_access(const char * a,int b)
{
	return access(a, b);
}


unsigned popc_alarm(unsigned int a)
{
	int rez;
	
	HANDLE phandle = GetCurrentProcess(); 
	rez = WaitForSingleObject( phandle, a/1000 );
	if (rez == WAIT_OBJECT_0 ) {
            printf("wait object signal out\n");
		return 0; // phandle raised by another thread to exit
	}
        return rez;
}


int popc_chdir(const char * a)
{
	return chdir(a);
}

int popc_close(int a)
{
	return close(a);
}

int popc_dup2(int a, int b)
{
	return dup2(a, b);
}


int popc_execvp(const char * a, char * const b[] )
{
	//return 0;
}

int popc_fork(void)
{
	//return 0;
}

char * popc_getcwd( char * a , popc_size_t b)
{
	return getcwd(a, b);
}


int popc_getdtablesize(void)
{
	if(dtablesize==0)
	{
		int max_stdio = _getmaxstdio();
		unsigned int bound;
		for (bound = 0x10000; _setmaxstdio (bound) < 0; bound = bound / 2);
		dtablesize = bound;
	}
	return dtablesize;
	
}


int popc_gethostname(char * a, int b)
{
    WSADATA wsaData;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    gethostname(a, b);

    return 0;
}

int popc_getpid(void) // normally return parameter pid_t
{
	return getpid();
}

int	popc_isatty(int a)
{
	return isatty(a);
}

int popc_pipe(int a[2] )
{
	return _pipe(a, 256, _O_BINARY);
}

int popc_read(int a, void * b, int c)
{
	return read(a, b, c);
}

int popc_setpgid( int a, int b)
{
	//return 0;
}

int popc_setuid(popc_uid_t a)  // normally uid_t parameter
{
	//return 0;
}

unsigned int popc_sleep(unsigned int a)
{
	Sleep(a * 1000);
	return 0;
}


int popc_unlink(const char * a)
{
	return unlink(a);
}


int popc_usleep(unsigned long a)
{
	Sleep(a/1000);
        return 0;
}

int popc_write(int a, const void * b, int c)
{
	return write(a, b, c);
}

// functions are extending standard <string.h>

char * popc_strdup(const char * a)
{
	return strdup(a);
}

// functions below are derivated from <sys/wait.h>
popc_pid_t popc_wait( int * a)
{
	//wait(a);	// used for RunPipe parocc.cc but will be used more!!
	
}

int popc_waitpid(int a, int * b, int c)
{
	//return waitpid(a, b, c);
	return 0;
}

// functions below are derivated from <winsGetIPock2.h>

//popc_hostent * popc_gethostbyname(const char * a)
//{
//	return gethostbyname(a);
//}

popc_in_addr_t popc_inet_addr(const char *a)
{
	return inet_addr(a);
}

void popc_endhostent(void)
{
	//return endhostent();
}

int popc_gettimeofday(popc_timeval * a, __timezone_ptr_t b)
{
	return gettimeofday(a,b);
}

// the followin function comes from http://www.koders.com

/* Reentrant string tokenizer.  Generic version.
   Copyright (C) 1991,1996-1999,2001,2004,2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <string.h>

#undef strtok_r
#undef __strtok_r

#ifndef _LIBC
# define __strtok_r popc_strtok_r
# define __rawmemchr strchr
#endif

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the saved pointer in SAVE_PTR is used as
   the next starting point.  For example:
	char s[] = "-abc-=-def";
	char *sp;
	x = strtok_r(s, "-", &sp);	// x = "abc", sp = "=-def"
	x = strtok_r(NULL, "-=", &sp);	// x = "def", sp = NULL
	x = strtok_r(NULL, "=", &sp);	// x = NULL
		// s = "abc\0-def\0"
*/
char *
__strtok_r (char *s, const char *delim, char **save_ptr)
{
  char *token;

  if (s == NULL)
    s = *save_ptr;

  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }

  /* Find the end of the token.  */
  token = s;
  s = strpbrk (token, delim);
  if (s == NULL)
    /* This token finishes the string.  */
    *save_ptr = __rawmemchr (token, '\0');
  else
    {
      /* Terminate the token and make *SAVE_PTR point past it.  */
      *s = '\0';
      *save_ptr = s + 1;
    }
  return token;
}
#ifdef weak_alias
libc_hidden_def (__strtok_r)
weak_alias (__strtok_r, strtok_r)
#endif

void * popc_dlopen(const char *, int)
{
}

//

char * popc_dlerror(void)
{
}

//

void * popc_dlsym(void *handle, const char *name)
{    
    /*FARPROC fp;
    fp = GetProcAddress(handle, name);
    if (!fp) {
        return NULL;
    }
    return fp;*/
}

//

int popc_dlclose(void *handle)
{
    /*if (!FreeLibrary(handle)) {
          return -1;
    }
    return 0;*/
}

//functions below are derivated from <fcntl.h>
int popc_fcntl(int fd, int cmd, int arg)
{
    return 0;
}

int popc_open(const char * a, int b)
{
	return open(a, b);
}

int popc_open(const char * a, int b, mode_t c)
{
	return open(a, b, c);
}

int popc_creat(const char * a, mode_t b)
{
	return creat(a, b);
}


int popc_accept(int a, __SOCKADDR_ARG b, socklen_t * c)
{
    return accept(a, b, c);
}

int popc_bind(int a, __CONST_SOCKADDR_ARG b, socklen_t c)
{
    return bind(a, b, c);
}

int popc_connect(int a, __CONST_SOCKADDR_ARG b, socklen_t c)
{
    return connect(a, b, c);
}

int popc_getsockname(int a, __SOCKADDR_ARG b, socklen_t * c)
{
    return getsockname(a, b, c);
}

int popc_getsockopt(int a, int b, int c, void * d, socklen_t * e)
{
    return getsockopt(a, b, c, (char*)d, e);
}

int popc_listen(int a, int b)
{
    return listen(a, b);   
}

int popc_socket(int a, int b, int c)
{
    return socket(a, b, c);
}

//functions below are derivated from <winsock2.h>

uint32_t	popc_htonl(uint32_t a)
{
	return htonl(a);
}


uint16_t	popc_htons(uint16_t a)
{
	return htons(a);
}

uint32_t	popc_ntohl(uint32_t a)
{
	return ntohl(a);
}

uint16_t	popc_ntohs(uint16_t a)
{
	return ntohs(a);
}
/*
#ifndef __GT_FILE
# define __GT_FILE 0
#endif

int popc_mkstemp(char *temp)
{
	return __gen_tempname (temp, __GT_FILE);
}
*/

int popc_poll(struct pollfd *fd, int n, int timeout)
{
	//return 0;
}

int popc_sysinfo(int command, char *buf, long count)
{
    char arch[count], sysname[count];
    int family;
    SYSTEM_INFO sysinf;    // Struct for hardware info
    
    switch(command)
    {
        case SI_SYSNAME:
            strcpy(sysname, "windows32");
            break;
        case SI_ARCHITECTURE:
            GetSystemInfo(&sysinf);  // Get hardware OEM
    
            family = sysinf.wProcessorLevel;
                switch (sysinf.wProcessorArchitecture) {
                case PROCESSOR_ARCHITECTURE_UNKNOWN:
                   strcpy(arch, "unknown");
                   break;
                case PROCESSOR_ARCHITECTURE_INTEL:
                   strcpy(arch, "ix86-pc");
                   break;
                case PROCESSOR_ARCHITECTURE_MIPS:
                   strcpy(arch, "mips");
                   break;
                case PROCESSOR_ARCHITECTURE_ALPHA:
                   strcpy(arch, "alpha");
                   break;
                case PROCESSOR_ARCHITECTURE_PPC:
                   strcpy(arch, "ppc");
                   break;
                case PROCESSOR_ARCHITECTURE_IA64:
                   strcpy(arch, "IA64");
                   break;
                case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
                   strcpy(arch, "IA32 on Win64");
                   break;
                case PROCESSOR_ARCHITECTURE_AMD64:
                   strcpy(arch, "amd64");
                   break;
                case PROCESSOR_ARCHITECTURE_SHX:
                   strcpy(arch, "sh");
                   break;
                case PROCESSOR_ARCHITECTURE_ARM:
                   strcpy(arch, "arm");
                   break;
                case PROCESSOR_ARCHITECTURE_ALPHA64:
                   strcpy(arch, "alpha64");
                   break;
                case PROCESSOR_ARCHITECTURE_MSIL:
                   strcpy(arch, "msil");
                   break;
                default: 
                   strcpy(arch, "unknown");
                   break;
                }

           if (sysinf.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
                switch(family) {
            case 3:
                   strcpy(arch, "i386");
               break;
            case 4:
                   strcpy(arch, "i486");
               break;
            case 5:
                   strcpy(arch, "i586");
               break;
            case 6:
               strcpy(arch, "i686");
               break;
            case 7:
               strcpy(arch, "i786");
               break;
            case 15:
                strcpy(arch, "i786");
                break;
           default:
                strcpy(arch, "ix86");
           }
            break;
        default:
            break;
    }
    return 0;
}
//functions below are derivated from <strings.h>

int popc_strcasecmp(const char * a, const char * b)
{
	return strcasecmp(a, b);
}

int popc_strncasecmp(const char * a, const char * b, popc_size_t c)
{
	return strncasecmp(a, b, c);
}


//functions below are derivated from <time.h>

int popc_gettimeofday(popc_timeval *, __timezone_ptr_t);

//functions below are derivated from <signal.h>

popc_sighandler_t popc_signal(int a, popc_sighandler_t b)
{
	return signal(a, b);
}

int popc_kill(pid_t a, int b)
{
    HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, a);
    if (! h) {
            errno = ESRCH;
            return -1;
    } else {
        if (! TerminateProcess(h, 0)) {
                return -1;
        }
    }
    return 0;
}



typedef void(* popc_sighandler_t) (int);

//#define popc_SIGHUP   1
#define popc_SIGINT   2
#define popc_SIGTERM   15
//#define popc_SIGINT   2
//#define popc_SIGQUIT   3
#define popc_SIGILL   4
#define popc_SIGABRT	   6
//#define popc_SIGKILL   9
//#define popc_SIGPIPE   13
//#define popc_SIGCHLD   17
#define popc_SIG_DFL   ((popc_sighandler_t) 0)
#define popc_SIG_IGN   ((popc_sighandler_t) 1)



// RunCmd function

int RunCmd(int argc, char *argv[])
{
	argv[argc] = 0;
	int status;
	char command_line[1024]="";
	
	for (int i =0; i<argc; i++)
		{
			strcat(command_line,argv[i]);
			strcat(command_line," ");
		}
	status = system(command_line);
	
	return status;
}

// RunPipe function
int RunPipe(int argc1, char *argv1[], int argc2, char *argv2[])
{
	argv1[argc1] = 0;
	argv2[argc2] = 0;
	DWORD status;
	char command_line1[1024]="", command_line2[1024]="";

	for (int i =0; i<argc1; i++)
	{
		strcat(command_line1,argv1[i]);
		strcat(command_line1," ");
	}
	
	for (int i =0; i<argc2; i++)
	{
		strcat(command_line2,argv2[i]);
		strcat(command_line2," ");
	}
	
	STARTUPINFO sInfoSource, sInfoDest;
	SECURITY_ATTRIBUTES sa;
	PROCESS_INFORMATION pInfoSource, pInfoDest;
	HANDLE hPipeIn, hPipeOut;
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
	
	/*HANDLE hTemp = CreateFile(argv2[1],
							GENERIC_WRITE,
							FILE_SHARE_DELETE| FILE_SHARE_WRITE | FILE_SHARE_READ,
							&sa,
							OPEN_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);*/
	
	ZeroMemory(&sInfoSource, sizeof(sInfoSource));
	ZeroMemory(&sInfoDest, sizeof(sInfoDest));
	
	sInfoSource.cb = sizeof(sInfoSource);
	sInfoDest.cb = sizeof(sInfoDest);
	
	sInfoSource.dwFlags = STARTF_USESTDHANDLES;
	sInfoDest.dwFlags = STARTF_USESTDHANDLES;    

	if(CreatePipe(&hPipeIn, &hPipeOut, &sa, 0) == 0)
		return GetLastError();

	sInfoSource.hStdInput = hIn;
	//sInfoSource.hStdError = sInfoSource.hStdOutput = hTemp;
	sInfoSource.hStdError = sInfoSource.hStdOutput = hPipeOut;
    sInfoDest.hStdInput = hPipeIn;
    sInfoDest.hStdError = sInfoDest.hStdOutput = hOut;
	printf("\n\n\n============================Process1==============================\n");
	printf("Before CreateProcess with command_line1=%s\n\n", command_line1);
	if(!CreateProcess(NULL, command_line1, NULL, NULL, TRUE, 0, NULL, NULL, &sInfoSource, &pInfoSource)) {
		printf("CreateProcess failed (%d).\n", GetLastError());
		return -1;
	}

	CloseHandle(pInfoSource.hThread);
	
	printf("============================endofProcess1==============================\n");
	
	printf("\n\n\n============================Process2==============================\n");
	printf("Before CreateProcess with command_line2=%s\n\n", command_line2);
	if(!CreateProcess(NULL, command_line2, NULL, NULL, TRUE, 0, NULL, NULL, &sInfoDest, &pInfoDest)) {
		printf("CreateProcess failed (%d).\n", GetLastError());
		return -1;
	}

	CloseHandle(pInfoDest.hThread);
	
	printf("============================endofProcess2==============================\n\n\n");
	
	HANDLE hArray[2];
    hArray[0] = pInfoSource.hProcess;
    hArray[1] = pInfoDest.hProcess;
    printf("wait for process end!!!\n");
    WaitForMultipleObjects(2, hArray, TRUE, INFINITE);
	printf("end of wait for process end!!!\n");
	GetExitCodeProcess(pInfoSource.hProcess, &status);
	
	if(status != 0) {printf("Process 1 completed.!");return status;}
        else {
            printf("status=%d\n", status);
        }
	GetExitCodeProcess(pInfoDest.hProcess, &status);

    CloseHandle(hArray[0]);
    CloseHandle(hArray[1]);
	return status;
}

int popc_setenv (const char *name, const char *value, int replace) 
{
    char string0[MAX_PATH];
    char *string;

    if (getenv(name)!=NULL && replace==0)
        return 1;
    strcpy(string0, name);
    strcat(string0, "=");
    strcat(string0, value);
    string=strdup(string0);
    if (putenv(string))
        return 1;
    else
        return 0;
}