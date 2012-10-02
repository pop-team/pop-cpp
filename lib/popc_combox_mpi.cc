/**
 * @author 	Valentin Clement
 * @date		2012/09/25
 * @brief	Implementation of the combox using MPI Communication layer
 */


#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>


#include "popc_combox_mpi.h"




POPC_MPIConnection::POPC_MPIConnection(paroc_combox *cb): _hasCommunicator(false), paroc_connection(cb)
{
	signal(SIGPIPE, SIG_IGN);
}

POPC_MPIConnection::POPC_MPIConnection(POPC_MPIConnection &me): _hasCommunicator(false), paroc_connection(me.GetCombox(), me.GetBufferFactory())
{
  setCommunicator(me.getCommunicator());
}

/**
 * MPI Connection destructor. Free the communicator if it has been set. 
 */
POPC_MPIConnection::~POPC_MPIConnection(){
  if(hasCommunicator())
    _communicator.Free();
}

/**
 *
 */
paroc_connection *POPC_MPIConnection::Clone()
{
	return new POPC_MPIConnection(*this);
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
void POPC_MPIConnection::setCommunicator(MPI::Intercomm communicator)
{
 // printf("Set comm in connection\n");
/*  if(_hasCommunicator)
    _communicator.Disconnect();*/
  //printf("Set comm in connection ok\n");    
  _hasCommunicator = true;
  _communicator = communicator;
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
MPI::Intercomm POPC_MPIConnection::getCommunicator()
{
  return _communicator;
}

/**
 * Check if the communicator has been set
 * @return TRUE if the communicator is set. FALSE in any other cases. 
 */
bool POPC_MPIConnection::hasCommunicator()
{
  return _hasCommunicator;
}



/**
 * POPC_COMBOX_MPI IMPLEMENTATION
 */
 
const char* popc_combox_mpi::POPC_COMBOX_MPI_PROTOCOL_PREFIX = "mpi://"; 

popc_combox_mpi::popc_combox_mpi() : peer(NULL), index(0), nready(0), isCanceled(false), _isServer(false), _rank(-1), _hasCommunicator(false)
{
}

popc_combox_mpi::~popc_combox_mpi()
{
	Close();
}

bool popc_combox_mpi::hasCommunicator()
{
  return _hasCommunicator;
}

void popc_combox_mpi::setCommunicator(MPI::Intercomm comm)
{
  //printf("Set comm in combox\n");    
 /* if(_hasCommunicator)
    _communicator.Disconnect();*/
//  printf("Set comm in combox ok\n");        
  _communicator = comm;
  _hasCommunicator = true;
}

MPI::Intercomm popc_combox_mpi::getCommunicator()
{
  return _communicator;
}

bool popc_combox_mpi::Create(char* host, int port, bool server)
{

	Close(); 
	_isServer=server;

	printf("MPI Combox created: %s\n", (server)?"Server":"Client");

	if(server){
	  if(!MPI::Is_initialized()) {
  	  // Init MPI for multithread support
	  	int required_support = MPI_THREAD_MULTIPLE; // Required multiple thread support to allow multiple connection to an object
		  int provided_support = MPI::Init_thread(required_support);

		  // Get the inter-communicator to communicate with the parent process (Interface)
	  	static MPI::Intercomm parent = MPI::COMM_WORLD.Get_parent();
      
		}
			  
		if(host != NULL){
  		_port_name.append(host);			
		} else {
      // Open a port to be able to be contacted by interfaces
		  char port_name[MPI_MAX_PORT_NAME]; 		
		  MPI::Open_port(MPI_INFO_NULL, port_name);
		  _port_name.append(port_name);
		  int length = _port_name.length();
		  //parent.Send(&length, 1, MPI_INT, 0, 0);		
		  //parent.Send(port_name, strlen(port_name), MPI_CHAR, 0, 0);		
		  printf("MPI Communication enable\n"); 
		}
	}
	
	_rank = MPI::COMM_WORLD.Get_rank();
	
	

	/*protoent *ppe;
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
	else peer=CreateConnection(-1);*/
	
	
	return true;
}


/**
 * Connect with the saved port name
 * @return TRUE if the connection succeed, FALSE in any other cases
 */
bool popc_combox_mpi::reconnect()
{
  printf("Want to reconnect to %s\n", _port_name.c_str());  
  if(_port_name.length() > 0){

    MPI::Intercomm broker = MPI::COMM_WORLD.Connect(_port_name.c_str(), MPI_INFO_NULL, 0);
    printf("Connected to %s\n", _port_name.c_str());  
    if(peer == NULL)
      peer = new POPC_MPIConnection(this);
    peer->setCommunicator(broker);
    setCommunicator(broker);
    
    return true;
  } else {
    return false;
  }
}


bool popc_combox_mpi::Connect(const char *url)
{
  if (url == NULL) {
		errno=EDESTADDRREQ;
		return false;
	}
  
 	char *host;
	while (isspace(*url)) url++;

	const char searchPattern[] = "mpi://";
	char * searchResult;
	if (strncmp(url, "mpi://", 6) == 0){
		host = strdup(url+6);
	} else {
	  host = strdup(url);
	}

  //MPI::Intercomm broker = MPI::COMM_WORLD.Connect(host, MPI_INFO_NULL, 0);
  //printf("Connected to %s\n", host);
  _port_name.clear();
  _port_name.append(host);
  
  if(peer == NULL)
    peer = new POPC_MPIConnection(this);
  //peer->setCommunicator(broker);
  //setCommunicator(broker);
  
  delete [] host;

  return true;


	/*

	*s=0;
	bool ret= Connect(host,port);
	free(host);
	if (ret) peer->sockfd=sockfd;
	return ret;*/
}

int popc_combox_mpi::Send(const char *s, int length)
{
  if(peer == NULL) {
    return 0;
  }
    
	MPI::Intercomm communicator = peer->getCommunicator();  
  communicator.Send(s, length, MPI_CHAR, _rank, 0);	
	printf("MPICOM: sent smth: %d\n", length, s);    
	return 0;
}

int popc_combox_mpi::Send(const char *s, int length, paroc_connection *conn)
{
  if(conn == NULL)
    return Send(s, length);

	MPI::Intercomm communicator = ((POPC_MPIConnection*)conn)->getCommunicator();
  communicator.Send(s, length, MPI_CHAR, _rank, 0);	
	printf("MPICOM: sent smth: %d\n", length, s);  
/*	int fd=((paroc_connection_sock *)conn)->sockfd;
	if (fd<0) return -1;
	int n=0;

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
*/
	return 0;
}

int popc_combox_mpi::Recv(char *s, int length)
{
  if(peer == NULL) {
    return -1;
  }
  
  MPI::Status status;  
	MPI::Intercomm communicator = peer->getCommunicator();    
  communicator.Recv(s, length, MPI_CHAR, 0, 0, status);    
  
	return 0;
}

int popc_combox_mpi::Recv(char *s, int length, paroc_connection *&iopeer)
{
	MPI::Intercomm communicator;
	POPC_MPIConnection *connection;  
	
  if(iopeer == NULL && !hasCommunicator()){
    printf("IOpeer is null will wait for a conn\n");
    connection = (POPC_MPIConnection*)Wait();  
    if(connection == NULL)
      return -1;
    communicator = connection->getCommunicator();
    iopeer = connection;
  } else if(iopeer != NULL) {
    communicator = ((POPC_MPIConnection*)iopeer)->getCommunicator();
  } else {
    communicator = getCommunicator();
  }
	  
  MPI::Status status;
  communicator.Recv(s, length, MPI_CHAR, 0, 0, status);

	return 0;
}


paroc_connection* popc_combox_mpi::Wait()
{
  if(_port_name.length() <= 0) {
    return NULL;
  }
  
  
  
  // Receive interface connection to the MPI Combox
	if(_isServer){
	  if(hasCommunicator()){
	    POPC_MPIConnection *oldpeer = new POPC_MPIConnection(this);
	    oldpeer->setCommunicator(getCommunicator());
	    printf("MPICOM-SERVER: Giving old connection instead of new connection\n");
	    return oldpeer;
	  }
	    
		printf("MPICOM-SERVER: Waiting for client connection on %s\n", _port_name.c_str());
		
    // Wait for new connection
    MPI::Intercomm client = MPI::COMM_WORLD.Accept(_port_name.c_str(), MPI_INFO_NULL, 0);

		printf("MPICOM-SERVER: New client connected\n");

    // Create a new connection and set its communicator    
    POPC_MPIConnection *peer = new POPC_MPIConnection(this);
    peer->setCommunicator(client);  
    setCommunicator(client);
    return peer;
	} else {
	  return NULL;
	}
	
	
/*
	if (sockfd<0 || isCanceled)
	{
		isCanceled=false;
		return NULL;
	}

	if (_isServer)
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
	*/
	return NULL;
}

void popc_combox_mpi::Close()
{
  if(!MPI::Is_initialized() && _port_name.length() > 0) {
    _communicator.Free();
    printf("MPI-COM: Port is free\n");
    MPI::Close_port(_port_name.c_str());
  }
  
/*
	int fd=sockfd;
	sockfd=-1;
	nready=0;
	index=-1;

	if (_isServer)
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
	*/
}

/**
 * Get the protocol name for the MPI combox
 * @param Return "mpi" as the protocol name
 * @return TRUE in any cases
 */
bool popc_combox_mpi::GetProtocol(POPString& protocolName)
{
	protocolName="mpi";
	return true;
}


/**
 * Return the URL to access this combox. URL is formed like mpi://<port_name>
 * @param accesspoint Formed URL to access this combox under the form mpi://<port_name>
 * @return TRUE if the URL can be formed, FALSE in any other cases. 
 */
bool popc_combox_mpi::GetUrl(POPString& accesspoint)
{
  if(_port_name.length() <= 0)
    return false;
  
  // Form the URL with protocol and port_name  
  POPString protocol;
  GetProtocol(protocol);
  char url[1024];
  sprintf(url, "%s://%s", (const char*)protocol, _port_name.c_str());
  accesspoint = url;
	return true;
}

bool popc_combox_mpi::Connect(const char *host, int port)
{
/*
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
	*/
}

bool popc_combox_mpi::disconnect()
{
  printf("MPI-COMBOX: disconnected\n");
  if(_isServer){
    if(_hasCommunicator){
      _communicator.Free();
    }  
    _hasCommunicator = false;
  }
}

/**
 * Check if the combox is instantiated as a server side combox (can receive connection)
 * @return TRUE if the combox is a server-side combox. 
 */
bool popc_combox_mpi::is_server()
{
  return _isServer;
}


/**
 * TODO comment
 */
/*void popc_combox_mpi::SetPortName(const char* port_name){
	_port_name.clear();
	_port_name.append(port_name);
}*/

/*
popc_connection_mpi *popc_combox_mpi::CreateConnection()
{
	return new popc_connection_mpi(this);
}
*/
