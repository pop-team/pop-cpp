/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of the communication box for TCP/socket
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

#include "paroc_combox_socket.h"

#define PROTO_TCP 6
#define PROTO_UDP 17

paroc_connection_sock::paroc_connection_sock(paroc_combox *cb): paroc_connection(cb)
{
	sockfd=-1;
	signal(SIGPIPE, SIG_IGN);
}

paroc_connection_sock::paroc_connection_sock(int fd, paroc_combox *cb): paroc_connection(cb)
{
	sockfd=fd;
}

paroc_connection_sock::paroc_connection_sock(paroc_connection_sock &me): paroc_connection(me.GetCombox(), me.GetBufferFactory())
{
	sockfd=me.sockfd;
}

paroc_connection *paroc_connection_sock::Clone()
{
	return new paroc_connection_sock(*this);
}





paroc_combox_socket::paroc_combox_socket()
{
	peer=NULL;
	sockfd=-1;
	index=0;
	nready=0;
	isCanceled=false;
}

paroc_combox_socket::~paroc_combox_socket()
{
	Close();
}

bool paroc_combox_socket::Create(int port, bool server)
{
	Close();
	isServer=server;

	protoent *ppe;
	char prot[]="tcp";
	int type, protocol;
	char tmpbuf[2048];

	//THESE LINES OF CODE MAKE THEM LESS PORTABLE...
	protocol=PROTO_TCP;
//  if ( (ppe=getprotobyname(prot))==0) return false;
//  else protocol=ppe->p_proto;

	type= SOCK_STREAM;

	sockfd=socket(PF_INET,type,protocol);
	if (sockfd<0) return false;
	if (port>0)
	{
		sockaddr_in sin;
		memset(&sin,0,sizeof(sin));
		sin.sin_family=AF_INET;
		sin.sin_addr.s_addr=INADDR_ANY;
		sin.sin_port=htons(port);
		SetOpt(SOL_SOCKET,SO_REUSEADDR,(char*)&sin,sizeof(sin)); // lwk : Added this line to allow reuse an earlier socket with the same address
		if (bind(sockfd,(sockaddr *)&sin,sizeof(sin))!=0)
		{
			return false;
		}
	}
	if (server)
	{
		pollarray.SetSize(1);
		pollarray[0].fd=sockfd;
		pollarray[0].events=POLLIN;
		pollarray[0].revents=0;
		index=1;
		nready=0;
		connarray.SetSize(1);
		connarray[0]=CreateConnection(sockfd);
		return (listen(sockfd,10)==0);
	}
	else peer=CreateConnection(-1);
	return true;
}


bool paroc_combox_socket::Connect(const char *url)
{
	if (url==NULL)
	{
		errno=EDESTADDRREQ;
		return false;
	}

	char *host;
	while (isspace(*url)) url++;

	const char searchPattern[]="socket://";
	char * searchResult;
	if (strncmp(url,"socket://",9)==0)
	{
		host=strdup(url+9);
	}
	else
	{
		host=strdup(url);
	}

	char *s=strchr(host,':');
	int port;
	if (s==NULL || sscanf(s+1,"%d",&port)!=1)
	{
		free(host);
		return false;
	}
	*s=0;
	bool ret= Connect(host,port);
	free(host);
	if (ret) peer->sockfd=sockfd;
	return ret;
}

int paroc_combox_socket::Send(const char *s,int len)
{
	int n=0;
	int count=0;
	while (len>0)
	{
		n=write(sockfd,s,len);
		if (n>0)
		{
			count+=n;
			s+=n;
			len-=n;
		}
		else if (errno!=EINTR) break;
	}
	return count;
}

int paroc_combox_socket::Send(const char *s,int len, paroc_connection *conn)
{
	if (conn==NULL) return Send(s,len);

	int fd=((paroc_connection_sock *)conn)->sockfd;
	if (fd<0) return -1;
	int n=0;
	int count=0;
	while (len>0)
	{
		n=write(fd,s,len);
		if (n>0)
		{
			count+=n;
			s+=n;
			len-=n;
		}
		else if (errno!=EINTR) break;
	}
	return count;
}

int paroc_combox_socket::Recv(char *s,int len)
{
	int fd, n;
	isCanceled=false;
	do
	{
		paroc_connection_sock *t=(paroc_connection_sock *)Wait();
		if (t==NULL) return -1;

		fd=t->sockfd;
		while ((n=read(fd,s,len))==-1 && errno==EINTR);
		if (n<=0)
		{
			if (CloseSock(fd)) continue;
			return -1;
		}
	} while (n<=0);
	if (!n) errno=EIO;
	return n;
}

int paroc_combox_socket::Recv(char *s,int len, paroc_connection *&iopeer)
{
	int fd, n;
	paroc_connection_sock *t;
	isCanceled=false;

	do
	{
		if (iopeer==NULL)
		{
			t=(paroc_connection_sock *)Wait();
			if (t==NULL) return -1;
			fd=t->sockfd;
		}
		else
		{
			fd=((paroc_connection_sock *)iopeer)->sockfd;
		}
		if (fd<0) return -1;

		while ( (n=read(fd,s,len))<0 && errno==EINTR);
		if (n==0)
		{
			if (CloseSock(fd) && iopeer==NULL) continue;
			return -1;
		}
	} while (n<=0);

	if (iopeer==NULL) iopeer=t;
	if (n<=0) errno=EIO;
	return n;
}


paroc_connection* paroc_combox_socket::Wait()
{
	if (sockfd<0 || isCanceled)
	{
		isCanceled=false;
		return NULL;
	}

	if (isServer)
	{
		pollfd *tmpfd;
		while (1)
		{
			if (nready>0)
			{
				int n=pollarray.GetSize();
				tmpfd=pollarray+index;
				for (int i=index;i>=0;i--, tmpfd--) if (tmpfd->revents!=0)
					{
						nready--;
						index=i-1;
						tmpfd->revents=0;
						if (i==0)
						{
							//Accept new connection....
							sockaddr addr;
							socklen_t addrlen=sizeof(addr);
							int s;
							while ((s=accept(sockfd,&addr,&addrlen))<0 && errno==EINTR);
							if (s<0)
							{
								return NULL;
							}
							pollarray.SetSize(n+1);
							pollarray[n].fd=s;
							pollarray[n].events=POLLIN;
							pollarray[n].revents=0;
							connarray.SetSize(n+1);
							connarray[n]=CreateConnection(s);
							bool ret=OnNewConnection(connarray[n]);
							n++;
							if (!ret) return NULL;
						}
						else
							return connarray[i];
					}
			}

			//Poll for ready fds....
			do
			{
				tmpfd=pollarray;
				int n=pollarray.GetSize();
				index=n-1;
//	      DEBUG("STEP1: socket poll (addr=%p, size=%d, fd0=%d, timeout=%d)", tmpfd,n, tmpfd->fd, timeout);
				nready=poll(tmpfd,n,timeout);
//	      DEBUG("STEP1: socket poll returned (addr=%p, size=%d, nready=%d)", tmpfd,n, nready);
			}  while (nready<0 && errno==EINTR && sockfd>=0);

			if (nready<=0)
			{

				if (nready==0) errno=ETIMEDOUT;
				return NULL;
			}
		}
	}
	else
	{
		if (timeout>=0)
		{
			pollfd tmpfd;
			tmpfd.fd=sockfd;
			tmpfd.events=POLLIN;
			tmpfd.revents=0;
			int t;
			while ((t=poll(&tmpfd,1,timeout))==-1 && errno==EINTR);
			if (t<=0)
			{
				if (t==0) errno=ETIMEDOUT;
				return NULL;
			}
		}
		return peer;
	}
}

void paroc_combox_socket::Close()
{
	int fd=sockfd;
	sockfd=-1;
	nready=0;
	index=-1;

	if (isServer)
	{
		int n=pollarray.GetSize();
		for (int i=0;i<n;i++) if (fd!=pollarray[i].fd) OnCloseConnection(connarray[i]);

		for (int i=0;i<n;i++) close(pollarray[i].fd);
		for (int i=0;i<n;i++) delete connarray[i];
		pollarray.RemoveAll();
		connarray.RemoveAll();
	}
	else
	{
		if (peer!=NULL)
		{
			OnCloseConnection(peer);
			delete peer;
			peer=NULL;
		}
		if (fd>=0) close(fd);
	}
}

bool paroc_combox_socket::GetProtocol(paroc_string & protocolName)
{
	protocolName="socket";
	return true;
}

bool paroc_combox_socket::GetUrl(paroc_string & accesspoint)
{
	paroc_string prot;
	GetProtocol(prot);
	int port=GetPort();
	char elem[1024];

	sprintf(elem,"%s://%s:%d",(const char *)prot,(const char*)paroc_system::GetHost(),port);
	accesspoint=elem;
	return true;
}

bool paroc_combox_socket::CloseSock(int fd)
{
	if (isServer)
	{
		int n=pollarray.GetSize();
		pollfd *t=pollarray;
		for (int i=0;i<n;i++, t++) if (t->fd==fd)
			{
				isCanceled=!OnCloseConnection(connarray[i]);
				pollarray.RemoveAt(i);
				delete connarray[i];
				connarray.RemoveAt(i);
				close(fd);
				if (isCanceled) errno=ECANCELED;
				return !isCanceled;
			}
	}
	else if (peer!=NULL && fd==sockfd)
	{
		isCanceled=true;
		close(fd);
		sockfd=-1;
		return true;
	}
	return false;
}

bool paroc_combox_socket::Connect(const char *host,int port)
{
	hostent *phe;
	sockaddr_in sin;
	int s,type;
	char tmpbuf[2048];
	int herrno;

	memset((char *)&sin,0,sizeof(sin));
	sin.sin_family=AF_INET;
	if ( (phe=gethostbyname(host)) !=NULL)
		memcpy((char *)&sin.sin_addr,phe->h_addr,phe->h_length);
	else if ((sin.sin_addr.s_addr=inet_addr(host))==-1) return false;
	sin.sin_port=htons(port);

	if (timeout<=0)
	{
		return (connect(sockfd,(sockaddr*)&sin,sizeof(sin))==0);
	}
	else
	{
		int flag=fcntl(sockfd,F_GETFL,0);
		int newflag=flag | O_NONBLOCK;
		fcntl(sockfd,F_SETFL,newflag);
		int ret=connect(sockfd,(sockaddr*)&sin,sizeof(sin));
		int err=errno;
		if (ret==-1 && errno==EINPROGRESS)
		{
			struct pollfd me;
			me.fd=sockfd;
			me.events=POLLOUT;
			me.revents=0;
			int t;
			while ((t=poll(&me,1,timeout))==-1 && errno==EINTR);
			if (t!=1)
			{
				err=ETIMEDOUT;
			}
			else
			{
				socklen_t len=sizeof(int);
				if (GetOpt(SOL_SOCKET,SO_ERROR,(char *)(&err),len)==0)
				{
					if (err==0) ret=0;
				}
				else err=errno;
			}
		}
		fcntl(sockfd,F_SETFL,flag);
		if (ret!=0) errno=err;
		return (ret==0);
	}
}


int paroc_combox_socket::GetSockInfo(sockaddr &info,socklen_t &len)
{
	return getsockname(sockfd,&info,&len);
}

int paroc_combox_socket::GetPort()
{
	sockaddr_in sin;
	socklen_t len=sizeof(sin);
	GetSockInfo((sockaddr &)sin, len);
	return ntohs(sin.sin_port);
}

int paroc_combox_socket::GetOpt(int level, int opt, char *buf, socklen_t &len)
{
	return getsockopt(sockfd,level,opt,buf,&len);
}
int paroc_combox_socket::SetOpt(int level, int opt, char *buf, socklen_t len)
{
	return setsockopt(sockfd,level,opt,buf,len);
}

paroc_connection_sock *paroc_combox_socket::CreateConnection(int fd)
{
	return new paroc_connection_sock(fd, this);
}
