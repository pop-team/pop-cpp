/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of parallel object broker : receive requests.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_Broker instead of paroc_broker
 */

#include "popc_intface.h"

#include <iostream>
#include <fstream>

#include "paroc_broker.h"
#include "paroc_interface.h"
#include "paroc_event.h"
#include "pop_buffer_factory.h"
#include "pop_buffer_factory_finder.h"
#include "paroc_system.h"
#include "popc_logger.h"

bool NewConnection(void *dat, pop_connection *conn) {
    paroc_broker *br = (paroc_broker *)dat;
    return br->OnNewConnection(conn);
}


bool CloseConnection(void *dat, pop_connection *conn) {
    paroc_broker *br = (paroc_broker*)dat;
    return br->OnCloseConnection(conn);
}


/**
 * Receive request and put request in the FIFO
 */
void paroc_broker::ReceiveThread(pop_combox *server) { // Receive request and put request in the FIFO
    server->SetCallback(COMBOX_NEW, NewConnection, this);
    server->SetCallback(COMBOX_CLOSE, CloseConnection, this);

    while(state == POPC_STATE_RUNNING) {
        paroc_request req;
        req.data=nullptr;
        try {
            if(!ReceiveRequest(server, req)) {
                break;
            }

#ifdef POP_PSEUDO
	    // Is it a connection initialization, then just serve a new request
            if(req.from->is_initial_connection()) {
                /* Note LWK: Apparently wait_unlock is never set
                if(!req.from->is_wait_unlock()) {
                    if(obj != nullptr) {
                        obj->AddRef();
                    }
                }
                */
                continue;
            }
#endif

            // Is it a POP-C++ core call ? If so serve it right away
            if(ParocCall(req)) {
                if(req.data!=nullptr) {
                    delete req.data;
                }
                execCond.broadcast();
                continue;
            }
            // Register the request to be served by the broker serving thread
            RegisterRequest(req);
        } catch(std::exception &e) {
            LOG_WARNING("Exception in paroc_broker::ReceiveThread: %s", e.what());
            if(req.data != nullptr) {
                delete req.data;
            }
            execCond.broadcast();
            break;
        }
    }
    LOG_DEBUG("Exiting receive thread %s", paroc_broker::accesspoint.GetAccessString().c_str());
    server->Close();
}


bool paroc_broker::ReceiveRequest(pop_combox *server, paroc_request &req) {
    server->SetTimeout(-1);
    while(1) {
        // Waiting for a new connection or a new request
        pop_connection* conn = server->Wait();

        // Trouble with the connection
        if(conn == nullptr) {
            execCond.broadcast();
            return false;
        }

#ifndef POP_PSEUDO
        if(conn->is_initial_connection()) {
            continue;
        }
#endif

        // Receiving the real data
        pop_buffer_factory *fact = conn->GetBufferFactory();
        req.data = fact->CreateBuffer();

        if(req.data->Recv(conn)) {
            req.from = conn;
            const paroc_message_header &h = req.data->GetHeader();
            req.methodId[0] = h.GetClassID();
            req.methodId[1] = h.GetMethodID();

            if(!((req.methodId[2] = h.GetSemantics()) & INVOKE_SYNC)) {
#ifdef OD_DISCONNECT
                if(checkConnection) {
                    server->SendAck(conn);
                }
#endif
            }
            return true;
        }

        delete req.data;
    }
    return false;
}


void paroc_broker::RegisterRequest(paroc_request &req) {
    //Check if mutex is waiting/executing...
    int type = req.methodId[2];

    if(type & INVOKE_SYNC) {
        // Method call is synchronous, a response will be send back so the connection is saved
        req.from  = req.from->Clone();
    } else {
        // Method call is asynchronous so the connection is not needed anymore
        req.from->reset();
        req.from = nullptr;
    }


    if(type & INVOKE_CONC) {    // Method semantic is concurrent so trying to execute if there is no mutex pending
        mutexCond.lock();
        if(mutexCount <= 0) {
            ServeRequest(req);
            mutexCond.unlock();
            return;
        }
    } else if(type & INVOKE_MUTEX) {  // Method semantic is mutex, adding one to the number of mutex pending
        mutexCond.lock();
        mutexCount++;
        mutexCond.unlock();
    }

    // Adding the request to the request queue
    execCond.lock();
    request_fifo.push_back(req);
    int count = request_fifo.size();

    execCond.broadcast();
    execCond.unlock();

    if(type & INVOKE_CONC) {
        concPendings++;
        mutexCond.unlock();
    }

    if(count >= POPC_QUEUE_NORMAL) {
        //To many requests: Slowdown the receive thread...
        int step = (count/POPC_QUEUE_NORMAL);
        long t = step*step*step;
        //if (count>POPC_QUEUE_NORMAL+5)
        LOG_WARNING(" Warning: too many requests (unserved requests: %d)",count);
        if(count<=POPC_QUEUE_MAX) {
            popc_usleep(10*t);
        } else {
            while(request_fifo.size()>POPC_QUEUE_MAX) {
                popc_usleep(t*10);
            }
        }
    }
}

bool paroc_broker::OnNewConnection(pop_connection * /*conn*/) {
    if(obj != nullptr) {
        obj->AddRef();
    }
    return true;
}

/**
 * This method is called when a connection with an interface is closed.
 */
bool paroc_broker::OnCloseConnection(pop_connection * /*conn*/) {
    if(obj != nullptr) {
        int ret = obj->DecRef();
        if(ret <= 0) {
            execCond.broadcast();
        }
    }
    return true;
}


paroc_object * paroc_broker::GetObject() {
    return obj;
}

bool paroc_broker::ParocCall(paroc_request &req) {
    if(req.methodId[1] >= 10) {
        LOG_DEBUG_T("BRK_R", "Methodid >= 10");
        return false;
    }

    unsigned* methodid = req.methodId;
    pop_buffer *buf = req.data;
    switch(methodid[1]) {
    case 0:
        // BindStatus call
        if(methodid[2] & INVOKE_SYNC) {
            paroc_message_header h(0, 0, INVOKE_SYNC ,"BindStatus");
            buf->Reset();
            buf->SetHeader(h);
            int status = 0;
            std::string enclist;
            pop_buffer_factory_finder *finder = pop_buffer_factory_finder::GetInstance();
            int count = finder->GetFactoryCount();
            for(int i = 0; i < count; i++) {
                std::string t;
                if(finder->GetBufferName(i, t)) {
                    enclist += t;
                    if(i < count-1) {
                        enclist += " ";
                    }
                }
            }

            buf->Push("code", "int", 1);
            buf->Pack(&status, 1);
            buf->Pop();

            buf->Push("platform", "std::string", 1);
            buf->Pack(&paroc_system::platform, 1);
            buf->Pop();

            buf->Push("info", "std::string", 1);
            buf->Pack(&enclist, 1);
            buf->Pop();

            buf->Send(req.from);
        }
        break;
    case 1: {
        //AddRef call...
        if(!obj) {
            LOG_DEBUG_T("BRK_R", "AddRef call with null object");
            return false;
        }
        int ret = obj->AddRef();
        if(methodid[2] & INVOKE_SYNC) {
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
    case 2: {
        // Decrement reference
        if(obj == nullptr) {
            LOG_DEBUG_T("BRK_R", "DecRef call with null object");
            return false;
        }
        int ret = obj->DecRef();
        if(methodid[2] & INVOKE_SYNC) {
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
    case 3: {
        // Negotiate encoding call
        std::string enc;
        buf->Push("encoding", "std::string", 1);
        buf->UnPack(&enc,1);
        buf->Pop();
        pop_buffer_factory *fact = pop_buffer_factory_finder::GetInstance()->FindFactory(enc);
        bool ret;
        if(fact) {
            req.from->SetBufferFactory(fact);
            ret = true;
        } else {
            ret = false;
        }
        if(methodid[2] & INVOKE_SYNC) {
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
    case 4: {
        // Kill call
        if(obj && obj->CanKill()) {
            LOG_INFO("Object exit by killcall");
            exit(1);
        }
        break;
    }
    case 5: {
        //ObjectAlive call
        if(!obj) {
            LOG_DEBUG_T("BRK_R", "ObjectAlive call with null object");
            return false;
        }
        if(methodid[2] & INVOKE_SYNC) {
            buf->Reset();
            paroc_message_header h("ObjectActive");
            buf->SetHeader(h);
            bool ret=(instanceCount || request_fifo.size());
            buf->Push("result", "bool", 1);
            buf->Pack(&ret, 1);
            buf->Pop();
            buf->Send(req.from);
        }

        break;
    }
#ifdef OD_DISCONNECT
    case 6: {
        //ObjectAlive call
        if(obj==nullptr) {
            LOG_DEBUG_T("BRK_R", "ObjectAlive call with null object");
            return false;
        }
        if(methodid[2] & INVOKE_SYNC) {
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
#ifdef POP_PSEUDO
    case 7: {
        // Dummy message
        break;
    }
#endif
    default:
        LOG_DEBUG_T("BRK_R", "Invalid call type %u", methodid[1]);
        return false;
    }
    return true;
}
