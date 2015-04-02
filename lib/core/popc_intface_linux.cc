#include "popc_intface.h"

#ifdef _POP_
#include "popc_logger.h"
#else
// Note: we redefine two methods of the logger here. This allows to use this file outside of popc
// This can of course be made in a cleaner way
#define LOG_INFO(_log_msg, ...)    fprintf(stderr, _log_msg, ##__VA_ARGS__)
#define LOG_ERROR(_log_msg, ...)   fprintf(stderr, _log_msg, ##__VA_ARGS__)
#endif

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>



// functions below are derivated from <unistd.h>

#define R_OK    4       /* Test for read permission.  */
#define W_OK    2       /* Test for write permission.  */
#define X_OK    1       /* Test for execute permission.  */
#define F_OK    0       /* Test for existence.  */

void popc__exit(int a) {
    _exit(a);
}

int popc_access(const char * a,int b) {
    return access(a, b);
}

unsigned popc_alarm(unsigned int a) {
    return alarm(a);
}

int popc_chdir(const char * a) {
    return chdir(a);
}

int popc_close(int a) {
    return close(a);
}

int popc_dup2(int a, int b) {
    return dup2(a, b);
}

int popc_execvp(const std::string& a, char * const b[]){
    char* dup = strdup(a.c_str());
    int ret = execvp(dup, b);
    free(dup);
    return ret;
}

int popc_fork(void) {
    return fork();
}

char * popc_getcwd(char * a , popc_size_t b) {
    return getcwd(a, b);
}

int popc_getdtablesize(void) {
    return getdtablesize();
}

int popc_gethostname(char * a, int b) {
    return gethostname(a, b);
}

int popc_getpid(void) { // normally return parameter pid_t
    return getpid();
}

int popc_isatty(int a) {
    return isatty(a);
}

int popc_pipe(int a[2]) {
    return pipe(a);
}

int popc_read(int a, void * b, int c) {
    return read(a, b, c);
}



int popc_setpgid(int a, int b) {
    return setpgid(a, b);
}

int popc_setuid(popc_uid_t a) { // normally uid_t parameter
    return setuid(a);
}

unsigned int popc_sleep(unsigned int a) {
    return sleep(a);
}

int popc_unlink(const char * a) {
    return unlink(a);
}

int popc_usleep(unsigned long a) {
    return usleep(a);
}

//popc_pid_t popc_vfork(void)
//{
//  return vfork();
//}

int popc_write(int a, const void * b, int c) {
    return write(a, b, c);
}


// functions are extending standard <string.h>


char * popc_strdup(const char * a) {
    return strdup(a);
}

void popc_tokenize(std::vector<std::string>& xr_result, const std::string& x_str , const std::string& x_sep) {
    char* tmpstr = strdup(x_str.c_str());
    char *tok=strtok(tmpstr,x_sep.c_str());
    while(tok!=nullptr) {
        xr_result.push_back(std::string(tok));
        tok=strtok(nullptr,x_sep.c_str());
    }
    free(tmpstr);
}

void popc_tokenize_r(std::vector<std::string>& xr_result, const std::string& x_str , const std::string& x_sep) {
    char* tmpstr = strdup(x_str.c_str());
    char *tmp = nullptr;
    char *tok=strtok_r(tmpstr,x_sep.c_str(),&tmp);
    while(tok!=nullptr) {
        xr_result.push_back(std::string(tok));
        tok=strtok_r(nullptr,x_sep.c_str(),&tmp);
    }
    free(tmpstr);
}


// functions below are derivated from <sys/wait.h>


popc_pid_t popc_wait(int * a) {
    return wait(a);
}


int popc_waitpid(int a, int * b, int c) {
    return waitpid(a, b, c);
}


//

//popc_va_start(a, b)
//{
//  va_start(a,b);
//}



// functions below are derivated from <netdb.h>


popc_hostent * popc_gethostbyname(const char * a) {
    return gethostbyname(a);
}

popc_in_addr_t popc_inet_addr(const char *a) {
    return inet_addr(a);
}

void popc_endhostent(void) {
    return endhostent();
}



// functions below are derivated from <sys/time.h>


int popc_gettimeofday(popc_timeval * a, __timezone_ptr_t b) {
    return gettimeofday(a,b);
}

//functions below are derivated from <pthread.h>

/* int popc_pthread_kill(popc_pthread_t a, int b)
{
        return pthread_kill(a, b);
}

popc_pthread_t popc_pthread_self(void)
{
    return pthread_self();
}
*/

//functions below are derivated from <signal.h>

popc_sighandler_t popc_signal(int a, popc_sighandler_t b) {
    return signal(a, b);
}

int popc_kill(pid_t a, int b) {
    return kill(a,b);
}


//functions below are derivated from <dirent.h>

/*
problem if we wrapper with features!
highly dependent on the system!
port exists with mingw where the normal inclusion. "h"

*/

/*
DIR * popc_opendir(const char * a)
{
    return opendir(a);
}

int popc_closedir(DIR * a)
{
    return closedir(a);
}

popc_dirent * popc_readdir(DIR * a)
{
    return readdir(a);
}
*/


//functions below are derivated from <dlfcn.h>
#ifdef HAVE_LIBDL
void * popc_dlopen(const char * a, int b) {
    return dlopen(a,b);
}

char * popc_dlerror(void) {
    return dlerror();
}

void * popc_dlsym(void * a, const char * b) {
    return dlsym(a, b);
}

int popc_dlclose(void *a) {
    return dlclose(a);
}

/*int popc_fcntl(int a, int b, long c)
{
    return fcntl(a, b, c);
}*/

#endif

//functions below are derivated from <fcntl.h>

int popc_open(const char * a, int b) {
    return open(a, b);
}

int popc_open(const char * a, int b, mode_t c) {
    return open(a, b, c);
}

int popc_creat(const char * a, mode_t b) {
    return creat(a, b);
}


//functions below are derivated from <sys/times.h>

popc_clock_t popc_times(popc_tms * a) {
    return times(a);
}



//functions below are derivated from <pwd.h>

popc_passwd * popc_getpwnam(const char * a) {
    return getpwnam(a);
}


//functions below are derivated from <sys/socket.h>

int popc_accept(int a, __SOCKADDR_ARG b, socklen_t * c) {
    return accept(a, b, c);
}

int popc_bind(int a, __CONST_SOCKADDR_ARG b, socklen_t c) {
    return bind(a, b, c);
}

int popc_connect(int a, __CONST_SOCKADDR_ARG b, socklen_t c) {
    return connect(a, b, c);
}

int popc_getsockname(int a, __SOCKADDR_ARG b, socklen_t * c) {
    return getsockname(a, b, c);
}

int popc_getsockopt(int a, int b, int c, void * d, socklen_t * e) {
    return getsockopt(a, b, c, d, e);
}

int popc_listen(int a, int b) {
    return listen(a, b);
}

int popc_socket(int a, int b, int c) {
    return socket(a, b, c);
}



//functions below are derivated from <arpa/inet.h>

uint32_t    popc_htonl(uint32_t a) {
    return htonl(a);
}

uint16_t    popc_htons(uint16_t a) {
    return htons(a);
}

uint32_t    popc_ntohl(uint32_t a) {
    return ntohl(a);
}

uint16_t    popc_ntohs(uint16_t a) {
    return ntohs(a);
}



//functions below are derivated from <stdlib.h>
int popc_sysinfo(int /*command*/, char* /*buf*/, long /*count*/) {
    return 0;
    //TODO return sysinfo(command, buf, count);
}

int popc_mkstemp(char *a) {
    return mkstemp(a);
}


//functions below are derivated from <poll.h>


int popc_poll(struct pollfd * a, nfds_t b, int c) {
    return poll(a, b, c);
}


//functions below are derivated from <strings.h>


int popc_strcasecmp(const char * a, const char * b) {
    return strcasecmp(a, b);
}


int popc_strncasecmp(const char * a, const char * b, popc_size_t c) {
    return strncasecmp(a, b, c);
}

// Create an array of arguments from an array of const string. Used to pass args to execve
char** popc_createArgsFromVect(const std::vector<std::string>& x_vect)
{
    char** result = reinterpret_cast<char**>(malloc((x_vect.size() + 1) * sizeof(char*)));
    char** pres   = result;
    for(const auto& elem : x_vect)
    {
        *pres = strdup(elem.c_str());
        pres++;
    }
    *pres = nullptr;
    return result;
}

// Free an array of arguments
void popc_freeArgs(char** args){
    char** p = args;
    while(*p != nullptr)
    {
        free(*p);
        p++;
    }
    free(args);
}

// RunCmd function
int RunCmd(int argc, char **argv, char *env[], int *status) {
    (void)argc;
    char *file=nullptr;

    if(argv==nullptr || argv[0]==nullptr) {
        return ENOENT;
    }
    file=argv[0];
    //  if (access(file,X_OK)!=0)
    //    {
    //      return -1;
    //    }
    popc_signal(popc_SIGCHLD, ((status==nullptr) ? popc_SIG_IGN : popc_SIG_DFL));

#ifndef UC_LINUX
    int pid=popc_fork();
    if(pid==-1) {
        int err=errno;
        LOG_ERROR("[CORE] Fork fails to execute. Can't run command. errno=%d ", errno);
        return err;
    } else if(pid==0) {
        /* Note LW: Commented since this stops "segfault" messages to be logged in terminal. What is the purpose of these lines ?
        int nf=popc_getdtablesize();
        for(int fd=3; fd<nf; fd++) {
            popc_close(fd);
        }
        */
        if(env!=nullptr) {
            while(*env!=nullptr) {
                putenv(popc_strdup(*env));
                env++;
            }
        }
        if(status==nullptr) {
            popc_setpgid(0,0);
        }
        //Child process
        popc_execvp(file,argv);
        LOG_ERROR("[CORE] Execution of [%s] fails",file);
        popc__exit(-1);
    }
#else
    int pid=popc_vfork();
    if(pid==-1) {
        int err=errno;
        LOG_ERROR("[CORE] Fork fails to execute! errno=%d", errno);
        return err;
    } else if(pid==0) {
        execve(file,argv,env);
        LOG_ERROR("[CORE] Execution of [%s] fail (popc_vfork)",file);
        popc__exit(-1);
    }
#endif
    if(status!=nullptr) {
        popc_waitpid(pid, status, 0);
    }
    return 0;
}

int RunCmd(int argc, const char *argv[]) {
/* TODO: See what to use
    char cmd[1024]="";

    // strcat(cmd,"sh ");
    for(int i =0; i<argc; i++) {
        strcat(cmd,argv[i]);
        strcat(cmd," ");
    }
    LOG_INFO("Execute %s", cmd);
    system(cmd);

    return 0;
*/


    argv[argc] = nullptr;
    int status;
    int pid = vfork();
    if(pid<0) {
        perror("POP-C++ Error: popcc run command");
        _exit(1);
    } else if(pid == 0) {
        execvp(argv[0], const_cast<char**>(argv));
        LOG_ERROR( "POP-C++ Error: %s not found", argv[0]);
        _exit(1);
    }
    wait(&status);
    int ret = WEXITSTATUS(status);
    return ret;
}

// RunPipe function
int RunPipe(int argc1, const char *argv1[], int argc2, const char *argv2[]) {
    argv1[argc1] = nullptr;
    argv2[argc2] = nullptr;

    int p[2];
    if(pipe(p) != 0) {
        perror("Error in pipe");
        _exit(1);
    }

    int status;
    int pid1=fork();
    if(pid1<0) {
        perror("Error in pid (1)");
        _exit(1);
    } else if(pid1==0) {
        close(p[0]);
        dup2(p[1],1);
        execvp(argv1[0], const_cast<char**>(argv1));
        LOG_ERROR("POP-C++ Error: %s not found",argv1[0]);
        _exit(1);
    }

    int pid2 = fork();
    if(pid2<0) {
        perror("Error in pid (2)");
        _exit(1);
    }

    if(pid2 == 0) {
        close(p[1]);
        dup2(p[0],0);
        execvp(argv2[0], const_cast<char**>(argv2));
        LOG_ERROR("POP-C++ Error: %s not found",argv2[0]);
        _exit(1);
    }
    close(p[0]);
    close(p[1]);

    wait(&status);
    int ret = WEXITSTATUS(status);
    if(ret != 0) {
        return ret;
    }

    wait(&status);
    ret = WEXITSTATUS(status);
    return ret;
}
