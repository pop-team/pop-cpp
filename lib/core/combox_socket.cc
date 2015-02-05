
/*
 * Note(BW): The complex functions are completely separated between the windows and linux
 * implementation in order to make them more readable and maintainable. The simple functions
 * are still contains conditional Linux / Windows code for sake of clarity.
 */

#include "popc_intface.h"

#ifndef __WIN32__
#include <fcntl.h>
#endif

#include "paroc_combox_socket.h"
#include "paroc_system.h"

#define PROTO_TCP 6
#define PROTO_UDP 17
#define POLLIN 0x001
#define POLLPRI 0x002
#define POLLOUT 0x004

#ifndef __WIN32__

//Following are the Linux implementations

bool paroc_combox_socket::Create(int port, bool server) {
    Close();
    isServer=server;

    auto protocol=PROTO_TCP;
    auto type= SOCK_STREAM;
    sockfd=popc_socket(PF_INET,type,protocol);

    if(sockfd<0) {
        return false;
    }

    if(port>0) {
        sockaddr_in sin;
        memset(&sin,0,sizeof(sin));
        sin.sin_family=AF_INET;
        sin.sin_addr.s_addr=INADDR_ANY;
        sin.sin_port=popc_htons(port);
        SetOpt(SOL_SOCKET,SO_REUSEADDR,(char*)&sin,sizeof(sin)); // lwk : Added this line to allow reuse an earlier socket with the same address

        if(popc_bind(sockfd,(sockaddr *)&sin,sizeof(sin))) {
            return false;
        }
    }

    if(server) {
        pollarray.SetSize(1);
        pollarray[0].fd=sockfd;
        pollarray[0].events=POLLIN;
        pollarray[0].revents=0;
        index=1;
        nready=0;

        connarray.SetSize(1);
        connarray[0]=CreateConnection(sockfd);

        return popc_listen(sockfd,10)==0;
    } else {
        peer=CreateConnection(-1);
    }

    return true;
}

#else

//Following are the Windows implementations

bool paroc_combox_socket::Create(int port, bool server) {
    Close();
    isServer=server;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    auto protocol=PROTO_TCP;
    auto type= SOCK_STREAM;
    sockfd=popc_socket(PF_INET,type,protocol);

    if(sockfd<0) {
        return false;
    }

    if(port>0) {
        sockaddr_in sin;
        memset(&sin,0,sizeof(sin));
        sin.sin_family=AF_INET;
        sin.sin_addr.s_addr=INADDR_ANY;
        sin.sin_port=popc_htons(port);
        SetOpt(SOL_SOCKET,SO_REUSEADDR,(char*)&sin,sizeof(sin)); // lwk : Added this line to allow reuse an earlier socket with the same address
        if(popc_bind(sockfd,(sockaddr *)&sin,sizeof(sin))!=0) {
            return false;
        }
    }

    if(server) {
        FD_ZERO(&activefdset);
        FD_ZERO(&readfds);

        FD_SET(sockfd, &activefdset);
        highsockfd = sockfd;
        nready=0;

        connarray.SetSize(1);
        connarray[0]=CreateConnection(sockfd);

        sockaddr_in sin;
        memset(&sin,0,sizeof(sin));
        sin.sin_family=AF_INET;
        sin.sin_addr.s_addr=INADDR_ANY;
        sin.sin_port=htons(0);

        if(popc_bind(sockfd,(sockaddr *)&sin,sizeof(sin)) == SOCKET_ERROR) {
            LOG_ERROR("bind error");
            WSACleanup();
            return false;
        }

        if(popc_listen(sockfd,10) == SOCKET_ERROR) {
            LOG_ERROR("listen error");
            WSACleanup();
            return false;
        }

        return true;
    } else {
        peer=CreateConnection(-1);
    }

    return true;
}

#endif

//Normal implementations that are not separated by arch

paroc_connection_sock::paroc_connection_sock(paroc_combox *cb): paroc_connection(cb) {
    sockfd=-1;
#ifndef __WIN32__
    popc_signal(popc_SIGPIPE, popc_SIG_IGN);
#endif
}

paroc_connection_sock::paroc_connection_sock(int fd, paroc_combox *cb): paroc_connection(cb) {
    sockfd=fd;
}

paroc_connection_sock::paroc_connection_sock(paroc_connection_sock &me): paroc_connection(me.GetCombox(), me.GetBufferFactory()) {
    sockfd=me.sockfd;
}

paroc_connection *paroc_connection_sock::Clone() {
    return new paroc_connection_sock(*this);
}

paroc_combox_socket::paroc_combox_socket() {
    peer=NULL;
    sockfd=-1;
    index=0;
    nready=0;
    isCanceled=false;
    isServer=false;
}

paroc_combox_socket::~paroc_combox_socket() {
    Close();
}

bool paroc_combox_socket::Connect(const char *url) {
    if(url==NULL) {
#ifdef __WIN32__
        errno=WSAEDESTADDRREQ;
#else
        errno=EDESTADDRREQ;
#endif
        return false;
    }

    char *host;
    while(isspace(*url)) {
        url++;
    }

    if(strncmp(url,"socket://",9)==0) {
        host=popc_strdup(url+9);
    } else {
        host=popc_strdup(url);
    }

    char *s=strchr(host,':');
    int port;
    if(s==NULL || sscanf(s+1,"%d",&port)!=1) {
        free(host);
        return false;
    }
    *s=0;

    bool ret = Connect(host,port);
    free(host);

    if(ret) {
        peer->sockfd=sockfd;
    }
    return ret;
}

int paroc_combox_socket::Send(const char *s,int len) {
    int n=0;
    int count=0;
    while(len>0) {
#ifndef __WIN32__
        n=write(sockfd,s,len);
#else
        n=send(sockfd,s,len,0);
#endif
        if(n>0) {
            count+=n;
            s+=n;
            len-=n;
        } else if(errno!=EINTR) {
            break;
        }
    }
    return count;
}

int paroc_combox_socket::Send(const char *s,int len, paroc_connection *conn) {
    if(conn==NULL) {
        return Send(s,len);
    }

    int fd=((paroc_connection_sock *)conn)->sockfd;

    if(fd<0) {
        return -1;
    }

    int n=0;
    int count=0;
    while(len>0) {
#ifndef __WIN32__
        n=write(fd,s,len);//vanhieu.nguyen
#else
        n=send(fd,s,len,0);
#endif
        if(n>0) {
            count+=n;
            s+=n;
            len-=n;
        } else if(errno!=EINTR) {
            break;
        }
    }
    return count;
}

int paroc_combox_socket::Recv(char *s,int len) {
    int fd, n;
    isCanceled=false;
    do {
        paroc_connection_sock *t=(paroc_connection_sock *)Wait();
        if(t==NULL) {
            return -1;
        }

        fd=t->sockfd;
#ifndef __WIN32__
        while((n=read(fd,s,len))==-1 && errno==EINTR);
#else
        while((n=read(fd,s,len))==-1 && GetLastError()== WSAEINTR);
#endif
        if(n<=0) {
            if(CloseSock(fd)) {
                continue;
            }

            return -1;
        }
    } while(n<=0);

    if(!n) {
        errno=EIO;
    }

    return n;
}

int paroc_combox_socket::Recv(char *s,int len, paroc_connection *iopeer) {
    int fd, n;
    paroc_connection_sock *t;
    isCanceled=false;

    do {
        if(!iopeer) {
            t=(paroc_connection_sock *)Wait();
            if(!t) {
                return -1;
            }

            fd=t->sockfd;
        } else {
            fd=((paroc_connection_sock *)iopeer)->sockfd;
        }

        if(fd<0) {
            return -1;
        }

#ifndef __WIN32__
        while((n=read(fd,s,len))<0 && errno==EINTR);
#else
        while((n=recv(fd,s,len,0))<0 && GetLastError()== WSAEINTR);
#endif

#ifndef __WIN32__
        if(n==0){
            if(CloseSock(fd) && iopeer==NULL) {
                continue;
            }

            return -1;
        }
#else
        if(GetLastError()==WSAECONNRESET){
            if(CloseSock(fd) && iopeer==NULL) {
                continue;
            }

            return -1;
        }
#endif
    } while(n<=0);

    if(!iopeer) {
        iopeer=t;
    }

    if(n<=0) {
        errno=EIO;
    }

    return n;
}

//TODO This function's code is simply terrible, the windows and linux part
//must be separated completely
paroc_connection* paroc_combox_socket::Wait() {
#ifdef __WIN32__
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    int tmpfdset;
#endif
    if(sockfd<0 || isCanceled) {
        isCanceled=false;
        return NULL;
    }

    if(isServer) {
#ifndef __WIN32__
        pollfd *tmpfd;
#endif
        while(1) {
            if(nready>0) {
#ifndef __WIN32__
                int n=pollarray.GetSize();
                tmpfd=pollarray+index;
                for(int i=index; i>=0; i--, tmpfd--) {
                    if(tmpfd->revents!=0) {
                        nready--;
                        index=i-1;
                        tmpfd->revents=0;
#else
                FD_ZERO(&readfds);
                readfds = activefdset;
                int n = readfds.fd_count;
                for(int i=n-1; i>=0; i--) {
                    if(readfds.fd_array[i] == tmpfdset) {
                        nready--;
#endif
                        if(i==0) {
                            //Accept new connection....
                            sockaddr addr;
                            socklen_t addrlen=sizeof(addr);
                            int s;
#ifndef __WIN32__
                            while((s=popc_accept(sockfd,&addr,&addrlen))<0 && errno==EINTR);
#else
                            while((s=popc_accept(sockfd,&addr,&addrlen))<0 && GetLastError()== WSAEINTR);
#endif
                            if(s<0) {
                                return NULL;
                            }
#ifndef __WIN32__
                            pollarray.SetSize(n+1);
                            pollarray[n].fd=s;
                            pollarray[n].events=POLLIN;
                            pollarray[n].revents=0;
                            connarray.SetSize(n+1);
                            connarray[n]=CreateConnection(s);
                            bool ret=OnNewConnection(connarray[n]);
                            n++;
#else
                            for(int j = 0; j < readfds.fd_count; j++)
                                if(readfds.fd_array[j] < s) {
                                    highsockfd = s;
                                }

                            FD_SET(s, &activefdset);

                            connarray.SetSize(activefdset.fd_count);
                            connarray[activefdset.fd_count-1]=CreateConnection(s);
                            bool ret=OnNewConnection(connarray[activefdset.fd_count-1]);
#endif
                            if(!ret) {
                                return NULL;
                            }
                        } else {
                            return connarray[i];
                        }
                    }
                }
            }

            //Poll for ready fds....
            do {
#ifndef __WIN32__
                tmpfd=pollarray;
                int n=pollarray.GetSize();
                index=n-1;
                nready=poll(tmpfd,n,timeout);
#else
                FD_ZERO(&readfds);
                readfds = activefdset;
                int n = readfds.fd_count;

                timeval tv;
                if(timeout < 0) {
                    tv.tv_sec = 1000000;
                } else {
                    tv.tv_sec = timeout / 1000;
                    tv.tv_usec = timeout % 1000;
                }

                nready = select(highsockfd+1, &readfds, (fd_set *)0, (fd_set *)0, &tv);
                for(int tmp = 0; tmp < n; tmp++) {
                    if(FD_ISSET(readfds.fd_array[tmp], &readfds)) {
                        tmpfdset = readfds.fd_array[tmp];
                    }
                }
#endif
            }  while(nready<0 && errno==EINTR && sockfd>=0);

            if(nready<=0) {
                if(nready==0) {
                    errno=ETIMEDOUT;
                }
                return NULL;
            }
        }
    } else {
        if(timeout>=0) {
            int t;
#ifndef __WIN32__
            pollfd tmpfd;
            tmpfd.fd=sockfd;
            tmpfd.events=POLLIN;
            tmpfd.revents=0;
            while((t=poll(&tmpfd,1,timeout))==-1 && errno==EINTR);
#else
            fd_set tempfds;
            FD_ZERO(&tempfds);
            highsockfd = sockfd;
            FD_SET(sockfd, &tempfds);
            timeval tv;
            tv.tv_sec = timeout / 1000;
            tv.tv_usec = timeout % 1000;

            while((t=select(highsockfd+1, &tempfds, (fd_set *)0, (fd_set *)0, &tv))==-1 && GetLastError()== WSAEINTR);
#endif
            if(t<=0) {
                if(t==0) {
                    errno=ETIMEDOUT;
                }
                return NULL;
            }
        }
        return peer;
    }
}

void paroc_combox_socket::Close() {
    int fd=sockfd;
#ifdef __WIN32__
    highsockfd = -1;
#endif
    sockfd=-1;
    nready=0;
    index=-1;

    if(isServer) {
#ifndef __WIN32__
        int n=pollarray.GetSize();
        for(int i=0; i<n; i++) if(fd!=pollarray[i].fd) {
                OnCloseConnection(connarray[i]);
            }
        for(int i=0; i<n; i++) {
            popc_close(pollarray[i].fd);
        }
        pollarray.RemoveAll();
#else
        int n=activefdset.fd_count;
        for(int i=0; i<n; i++) if(fd!=activefdset.fd_array[i]) {
                /*FD_CLR(activefdset.fd_array[i], &activefdset);*/OnCloseConnection(connarray[i]);
            }
        FD_ZERO(&activefdset);
        FD_ZERO(&readfds);
#endif

        for(int i=0; i<n; i++) {
            delete connarray[i];
        }
        connarray.RemoveAll();
    } else {
        if(peer!=NULL) {
            OnCloseConnection(peer);
            delete peer;
            peer=NULL;
        }

        if(fd>=0) {
            popc_close(fd);
        }
    }
}

bool paroc_combox_socket::GetProtocol(POPString & protocolName) {
    protocolName="socket";
    return true;
}

bool paroc_combox_socket::GetUrl(POPString & accesspoint) {
    POPString prot;
    GetProtocol(prot);
    int port=GetPort();
    char elem[1024];

    sprintf(elem,"%s://%s:%d",(const char *)prot,(const char*)paroc_system::GetHost(),port);
    accesspoint=elem;
    return true;
}

bool paroc_combox_socket::CloseSock(int fd) {
    if(isServer) {
#ifndef __WIN32__
        int n=pollarray.GetSize();
        pollfd *t=pollarray;
        for(int i=0; i<n; i++, t++) if(t->fd==fd)
#else
        int n = activefdset.fd_count;
        for(int i=0; i<n; i++) if(activefdset.fd_array[i]==fd)
#endif
            {
                isCanceled=!OnCloseConnection(connarray[i]);
                delete connarray[i];
                connarray.RemoveAt(i);
#ifdef __WIN32__
                FD_CLR(activefdset.fd_array[i], &activefdset);
#else
                pollarray.RemoveAt(i);
                if(isCanceled) {
                    errno=ECANCELED;
                }
#endif
                popc_close(fd);
                return !isCanceled;
            }
    } else if(peer!=NULL && fd==sockfd) {
        isCanceled=true;
        popc_close(fd);
        sockfd=-1;
        return true;
    }
    return false;
}

bool paroc_combox_socket::Connect(const char *host,int port) {
    hostent *phe;
    sockaddr_in sin;
#ifdef __WIN32__
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    memset((char *)&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    if((phe=gethostbyname(host)) !=NULL) {
        memcpy((char *)&sin.sin_addr,phe->h_addr,phe->h_length);
    } else if(static_cast<int>((sin.sin_addr.s_addr=popc_inet_addr(host)))==-1) {
        return false;
    }

    sin.sin_port=popc_htons(port);

    if(timeout<=0) {
        return (popc_connect(sockfd,(sockaddr*)&sin,sizeof(sin))==0);
    } else {
#ifndef __WIN32__
        int flag=fcntl(sockfd,F_GETFL,0);
        int newflag=flag | O_NONBLOCK;
        fcntl(sockfd,F_SETFL,newflag);
#else
        unsigned long ul = 1;
        ioctlsocket(sockfd, FIONBIO, &ul);
#endif
        int ret=popc_connect(sockfd,(sockaddr*)&sin,sizeof(sin));
        int err=errno;
#ifndef __WIN32__
        if(ret==-1 && errno==EINPROGRESS) {
            int t;
            struct pollfd me;
            me.fd=sockfd;
            me.events=POLLOUT;
            me.revents=0;
            //Linux: poll function
            while((t=poll(&me,1,timeout))==-1 && errno==EINTR);
#else
        if(ret==-1 /*&& GetLastError()== WSAEINPROGRESS*/) {
            fd_set tmpwritefds;
            FD_ZERO(&tmpwritefds);
            FD_SET(sockfd, &tmpwritefds);
            int t;
            timeval tv;
            tv.tv_sec = timeout / 1000;
            tv.tv_usec = timeout % 1000;

            //Win: select function
            while((t=select(sockfd+1, (fd_set *)0, &tmpwritefds, (fd_set *)0, &tv))==-1 && GetLastError()== WSAEINTR);
#endif
            if(t!=1) {
                err=ETIMEDOUT;
            } else {
                socklen_t len=sizeof(int);
                if(GetOpt(SOL_SOCKET,SO_ERROR,(char *)(&err),len)==0) {
                    if(err==0) {
                        ret=0;
                    }
                } else {
                    err=errno;
                }
            }
        }
#ifndef __WIN32__
        //Linux:fcntl function
        fcntl(sockfd,F_SETFL,flag);
#else
        //Win:ioctlsocket function
        ul = 0;
        ioctlsocket(sockfd, FIONBIO, &ul);
#endif

        if(ret!=0) {
            errno=err;
        }
        return (ret==0);
    }
}


int paroc_combox_socket::GetSockInfo(sockaddr &info,socklen_t &len) {
    return popc_getsockname(sockfd,&info,&len);
}

int paroc_combox_socket::GetPort() {
    sockaddr_in sin;
    socklen_t len=sizeof(sin);
    GetSockInfo((sockaddr &)sin, len);
    return popc_ntohs(sin.sin_port);
}

int paroc_combox_socket::GetOpt(int level, int opt, char *buf, socklen_t &len) {
    return popc_getsockopt(sockfd,level,opt,buf,&len);
}
int paroc_combox_socket::SetOpt(int level, int opt, char *buf, socklen_t len) {
    return setsockopt(sockfd,level,opt,buf,len);
}

paroc_connection_sock *paroc_combox_socket::CreateConnection(int fd) {
    return new paroc_connection_sock(fd, this);
}
