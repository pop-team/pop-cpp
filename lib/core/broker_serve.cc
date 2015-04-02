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
    pop_broker instead of pop_broker
 */
#include "popc_intface.h"

#include "pop_broker.h"
#include "pop_interface.h"
#include "pop_event.h"
#include "pop_thread.h"
#include "pop_system.h"
#include "popc_logger.h"

#define PROPAGATE_EXCEPTION(a)  catch (a err) { LOG_WARNING("Exception in broker_serve"); if (request.from!=nullptr) pop_buffer::SendException(*request.data, request.from, err);  else UnhandledException(); }

class pop_invokethread: public pop_thread {
public:
    pop_invokethread(pop_broker *br, pop_request &myrequest, int *instanceCount, pop_condition *execCond);
    ~ pop_invokethread();
    virtual void start() override;

protected:
    pop_request request;

    pop_broker *pbroker;
    int *pinstanceCount;
    pop_condition *pcond;
};

pop_invokethread::pop_invokethread(pop_broker *br, pop_request &myrequest,  int *instanceCount, pop_condition *execCond): pop_thread(false), request(myrequest) {
    pbroker=br;
    pinstanceCount=instanceCount;
    pcond=execCond;
    pcond->lock();
    (*pinstanceCount)++;
    pcond->unlock();
}

pop_invokethread::~pop_invokethread() {
    delete request.data;
    if(request.from!=nullptr) {
        delete request.from;
    }

    pcond->lock();
    (*pinstanceCount)--;
    pcond->broadcast();
    pcond->unlock();
}

void pop_invokethread::start() {
    pbroker->DoInvoke(request);
}



bool pop_broker::GetRequest(pop_request &req) {
    pop_mutex_locker locker(execCond);

    //If the queue is empty then wait for the request....
    while(request_fifo.empty()) {
        if((obj!=nullptr && obj->GetRefCount()<=0) || state!=POP_STATE_RUNNING) {
            return false;
        }
        execCond.wait(); //Wait for new request
    }

    auto pos=request_fifo.begin();
    if(concPendings) {
        auto pos1=pos;
        while(pos1!=request_fifo.end()) {
            auto old=pos1;
            pop_request &tmp=*pos1++;
            if(tmp.methodId[2] & INVOKE_CONC) {
                req=tmp;
                request_fifo.erase(old);
                concPendings--;
                return true;
            } else if(tmp.methodId[2] & INVOKE_MUTEX) {
                break;
            }
        }
    }

    req=*pos;
    request_fifo.pop_front();

    //Top request is of type mutex
    if(req.methodId[2] & INVOKE_MUTEX) {
        while(instanceCount>0) {
            execCond.wait();
        }
    }

    return true;
}

void pop_broker::ServeRequest(pop_request &req) {
    int type=req.methodId[2];
    if(type & INVOKE_CONC) {
        auto thr= new pop_invokethread(this,req, &instanceCount,&execCond);

        int ret;
        int t=1;
        while((ret=thr->create())!=0 && t<3600) {
            LOG_WARNING("can not create a new thread. Sleep for %d seconds",t);
            popc_sleep(t);
            t=t*2;
        }

        if(ret!=0) {
            //Error: Can not create a new thread and timeout
            pop_mutex_locker locker(execCond);
            execCond.broadcast();

            if(req.from!=nullptr) {

                pop_exception e(ret);
                e.AddInfo(classname);
                e.AddInfo(accesspoint.GetAccessString());
                pop_buffer::SendException(*req.data, req.from, e);
            } else {
                LOG_ERROR("fail to create a new thread for %s@%s (method:%d:%d)\n",classname.c_str(), accesspoint.GetAccessString().c_str(), req.methodId[0], req.methodId[1]);
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
        delete req.data;
        if(req.from!=nullptr) {
            delete req.from;
        }
    }
}

void pop_broker::UnhandledException() {
    if(!pop_system::appservice.IsEmpty()) {
        //char tmp[1024];
        LOG_WARNING("Unhandled exception on %s@%s", classname.c_str(), accesspoint.GetAccessString().c_str());
//      sprintf(tmp,"Unhandled exception on %s@%s\n",(const char *)classname, accesspoint.GetAccessString());
        /*AppCoreService app(pop_system::appservice);
        app.Log(tmp);
        app.UnManageObject(pop_broker::accesspoint);
        app.KillAll();*/
        state=POP_STATE_ABORT;
    }
}

bool pop_broker::DoInvoke(pop_request &request) {
    try {
        if(!Invoke(request.methodId, *request.data, request.from)) {
            LOG_ERROR("Mismatched method was invoked: classid=%d, methodid=%d", request.methodId[0], request.methodId[1]);
            pop_exception::pop_throw(OBJECT_MISMATCH_METHOD, "Mismatched method was invoked");
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

    PROPAGATE_EXCEPTION(pop_interface)

    PROPAGATE_EXCEPTION(char *)
    catch(pop_exception *e) {
        LOG_WARNING("POP-C++ exception in pop_broker::DoInvoke");
        if(request.from!=nullptr) {
            std::string extra=e->Info();
            if(e->Info().empty()) {
                extra= classname + "@" + accesspoint.GetAccessString();
            } else {
                extra=classname + "@" + accesspoint.GetAccessString() + ": " + extra;
            }
            e->AddInfo(extra);
            pop_buffer::SendException(*request.data,request.from,*e);
        } else {
            UnhandledException();
        }
        delete e;
    } catch(pop_exception e) {
        LOG_WARNING("POP-C++ exception in pop_broker::DoInvoke %s", e.what());
        if(request.from!=nullptr) {

            std::string extra=e.Info();
            if(e.Info().empty()) {
                extra=classname+"@"+accesspoint.GetAccessString();
            } else {
                extra=classname+"@"+accesspoint.GetAccessString()+": "+extra;
            }
            e.AddInfo(extra);
            pop_buffer::SendException(*request.data, request.from, e);
        } else {
            UnhandledException();
        }
    } catch(std::exception *e) {
        LOG_WARNING("Std exception in pop_broker::DoInvoke");
        if(request.from != nullptr) {
            pop_exception  e2=pop_exception(STD_EXCEPTION);
            e2.AddInfo(classname+"@"+accesspoint.GetAccessString() + ": " + e->what());
            pop_buffer::SendException(*request.data, request.from, e2);
            delete e;
        } else {
            UnhandledException();
        }
    } catch(std::exception e) {
        LOG_WARNING("Std exception in pop_broker::DoInvoke");
        if(request.from != nullptr) {
            pop_exception  e2=pop_exception(STD_EXCEPTION);
            e2.AddInfo(classname+"@"+accesspoint.GetAccessString() + ": " + e.what());
            pop_buffer::SendException(*request.data, request.from, e2);
        } else {
            UnhandledException();
        }
    } catch(...) {
        LOG_WARNING("Unknown exception in pop_broker::DoInvoke");
        if(request.from!=nullptr) {
            pop_exception e2(UNKNOWN_EXCEPTION);
            e2.AddInfo(classname+"@"+accesspoint.GetAccessString());
            pop_buffer::SendException(*request.data, request.from, e2);
        } else {
            UnhandledException();
        }
    }

    if(obj==nullptr || obj->GetRefCount()<=0) {
        return false;
    }

    return true;
}


bool pop_broker::Invoke(unsigned method[3], pop_buffer &buf, pop_connection *peer) {
    pop_request req;
    req.from=peer;
    memcpy(req.methodId, method, 3*sizeof(unsigned));
    req.data=&buf;
    return PopCall(req);
}
