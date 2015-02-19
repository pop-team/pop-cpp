/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of parallel object broker: serve request stuffs.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_Broker instead of paroc_broker
 */
#include "popc_intface.h"

#include "paroc_broker.h"
#include "paroc_interface.h"
#include "paroc_event.h"
#include "paroc_thread.h"
#include "paroc_system.h"
#include "popc_logger.h"

#define PROPAGATE_EXCEPTION(a)  catch (a err) { LOG_WARNING("Exception in broker_serve"); if (request.from!=NULL) paroc_buffer::SendException(*request.data, request.from, err);  else UnhandledException(); }

class paroc_invokethread: public paroc_thread {
public:
    paroc_invokethread(paroc_broker *br, paroc_request &myrequest, int *instanceCount, paroc_condition *execCond);
    ~ paroc_invokethread();
    virtual void start();

protected:
    paroc_request request;

    paroc_broker *pbroker;
    int *pinstanceCount;
    paroc_condition *pcond;
};

paroc_invokethread::paroc_invokethread(paroc_broker *br, paroc_request &myrequest,  int *instanceCount, paroc_condition *execCond): paroc_thread(false), request(myrequest) {
    pbroker=br;
    pinstanceCount=instanceCount;
    pcond=execCond;
    pcond->lock();
    (*pinstanceCount)++;
    pcond->unlock();
}

paroc_invokethread::~paroc_invokethread() {
    request.data->Destroy();
    if(request.from!=NULL) {
        delete request.from;
    }

    pcond->lock();
    (*pinstanceCount)--;
    pcond->broadcast();
    pcond->unlock();
}

void paroc_invokethread::start() {
    pbroker->DoInvoke(request);
}



bool paroc_broker::GetRequest(paroc_request &req) {
    paroc_mutex_locker locker(execCond);

    //If the queue is empty then wait for the request....
    while(request_fifo.IsEmpty()) {
        if((obj!=NULL && obj->GetRefCount()<=0) || state!=POPC_STATE_RUNNING) {
            return false;
        }
        execCond.wait(); //Wait for new request
    }

    POSITION pos=request_fifo.GetHeadPosition();
    if(concPendings) {
        POSITION pos1=pos;
        while(pos1!=NULL) {
            POSITION old=pos1;
            paroc_request &tmp=request_fifo.GetNext(pos1);
            if(tmp.methodId[2] & INVOKE_CONC) {
                req=tmp;
                request_fifo.RemoveAt(old);
                concPendings--;
                return true;
            } else if(tmp.methodId[2] & INVOKE_MUTEX) {
                break;
            }
        }
    }

    req=request_fifo.GetAt(pos);
    request_fifo.RemoveHead();

    //Top request is of type mutex
    if(req.methodId[2] & INVOKE_MUTEX) {
        while(instanceCount>0) {
            execCond.wait();
        }
    }
    return true;
}

void paroc_broker::ServeRequest(paroc_request &req) {
    int type=req.methodId[2];
    if(type & INVOKE_CONC) {
        paroc_invokethread *thr= new paroc_invokethread(this,req, &instanceCount,&execCond);

        int ret;
        int t=1;
        while((ret=thr->create())!=0 && t<3600) {
            LOG_WARNING("can not create a new thread. Sleep for %d seconds",t);
            popc_sleep(t);
            t=t*2;
        }

        if(ret!=0) {
            //Error: Can not create a new thread and timeout
            paroc_mutex_locker locker(execCond);
            execCond.broadcast();

            if(req.from!=NULL) {

                paroc_exception e(ret);
                e.AddInfo(classname+"@"+accesspoint.GetAccessString());
                paroc_buffer::SendException(*req.data, req.from, e);
            } else {
                LOG_ERROR("fail to create a new thread for %s@%s (method:%d:%d)\n",(const char *)classname,accesspoint.GetAccessString(), req.methodId[0], req.methodId[1]);
            }
            delete thr;

        }
    } else {
        DoInvoke(req);
        if(type & INVOKE_MUTEX) {
            mutexCond.lock();
            mutexCount--;
            if(mutexCount==0) {
                mutexCond.broadcast();
            }
            mutexCond.unlock();
        }
        req.data->Destroy();
        if(req.from!=NULL) {
            delete req.from;
        }
    }
}

void paroc_broker::UnhandledException() {
    if(!paroc_system::appservice.IsEmpty()) {
        //char tmp[1024];
        LOG_WARNING("Unhandled exception on %s@%s",(const char *)classname, accesspoint.GetAccessString());
//      sprintf(tmp,"Unhandled exception on %s@%s\n",(const char *)classname, accesspoint.GetAccessString());
        /*AppCoreService app(paroc_system::appservice);
        app.Log(tmp);
        app.UnManageObject(paroc_broker::accesspoint);
        app.KillAll();*/
        state=POPC_STATE_ABORT;
    }
}

bool paroc_broker::DoInvoke(paroc_request &request) {
    try {
        if(!Invoke(request.methodId, *request.data, request.from)) {
            LOG_ERROR("Mismatched method was invoked: id=%d", request.methodId);
            paroc_exception::paroc_throw(OBJECT_MISMATCH_METHOD, "Mismatched method was invoked");
        }
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
    catch(paroc_exception *e) {
        LOG_WARNING("POP-C++ exception in paroc_broker::DoInvoke");
        if(request.from!=NULL) {
            POPString extra=e->Info();
            if(e->Info().Length()==0) {
                extra= classname + "@" + accesspoint.GetAccessString();
            } else {
                extra=classname + "@" + accesspoint.GetAccessString() + ": " + extra;
            }
            e->AddInfo(extra);
            paroc_buffer::SendException(*request.data,request.from,*e);
        } else {
            UnhandledException();
        }
        delete e;
    } catch(paroc_exception e) {
        LOG_WARNING("POP-C++ exception in paroc_broker::DoInvoke");
        if(request.from!=NULL) {

            POPString extra=e.Info();
            if(e.Info().Length()==0) {
                extra=classname+"@"+accesspoint.GetAccessString();
            } else {
                extra=classname+"@"+accesspoint.GetAccessString()+": "+extra;
            }
            e.AddInfo(extra);
            paroc_buffer::SendException(*request.data, request.from, e);
        } else {
            UnhandledException();
        }
    } catch(std::exception *e) {
        LOG_WARNING("Std exception in paroc_broker::DoInvoke");
        if(request.from != NULL) {
            paroc_exception  e2=paroc_exception(STD_EXCEPTION);
            e2.AddInfo(classname+"@"+accesspoint.GetAccessString() + ": " + e->what());
            paroc_buffer::SendException(*request.data, request.from, e2);
            delete e;
        } else {
            UnhandledException();
        }
    } catch(std::exception e) {
        LOG_WARNING("Std exception in paroc_broker::DoInvoke");
        if(request.from != NULL) {
            paroc_exception  e2=paroc_exception(STD_EXCEPTION);
            e2.AddInfo(classname+"@"+accesspoint.GetAccessString() + ": " + e.what());
            paroc_buffer::SendException(*request.data, request.from, e2);
        } else {
            UnhandledException();
        }
    } catch(...) {
        LOG_WARNING("Unknown exception in paroc_broker::DoInvoke");
        if(request.from!=NULL) {
            paroc_exception e2(UNKNOWN_EXCEPTION);
            e2.AddInfo(classname+"@"+accesspoint.GetAccessString());
            paroc_buffer::SendException(*request.data, request.from, e2);
        } else {
            UnhandledException();
        }
    }

    if(obj==NULL || obj->GetRefCount()<=0) {
        return false;
    }
    return true;
}


bool paroc_broker::Invoke(unsigned method[3], paroc_buffer &buf, paroc_connection *peer) {
    paroc_request req;
    req.from=peer;
    memcpy(req.methodId,method, 3*sizeof(unsigned));
    req.data=&buf;
    return ParocCall(req);
}