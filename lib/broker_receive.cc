/**
 * File : broker_receive.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of parallel object broker : receive stuffs
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 * P.Kuonen     March 2011      suppress warning message "too many requests"
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <iostream>
#include <fstream>

#include "paroc_broker.h"
#include "paroc_interface.h"
#include "paroc_event.h"
#include "paroc_buffer_factory.h"
#include "paroc_buffer_factory_finder.h"

bool NewConnection(void *dat, paroc_connection *conn)
{
  paroc_broker *br = (paroc_broker *)dat;
  return br->OnNewConnection(conn);
}


bool CloseConnection(void *dat, paroc_connection *conn)
{
  paroc_broker *br = (paroc_broker *)dat;
  return br->OnCloseConnection(conn);
}


/**
 * Receive request and put request in the FIFO
 */
void paroc_broker::ReceiveThread(paroc_combox *server)
{
	server->SetCallback(COMBOX_NEW, NewConnection, this);
	server->SetCallback(COMBOX_CLOSE, CloseConnection, this);

	while (state==POPC_STATE_RUNNING) {
	  server->disconnect();
	  printf("BROKER: %s waiting for request\n", classname.GetString());
    paroc_request request;
		request.data = NULL;
		try {
			if (!ReceiveRequest(server, request)) 
			  break;
    
			if (ParocCall(request)) {
				if (request.data != NULL) 
				  request.data->Destroy();
				execCond.broadcast();
				continue;
			}
			RegisterRequest(request);
		} catch (...) {
			if (request.data != NULL) 
			  request.data->Destroy();
			execCond.broadcast();
			break;
		}
	}
	server->Close();
}


bool paroc_broker::ReceiveRequest(paroc_combox *server, paroc_request &request)
{
	server->SetTimeout(-1);
	while (1) {
    paroc_connection* connection = server->Wait();
		
		if (connection == NULL) {
			execCond.broadcast();
			return false;
		}
		paroc_buffer_factory* bufferFactory = connection->GetBufferFactory();
		request.data = bufferFactory->CreateBuffer();
		
		
		if (request.data->Recv(connection)) {
			request.from = connection;
			const paroc_message_header &h = request.data->GetHeader();
			request.methodId[0] = h.GetClassID();
			request.methodId[1] = h.GetMethodID();
			if (!((request.methodId[2] = h.GetSemantics()) & INVOKE_SYNC) ) {
			
#ifdef OD_DISCONNECT
				if (checkConnection) {
					server->SendAck(conn);
				}
#endif

			}
			return true;
		}
		request.data->Destroy();
	}
	return false;
}


void paroc_broker::RegisterRequest(paroc_request &req)
{
  printf("BROKER: register request\n");
	//Check if mutex is waiting/executing...
	int type = req.methodId[2];
	req.from = (type & INVOKE_SYNC) ? req.from->Clone() : NULL;

	if (type & INVOKE_CONC) {
		mutexCond.lock();
		if (mutexCount <= 0) {
			ServeRequest(req);
			mutexCond.unlock();
			return;
		}
	} else if (type & INVOKE_MUTEX) {
		mutexCond.lock();
		mutexCount++;
		mutexCond.unlock();
	}

	execCond.lock();
	request_fifo.AddTail(req);
	int count = request_fifo.GetCount();

	execCond.broadcast();
	execCond.unlock();

	if (type & INVOKE_CONC) {
		concPendings++;
		mutexCond.unlock();
	}

	if (count >= POPC_QUEUE_NORMAL) {
      //To many requests: Slowdown the receive thread...
      int step = (count/POPC_QUEUE_NORMAL);
      long t = step*step*step;
      //if (count>POPC_QUEUE_NORMAL+5)
        //rprintf(" Warning: too many requests (unserved requests: %d)\n",count);
      if (count<=POPC_QUEUE_MAX) {
        usleep(10*t);
      } else {
        while (request_fifo.GetCount()>POPC_QUEUE_MAX) 
          usleep(t*10);
      }
	}
}

bool paroc_broker::OnNewConnection(paroc_connection *conn)
{
	if (obj != NULL) 
	  obj->AddRef();
	return true;
}

/**
 * This method is called when a connection with an interface is closed.
 */
bool paroc_broker::OnCloseConnection(paroc_connection *conn)
{
	if (obj != NULL) {
		int ret = obj->DecRef();
		if (ret <= 0) 
			execCond.broadcast();
	}
	return true;
}


paroc_object * paroc_broker::GetObject()
{
	return obj;
}

bool paroc_broker::ParocCall(paroc_request &req)
{
  printf("BROKER: Is ParocCall ? %d\n", req.methodId[1]);
	if (req.methodId[1] >= 10) 
	  return false;

	unsigned* methodid = req.methodId;
	paroc_buffer *buf = req.data;
  printf("BROKER: %s, PopCall %d // %d\n", classname.GetString(), methodid[1], methodid[2]);
	switch (methodid[1]) {
  	case 0: // BindStatus call
	  	if (methodid[2] & INVOKE_SYNC) {
  			paroc_buffer_factory *bufferFactory;
        bufferFactory = req.from->GetBufferFactory();
	  		paroc_message_header h("BindStatus");
		  	buf->Reset();
			  buf->SetHeader(h);
  			int status = 0;
	  		POPString enclist;
		  	paroc_buffer_factory_finder *finder = paroc_buffer_factory_finder::GetInstance();
			  int count = finder->GetFactoryCount();
  			for (int i = 0; i < count; i++) {
  				POPString t;
	  			if (finder->GetBufferName(i,t)) {
  					enclist += t;
	  				if (i < count-1) { 
	  				  enclist += " ";
	  				}
		  		}
			  }
			  
			  buf->Push("code", "int", 1);
  			buf->Pack(&status, 1);
	  		buf->Pop();
	  		
		  	buf->Push("platform", "POPString", 1);
			  buf->Pack(&paroc_system::platform, 1);
  			buf->Pop();

	  		buf->Push("info", "POPString", 1);
		  	buf->Pack(&enclist, 1);
			  buf->Pop();
			  
			  printf("BROKER: %s - ready to send paroc_call answer %s, %s\n", classname.GetString(), paroc_system::platform.GetString(), enclist.GetString());
  			buf->Send(req.from);
	  	}
		  break;
  	case 1:
	  {
		  //AddRef call...
  		if (obj == NULL) 
  		  return false;
	  	int ret = obj->AddRef();
		  if (methodid[2] & INVOKE_SYNC) {
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
  		if (obj == NULL) 
  		  return false;
	  	int ret = obj->DecRef();
		  if (methodid[2] & INVOKE_SYNC) {
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
		  // Negotiate encoding call
  		POPString enc;
	  	buf->Push("encoding", "POPString", 1);
		  buf->UnPack(&enc,1);
  		buf->Pop();
	  	paroc_buffer_factory *fact = paroc_buffer_factory_finder::GetInstance()->FindFactory(enc);
	  	printf("negotiate encoding ... %s\n", enc.GetString()); 
		  bool ret;
  		if (fact != NULL) {
  			req.from->SetBufferFactory(fact);
	  		ret = true;
		  } else { 
		    ret = false;
		  }
  		if (methodid[2] & INVOKE_SYNC) {
  			paroc_message_header h("Encoding");
	  		buf->SetHeader(h);
		  	buf->Reset();
			  buf->Push("result", "bool", 1);
  			buf->Pack(&ret, 1);
	  		buf->Pop();
	  		buf->Send(req.from);
		  }
  		break;
	  }
  	case 4:
	  {
		  //Kill call...
  		if (obj!=NULL && obj->CanKill()) {
  			DEBUG("EXIT BY KILL NOW");
	  		exit(1);
		  }
  		break;
	  }
  	case 5:
	  {
		  //ObjectAlive call
  		if (obj==NULL) 
  		  return false;
	  	if (methodid[2] & INVOKE_SYNC) {
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
  		if (obj==NULL) 
  		  return false;
	  	if (methodid[2] & INVOKE_SYNC) {
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
    case 7:
    {
      printf("BROKER: POPCall Disconnect\n");
//      server->Disconnect();
    }
  	default:
	  	return false;
	}
	return true;
}
