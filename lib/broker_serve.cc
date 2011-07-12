#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include "paroc_broker.h"
#include "paroc_interface.h"
#include "paroc_event.h"

#include "objectmonitor.ph"
#include "paroc_thread.h"


#define PROPAGATE_EXCEPTION(a)  catch (a err) { if (peer!=NULL) paroc_buffer::SendException(buf, peer, err);  else rprintf("Unhandled exception occurs on %s@%s/%d:%d\n", (const char *)classname,accesspoint.GetAccessString(), methodid[0], methodid[1]); }

// #define PROPAGATE_EXCEPTION(a, id)  catch (a err) { if (methodid[2] & INVOKE_SYNC) {\
//     buf.Reset();\
//     buf.SetType(TYPE_EXCEPTION);\
//     int type=id;\ 
//     buf.Pack(&type,1);\
//     buf.Pack(&err,1); \
//     buf.Send(*peer); }\
//     else rprintf("Unhandled exception occurs on %s@%s/%d:%d\n",classname,accesspoint.GetAccessString(), methodid[0], methodid[1]); }

// #define TRANSMIT_EXCEPTION(name,type,buf,comm)  { buf.Reset();\
//     buf.SetType(TYPE_EXCEPTION);\
//     int t=type;\ 
//     buf.Pack(&t,1);\
//     buf.Pack(name,1); \
//     buf.Send(comm); }


bool paroc_broker::GetRequest(paroc_request &req)
{
  execCond.lock();
  //If the queue is empty then wait for the request....
  while (request_fifo.IsEmpty())
    {
      if ((obj!=NULL && obj->GetRefCount()<=0) || state!=PAROC_STATE_RUNNING)
	{
	  execCond.unlock();
	  return false;
	}
      execCond.wait(); //Wait for new request
    }
  
  POSITION pos=request_fifo.GetHeadPosition();
  req=request_fifo.GetAt(pos);
  request_fifo.RemoveHead();

  //Top request is of type mutex
  if (req.methodId[2] & INVOKE_MUTEX) 
    {
      while (instanceCount>0)
	{
	  execCond.wait();
	}
    }
  execCond.unlock();
  return true;
}

void paroc_broker::ServeRequest(paroc_request &req)
{
  int type=req.methodId[2];
  DoInvoke(req.methodId,*req.data,req.from);
  if (type & INVOKE_MUTEX) 
    {
      mutexCond.lock();
      mutexCount--;
      if (mutexCount==0) mutexCond.broadcast();
      mutexCond.unlock();
    }  
  req.data->Destroy();
  if (req.from!=NULL) delete req.from;
}

bool paroc_broker::DoInvoke(unsigned methodid[3], paroc_buffer &buf, paroc_connection *peer)
{
    try 
    {
      if (!Invoke(methodid, buf, peer) )  paroc_exception::paroc_throw(OBJECT_MISMATCH_METHOD);
    }
    
    PROPAGATE_EXCEPTION(int)
    PROPAGATE_EXCEPTION(unsigned)
      
    PROPAGATE_EXCEPTION(long)
    PROPAGATE_EXCEPTION(unsigned long)

    PROPAGATE_EXCEPTION(short)
    PROPAGATE_EXCEPTION(unsigned short)

    PROPAGATE_EXCEPTION(bool)

    PROPAGATE_EXCEPTION(char)
    PROPAGATE_EXCEPTION(unsigned char)

    PROPAGATE_EXCEPTION(float)
    PROPAGATE_EXCEPTION(double)

    PROPAGATE_EXCEPTION(paroc_interface)

    PROPAGATE_EXCEPTION(char *) 
    catch (paroc_exception *e)
      {
	if ((methodid[2] & INVOKE_SYNC) && peer!=NULL)
	  {
	    paroc_string &extra=e->Extra();
	    if (extra==NULL) extra=classname+"@"+accesspoint.GetAccessString();
	    paroc_buffer::SendException(buf,peer,*e);
	  }
	else 
	  {
	    rprintf("Unhandled exception occurs on %s@%s/%d:%d (extra=%s, code=%d)\n", (const char *)classname,accesspoint.GetAccessString(), methodid[0], methodid[1], (const char *)e->Extra(), e->Code());

	  }
	delete e;
      }    
      
    catch (...)
      {
	if (peer!=NULL)
	  {
	    paroc_exception  *e=paroc_exception::create(UNKNOWN_EXCEPTION);
	    paroc_string &extra=e->Extra();
	    extra=classname+"@"+accesspoint.GetAccessString();
	    paroc_buffer::SendException(buf, peer, *e);
	    delete e;
	  }
	else
	  {
	    rprintf("Unhandled exception occurs on %s@%s/%d:%d\n", (const char *)classname,accesspoint.GetAccessString(), methodid[0], methodid[1]);
	  }
      }

    if (obj==NULL || obj->GetRefCount()<=0)
    {
	return false;	      
    }
    return true;
}



