#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include "paroc_combox_http.h"
#include "paroc_system.h"

/*
BEGIN PLUGIN 
 */

extern "C" {
  int LoadProtocol(paroc_string &name, COMBOX_CREATOR &creator);
}

paroc_combox *paroc_http_creator()
{
  return new paroc_combox_http;
}

int LoadProtocol(paroc_string &name, COMBOX_CREATOR &creator)
{
  name="http";
  creator=paroc_http_creator;
  return 0;
}

/*
END PLUGIN
 */

http_conn_cookie::http_conn_cookie()
{
  ref=1;
  fact=NULL;
}

 http_conn_cookie & http_conn_cookie::operator =(http_conn_cookie &x)
{
  cookie=x.cookie;
  fact=x.fact;
  ref=x.ref;
  return *this;
}


  
paroc_connection_http::paroc_connection_http(paroc_combox *cb): paroc_connection_sock(cb)
{
  isChunkRecv=isChunkSend=false;

  closeConnection=reconnect=false;
  sendHeader=true;
  messageLen=0;
  myfile="";
  myhost="";
  connref=NULL;
}

paroc_connection_http::paroc_connection_http(int fd, paroc_combox *cb): paroc_connection_sock(fd, cb)
{
  isChunkRecv=isChunkSend=false;
  closeConnection=reconnect=false;
  sendHeader=true;
  messageLen=0;
  myfile="";
  myhost="";
  connref=NULL;
}

paroc_connection_http::paroc_connection_http(paroc_connection_http &me): paroc_connection_sock(me)
{
  isChunkRecv=me.isChunkRecv;
  isChunkSend=me.isChunkSend;

  closeConnection=me.closeConnection;
  reconnect=me.reconnect;

  sendHeader=me.sendHeader;
  messageLen=me.messageLen;
  myfile=me.myfile;
  myhost=me.myhost;
  connref=NULL;

  SetRef(me.GetRef());
}

paroc_connection_http::~paroc_connection_http()
{
  if (connref!=NULL) connref->ref--;
}



paroc_connection *paroc_connection_http::Clone()
{
  return new paroc_connection_http(*this);
}


http_conn_cookie *paroc_connection_http::GetRef()
{
  return connref;
}

void paroc_connection_http::SetRef(http_conn_cookie *x)
{
  if (connref!=NULL) connref->ref--;
  if (x!=NULL) x->ref++;
  connref=x;
}

void paroc_connection_http::SetBufferFactory(paroc_buffer_factory *fact)
{
  if (connref!=NULL) connref->fact=fact;
  else paroc_connection_sock::SetBufferFactory(fact);
}

paroc_buffer_factory *paroc_connection_http::GetBufferFactory()
{
  if (connref!=NULL && connref->fact!=NULL) return connref->fact;
  else return paroc_connection_sock::GetBufferFactory(); 
}

//COMBOX IMPLEMENTATION


paroc_combox_http::paroc_combox_http()
{
  cookie_count=0;
  signal(SIGPIPE, SIG_IGN);
}

paroc_combox_http::~paroc_combox_http()
{
  Close();
}

bool paroc_combox_http::Connect(const char *url)
{

  if (url==NULL)
    {
      errno=EDESTADDRREQ;
      return false;
    }

  char *host;
  const char searchPattern[]="http://";
  char * searchResult;
  if(searchResult=strstr(url, searchPattern))
    {
      host=strdup(searchResult+7);
    }
  else
    {
      host=strdup(url);
    }

  char *s=strchr(host,':');
  char *slash=strchr(host,'/');
  int port;
  paroc_string myfile;
  
  if (slash!=NULL)
    {
      myfile=slash;
      if (slash<s)
	{
	  s=NULL;
	  *slash=0;
	}
    }
  else myfile="/";

  if (s==NULL) port=80;
  else if (sscanf(s+1,"%d",&port)!=1)
  {
     free(host);
     return false;
  }
  else *s=0;

  paroc_string myhost=host;
  if (port!=80) 
    {
      char tmp[32];
      sprintf(tmp,":%d", port);
      myhost+=tmp;
    }

  //DEBUG("try to connect to host:%s with port:%d", host, port);
  
  char tmpurl[10240];
  sprintf(tmpurl,"%s:%d", host, port);

  free(host);
  
  if (paroc_combox_socket::Connect(tmpurl))
    {
      paroc_connection_http *t=(paroc_connection_http *)peer;
      char *str=strstr(myfile.GetString(),"?url=");

      t->myhost=myhost;

      if (str==NULL)
	{
	  t->myhost=myhost;
	  t->myfile=myfile;
	  //	  DEBUG("HOST=%s ; FILE=%s",(const char *)t->myhost, (const char *)t->myfile);
	}
      else
	{
	  str+=5;
	  t->myfile=str;

	  if (strncmp(str, "http://",7)==0) str+=7;
 	  char *str1=strchr(str,'/');
 	  if (str1!=NULL)
 	    {
	      // 	      t->myfile=str1;
 	      *str1=0;
 	    }
	  // 	  else t->myfile="/";
 	  t->myhost=str;
	  //	  DEBUG("HOST=%s ; FILE=%s",(const char *)t->myhost, (const char *)t->myfile);
	}
      int len=t->myfile.Length()-1;
      if (t->myfile[len]!='/') t->myfile+="/";
      myurl=url; 
      return true;
    }
  return false;
 }

int paroc_combox_http::Send(const char *s,int len)
{
  if (peer==NULL) return -1;
  return Send(s,len,peer);
}

int paroc_combox_http::Send(const char *s,int len, paroc_connection *conn)
{
  if (len<=0) return 0;
  if (conn==NULL) conn=peer;

  if (conn==NULL) return -1;
  paroc_connection_http *http=(paroc_connection_http *)conn;

  if (http->sendHeader)
    {
      if (!SendHeader(http,len )) return -1;
    }

  if (http->isChunkSend)
    {
      char str[256];
      sprintf(str,"%x\r\n",len);
      int t=strlen(str);
      if (paroc_combox_socket::Send(str,t, conn)!=t) 
	{
	  if (!isServer && ReConnect())
	    {
	      http->sendHeader=true;
	      return Send(s, len, conn);
	    } 
	  return -1;
	}
    }

  if (paroc_combox_socket::Send(s,len, conn)==len) 
    {
      FinalizeSend(http);
      return len;
    }
  else 
    {
      if (!isServer && ReConnect())
	{
	  http->sendHeader=true;
	  return Send(s, len, conn);
	} 
      return -1;
    }
}

bool paroc_combox_http::SendAck(paroc_connection *conn)
{
  if (conn==NULL) return false;
  SendHeader((paroc_connection_http *)conn, 0);
}

int paroc_combox_http::Recv(char *s,int len)
{
  paroc_connection *conn=NULL;
  return Recv(s,len,conn);
}

int paroc_combox_http::Recv(char *s,int len, paroc_connection *&iopeer)
{
  if (len<=0) return 0;
  paroc_connection_http *conn;
  bool shouldSend=true;
  while (1)
    {
      if (iopeer==NULL)
	{
	  if (shouldSend)
	    {
	      int n=connarray.GetSize()-1;
	      while (n>0)
		{
		  conn=(paroc_connection_http *)connarray[n];
		  FinalizeSend(conn);
		  n--;
		}
	      shouldSend=false;
	    }
	  conn=(paroc_connection_http *)Wait();
	  if (conn==NULL) return -1;
	}
      else
	{
	  conn=(paroc_connection_http *)iopeer;
	  if (shouldSend)
	    {
	      shouldSend=false;
	      if (!FinalizeSend(conn)) return -1;
	    }
	}


      if (conn->messageLen<=0)
	{
	  if (conn->isChunkRecv)
	    {
	      if (!ReadChunkSize(conn))
		{
		  if (iopeer==NULL && !isCanceled) continue;
		  return -1;
		}
	    }
	  if (conn->messageLen<=0)
	    {
	      if (!RecvHeader(conn))
		{
		  if (iopeer==NULL && !isCanceled) continue;
		  return -1;
		}
	    }
	  if (conn->messageLen<=0)
	    {
	      if (iopeer==NULL) continue;
	      return conn->messageLen;
	    }
	      
	}

      if (len>conn->messageLen) len=conn->messageLen;

      paroc_connection *t=conn;
      int sz=paroc_combox_socket::Recv(s , len ,t);
      if (sz<=0 && iopeer==NULL && !isCanceled) continue;

      if (sz>0)
	{
	  conn->messageLen-=sz;
	  if (iopeer==NULL) iopeer=conn;
	}
      return sz;
    }
}

bool paroc_combox_http::RecvAck(paroc_connection *conn)
{
  if (conn==NULL) return false;
  RecvHeader((paroc_connection_http *)conn);
}

paroc_connection *paroc_combox_http::Wait()
{
  if (isServer)
    {
      while (1)
	{
	  paroc_connection_http *http=( paroc_connection_http *)paroc_combox_socket::Wait();
	  if (http!=NULL && http->GetRef()==NULL)
	    {
	      if (RecvHeader(http)) return http;
	      else if (isCanceled) return NULL;
	      continue;
	    }
	  return http;
	}
    }
  else
    return paroc_combox_socket::Wait();
  
}

void paroc_combox_http::Close()
{
  if (!isServer && peer!=NULL)
    {
      paroc_connection_http *conn=(paroc_connection_http *)peer;
      http_conn_cookie *ref=conn->GetRef();

      if (ref!=NULL)
	{
	  conn->closeConnection=true;
	  //	  DEBUG("Send close request");
	  SendHeader(conn,0);
	}
    }
  paroc_combox_socket::Close();
}


bool paroc_combox_http::GetProtocol(paroc_string & protocolName)
{
  protocolName="http";
}

bool paroc_combox_http::GetUrl(paroc_string & accesspoint)
{
  char *gateway=getenv("PAROC_HTTP_PROXY");
  if (gateway!=NULL)
    {
      paroc_string str;
      if (!paroc_combox_socket::GetUrl(str)) return false;
      if (strncmp(gateway,"http://",7)==0) accesspoint=gateway;
      else 
	{
	  accesspoint="http://";
	  accesspoint+=gateway;
	}
      accesspoint+="/?url=";
      accesspoint+=str;
      return true;
    }
  else return paroc_combox_socket::GetUrl(accesspoint);
}



paroc_connection_sock *paroc_combox_http::CreateConnection(int fd)
{
  return new paroc_connection_http(fd, this);
}

bool paroc_combox_http::RecvHeader(paroc_connection_http *conn)
{

  char tmpdata;
  int sz=0;
  bool done=false;
  paroc_connection *tmpconn=conn;

  char header[1024];

  bool firstline=true;
  bool transfer=false;
  bool contentlen=false;

  http_conn_cookie *cookieref=conn->GetRef();
  bool cookie=false;
  
  bool closed=false;

  int code=0;
  char value[1024];

  conn->isChunkRecv=false;
  

  while (!done)
    {
      if (!ReadLine(conn,header,1024)) return false;

      if (firstline)
	{
	  if (isServer)
	    {
	      char url[1024];
	      int count=sscanf(header,"%s %s",value,url);
	      if (count==2)
		{
		  if (strstr(url,"close=true")!=NULL)
		    {
		      //		      DEBUG("Request to close the connection");
		      conn->closeConnection=true;
		    }
		}
	    }
	  else
	    {
	      if (strncasecmp(header, "HTTP/1.",7)!=0  || sscanf(header+8,"%d", &code)!=1 || code!=200)
		{
		  CloseSock(conn->sockfd);
		  isCanceled=true;
		  return false;
		}
	    }
	  firstline=false;
	  continue;
	}
      else
	{
	  if (!closed)
	    {
	      char *tmp=NULL;
	      if (strncasecmp(header,"Connection",10)==0) tmp=header+10;
	      else if (strncasecmp(header,"Proxy-Connection",16)==0) tmp=header+16;
	      if (tmp!=NULL)
		{
		  while (isspace(*tmp) || *tmp==':') tmp++;
		  if (strncasecmp(tmp,"close", 4)==0) conn->reconnect=true;
		  closed=true;	      
		}
	    }

	  if (!transfer && strncasecmp(header,"Transfer-Encoding",17)==0)
	    {
	      char *tmp=header+17;
	      while (isspace(*tmp) || *tmp==':') tmp++;
	      if (strncasecmp(tmp,"chunked", 7)==0) conn->isChunkRecv=true;
	      transfer=true;
	    }

	  if (!contentlen && strncasecmp(header,"Content-Length",14)==0)
	    {
	      char *tmp=header+14;
	      while (isspace(*tmp) || *tmp==':') tmp++;
	      if (sscanf(tmp,"%d", &code)==1)
		{
		  conn->messageLen=code;
		}
	      else 
		{
		  DEBUG("Invalid content-length value");
		  CloseSock(conn->sockfd);
		  return false;	
		} 
	      contentlen=true;
	    }
	  if (!cookie && cookieref==NULL)
	    {
	      char *tmp=NULL;
	      
	      if (strncasecmp(header,"Set-Cookie",10)==0) tmp=header+10;
	      else if (strncasecmp(header,"Cookie",6)==0) tmp=header+6;
	      if (tmp!=NULL)
		{
		  while (isspace(*tmp) || *tmp==':') tmp++;
		  if (sscanf(tmp,"%s",value)==1)
		    {
		      char *t=strchr(value,';');
		      if (t!=NULL) *t=0;
		      cookieref=FindCookie(value);
		      if (cookieref==NULL)
			{
			  cookieref=CreateCookie();
			  cookieref->cookie=value;
			}
		      conn->SetRef(cookieref);
		    }
		  cookie=true;
		}
	    }

	  if (*header==0 || (*header=='\r' && *(header+1)==0)) done=true;
	}
    }

  if (conn->closeConnection)
    {
      CloseSock(conn->sockfd);
      return false;
    }

  conn->recvHeader=!(conn->isChunkRecv);
  if (cookieref==NULL && isServer)
    {
      conn->SetRef(CreateCookie());
      if (!OnNewConnection(conn))
	{
	  isCanceled=true;
	  return false;
	}
    }

  return true;
}

bool paroc_combox_http::ReadChunkSize(paroc_connection_http * conn)
{
  if (!conn->isChunkRecv) return false;
  //read next header
  char tmpdata=0;
  paroc_connection *tmpconn=conn;

  char header[1024];
  if (!ReadLine(conn,header,1024)) return false;

  int sz=0;
  if (sscanf(header,"%x",&sz)!=1) 
    {
      DEBUG("Can not read chunk size");
      CloseSock(conn->sockfd);
      return false;
    }
  else 
    {
      conn->messageLen=sz;
      conn->recvHeader=(sz<=0);
    }
  return true;
}

bool  paroc_combox_http::SendHeader(paroc_connection_http * conn, int msgsize)
{
  bool retry=true;
  if (!isServer && conn->reconnect)
    {
      if (!ReConnect()) return false;
      conn->reconnect=false;
      DEBUG("Reconnected");
      retry=false;
    }

  char buff[1024];
  char HTTPHeader[10240];
  char *pos=HTTPHeader;
  http_conn_cookie *cookieref=conn->GetRef();
  
  if(isServer) 
    {
      strcpy(pos,"HTTP/1.1 200 OK\r\n");
      pos+=strlen(pos);
      if (cookieref!=NULL)
	{
	  sprintf(pos,"Set-Cookie: %s;\r\n",(const char *)(cookieref->cookie));
	  pos+=strlen(pos);
	}
    }
  else
    {
      sprintf(pos, "POST %s%s HTTP/1.1\r\nHost: %s\r\n", (const char *)conn->myfile, conn->closeConnection? "?close=true" : "" , (const char *)conn->myhost);
      pos+=strlen(pos);
      if(cookieref!=NULL)
	{
	  sprintf(pos, "Cookie: %s\r\n", (const char *)(cookieref->cookie));
	  pos+=strlen(pos);
	}
    }
  if(conn->closeConnection)
    {
      strcpy(pos,"Connection: close\r\n");
    }
  else
    {
      strcpy(pos,"Connection: Keep-alive\r\nKeep-Alive: 300\r\n");
    }
  pos+=strlen(pos);
  conn->isChunkSend=(msgsize<0);
  conn->sendHeader=!(conn->isChunkSend);
  if (conn->isChunkSend)
   {
      strcpy(pos, "Transfer-Encoding: chunked\r\n\r\n");
    }
  else
    {
      sprintf(pos, "Content-Length: %d\r\n\r\n", msgsize);
    }


  int len=strlen(HTTPHeader);
  pos=HTTPHeader;
  
  if (isServer) return (paroc_combox_socket::Send(pos,len, conn)==len);
  else
    {
      while (1)
	{
	  if (paroc_combox_socket::Send(pos,len, conn)==len) return true;
	  if (retry)
	    {
	      retry=false;
	      if (!ReConnect()) return false;
	    }
	  else return false;
	}
    }
  return true;
 }

bool paroc_combox_http::ReadLine(paroc_connection *conn, char *aline, int sz)
{
  int n=1;
  while (n<sz)
    {
      if (paroc_combox_socket::Recv(aline,1,conn)<=0) return false;
      n++;
      if (*aline=='\n') break;
      aline++;
    }
  *aline=0;
  return true;
}

bool paroc_combox_http::FinalizeSend(paroc_connection_http *conn)
{
  if (!conn->sendHeader && conn->isChunkSend)
    {
      char str[]="0\r\n";
      conn->sendHeader=true;
      return (paroc_combox_socket::Send(str,3,conn)==3);
    }
  return true;
}

http_conn_cookie * paroc_combox_http::CreateCookie()
{
  char str[256];
  sprintf(str,"%d-%d",cookie_count++, time(NULL)); 
  http_conn_cookie &t=cookie_list.AddTailNew();
  t.cookie=str;
  t.fact=GetBufferFactory();
  return &t;
}

http_conn_cookie * paroc_combox_http::FindCookie(const paroc_string &cookie)
{
  if (cookie==NULL) return false;
  POSITION pos=cookie_list.GetHeadPosition();
  while (pos!=NULL)
    {
      http_conn_cookie &t=cookie_list.GetNext(pos);
      if (paroc_utils::isEqual(t.cookie, cookie)) return &t;
    }
  return NULL;
}


bool paroc_combox_http::RemoveCookie(const paroc_string &cookie)
{
  if (cookie==NULL) return false;
  POSITION pos=cookie_list.GetHeadPosition();
  while (pos!=NULL)
    {
      POSITION old=pos;
      http_conn_cookie &t=cookie_list.GetNext(pos);
      
      if (paroc_utils::isEqual(t.cookie, cookie))
	{
	  t.ref--;
	  if (t.ref<=0)
	    {
	      cookie_list.RemoveAt(old);
	    }
	  return true;
	}
      if (t.ref<=0) cookie_list.RemoveAt(old);
    }
  return false;
}



bool paroc_combox_http::OnNewConnection(paroc_connection *conn)
{
  //  DEBUG("HTTP OnNewConnection");
  paroc_connection_http *http=(paroc_connection_http *)conn;
  if (http->GetRef()==NULL) return true;
  return paroc_combox_socket::OnNewConnection(conn);
}

bool paroc_combox_http::OnCloseConnection(paroc_connection *conn)
{
  //  DEBUG("HTTP OnCloseConnection");
  paroc_connection_http *http=(paroc_connection_http *)conn;
  http_conn_cookie *cookieref=http->GetRef();
  if (!http->closeConnection || cookieref==NULL) return true;
  cookieref->ref--;
  if (RemoveCookie(cookieref->cookie))
    {
      return paroc_combox_socket::OnCloseConnection(conn);
    }
  return true;
}

bool paroc_combox_http::ReConnect()
{
  DEBUG("Try to reconnect....");
  if (!isServer && peer!=NULL)
    {
      paroc_connection_sock *old=peer;
      peer=NULL;
      Close();
      if (!Create(0, false) || !Connect(myurl))
	{
	  delete old;
	  return false;
	}
      old->sockfd=peer->sockfd;
      delete peer;
      peer=old;
      DEBUG("Reconnected");
    }
  return true;
}
