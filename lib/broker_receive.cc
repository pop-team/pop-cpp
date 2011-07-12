/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of parallel object broker: receive stuffs
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include "paroc_broker.h"
#include "paroc_interface.h"
#include "paroc_event.h"
#include "paroc_buffer_factory.h"
#include "paroc_buffer_factory_finder.h"

bool NewConnection(void *dat, paroc_connection *conn)
{
	paroc_broker *br=(paroc_broker *)dat;
	return br->OnNewConnection(conn);
}


bool CloseConnection(void *dat, paroc_connection *conn)
{
	paroc_broker *br=(paroc_broker *)dat;
	return br->OnCloseConnection(conn);
}


void paroc_broker::ReceiveThread(paroc_combox *server) // Receive request and put request in the FIFO
{
	server->SetCallback(COMBOX_NEW, NewConnection, this);
	server->SetCallback(COMBOX_CLOSE, CloseConnection, this);

	while (state==POPC_STATE_RUNNING)
	{
		paroc_request req;
		req.data=NULL;
		try
		{
			if (!ReceiveRequest(server, req)) break;

			if (ParocCall(req))
			{
				if (req.data!=NULL) req.data->Destroy();
				execCond.broadcast();
				continue;
			}
			RegisterRequest(req);
		}
		catch (...)
		{
			if (req.data!=NULL) req.data->Destroy();
			execCond.broadcast();
			break;

		}
	}
	server->Close();
}


bool paroc_broker::ReceiveRequest(paroc_combox *server, paroc_request &req)
{
	server->SetTimeout(-1);
	while (1)
	{
		paroc_connection *conn=server->Wait();
		if (conn==NULL)
		{
			execCond.broadcast();
			return false;
		}
		paroc_buffer_factory *fact=conn->GetBufferFactory();
		req.data=fact->CreateBuffer();
		if (req.data->Recv(conn))
		{
			req.from=conn;
			const paroc_message_header &h=req.data->GetHeader();
			req.methodId[0]=h.GetClassID();
			req.methodId[1]=h.GetMethodID();
			if ( !((req.methodId[2]=h.GetSemantics()) & INVOKE_SYNC) ) {
#ifdef OD_DISCONNECT
				if (checkConnection) {
					server->SendAck(conn);
				}
#endif
			}
			return true;
		}
		req.data->Destroy();
	}
	return false;
}


void paroc_broker::RegisterRequest(paroc_request &req)
{
	//Check if mutex is waiting/executing...
	int type=req.methodId[2];
	req.from=(type & INVOKE_SYNC)? req.from->Clone() : NULL;

	if (type & INVOKE_CONC)
	{
		mutexCond.lock();
		if (mutexCount<=0)
		{
			ServeRequest(req);
			mutexCond.unlock();
			return;
		}
	}
	else if (type & INVOKE_MUTEX)
	{
		mutexCond.lock();
		mutexCount++;
		mutexCond.unlock();
	}

	execCond.lock();
	request_fifo.AddTail(req);
	int count=request_fifo.GetCount();

	execCond.broadcast();
	execCond.unlock();

	if (type & INVOKE_CONC)
	{
		concPendings++;
		mutexCond.unlock();
	}

	if (count>=POPC_QUEUE_NORMAL)
	{
		//To many requests: Slowdown the reseive thread...
		int step=(count/POPC_QUEUE_NORMAL);
		long t=step*step*step;
		if (count>POPC_QUEUE_NORMAL+5) rprintf(" Warning: too many requests (unserved requests: %d)\n",count);
		if (count<=POPC_QUEUE_MAX) usleep(10*t);
		else
		{
			while (request_fifo.GetCount()>POPC_QUEUE_MAX) usleep(t*10);
		}
	}
}

bool paroc_broker::OnNewConnection(paroc_connection *conn)
{
	//  if (state!=POPC_STATE_RUNNING) return false;
	if (obj!=NULL) obj->AddRef();
	return true;
}

bool paroc_broker::OnCloseConnection(paroc_connection *conn)
{
	if (obj!=NULL)
	{
		int ret=obj->DecRef();
		if (ret<=0) execCond.broadcast();
	}
	return true;
	//(state==POPC_STATE_RUNNING);
}


paroc_object * paroc_broker::GetObject()
{
	return obj;
}

bool  paroc_broker::ParocCall(paroc_request &req)
{
	if (req.methodId[1]>=10) return false;

	unsigned *methodid=req.methodId;
	paroc_buffer *buf=req.data;

	switch (methodid[1])
	{
	case 0:
		//BindStatus call
		if (methodid[2] & INVOKE_SYNC)
		{
			paroc_buffer_factory *fact=req.from->GetBufferFactory();
			paroc_message_header h("BindStatus");
			buf->Reset();
			buf->SetHeader(h);
			int status=0;
			paroc_string enclist;
			paroc_buffer_factory_finder *finder=paroc_buffer_factory_finder::GetInstance();
			int count=finder->GetFactoryCount();
			for (int i=0;i<count;i++)
			{
				paroc_string t;
				if (finder->GetBufferName(i,t))
				{
					enclist+=t;
					if (i<count-1) enclist+=" ";
				}
			}
			buf->Push("code","int",1);
			buf->Pack(&status,1);
			buf->Pop();
			buf->Push("platform","paroc_string",1);
			buf->Pack(&paroc_system::platform,1);
			buf->Pop();

			buf->Push("info","paroc_string",1);
			buf->Pack(&enclist,1);
			buf->Pop();
			buf->Send(req.from);
		}
		break;
	case 1:
	{
		//AddRef call...
		if (obj==NULL) return false;
		int ret=obj->AddRef();
		if (methodid[2] & INVOKE_SYNC)
		{
			buf->Reset();
			paroc_message_header h("AddRef");
			buf->SetHeader(h);

			buf->Push("refcount","int",1);
			buf->Pack(&ret,1);
			buf->Pop();

			buf->Send(req.from);
		}
		execCond.broadcast();
	}
	break;
	case 2:
	{
		//DecRef call....
		if (obj==NULL) return false;
		int ret=obj->DecRef();
		if (methodid[2] & INVOKE_SYNC)
		{
			buf->Reset();
			paroc_message_header h("DecRef");
			buf->SetHeader(h);

			buf->Push("refcount","int",1);
			buf->Pack(&ret,1);
			buf->Pop();

			buf->Send(req.from);
		}
		execCond.broadcast();
		break;
	}


	case 3:
	{
		//GetEncoding call...
		paroc_string enc;
		buf->Push("encoding","paroc_string",1);
		buf->UnPack(&enc,1);
		buf->Pop();
		paroc_buffer_factory *fact=paroc_buffer_factory_finder::GetInstance()->FindFactory(enc);
		bool ret;
		if (fact!=NULL)
		{
			req.from->SetBufferFactory(fact);
			ret=true;
		}
		else ret=false;
		//  DEBUGIF(ret,"Set data encoding: %s",(const char *)enc);
		if (methodid[2] & INVOKE_SYNC)
		{
			paroc_message_header h("Encoding");
			buf->SetHeader(h);
			buf->Reset();
			buf->Push("result","bool",1);
			buf->Pack(&ret,1);
			buf->Pop();

			buf->Send(req.from);
		}
		break;
	}
	case 4:
	{
		//Kill call...
		if (obj!=NULL && obj->CanKill())
		{
			DEBUG("EXIT BY KILL NOW");
			exit(1);
			//      paroc_mutex_locker locker(execCond);
			//      state=POPC_STATE_ABORT;
			//      execCond.broadcast();
		}
		break;
	}
	case 5:
	{
		//ObjectAlive call
		if (obj==NULL) return false;
		if (methodid[2] & INVOKE_SYNC)
		{
			buf->Reset();
			paroc_message_header h("ObjectActive");
			buf->SetHeader(h);
			bool ret=(instanceCount || request_fifo.GetCount());
			buf->Push("result","bool",1);
			buf->Pack(&ret,1);
			buf->Pop();
			buf->Send(req.from);
		}

		break;
	}
#ifdef OD_DISCONNECT
	case 6:
	{
		//ObjectAlive call
		if (obj==NULL) return false;
		if (methodid[2] & INVOKE_SYNC)
		{
			buf->Reset();
			paroc_message_header h("ObjectAlive");
			h.SetClassID(0);
			h.SetMethodID(6);
			buf->SetHeader(h);
			buf->Send(req.from);
		}

		break;
	}
#endif
	default:
		return false;
	}
	return true;
}
