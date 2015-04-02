/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of parallel object broker: General part.
 *
 *
 */

/*
  Deeply need refactoring:
    pop_broker instead of pop_broker
 */

#include "popc_intface.h"
#include "popc_logger.h"

#include "pop_broker.h"
#include "pop_interface.h"
#include "pop_event.h"
#include "pop_buffer_factory_finder.h"
#include "pop_buffer_raw.h"
#include "pop_utils.h"
#include "pop_thread.h"
#include "pop_system.h"

#define TIMEOUT 1800

#define MINMETHODID 2
pop_request::pop_request() {
    from=nullptr;
    data=nullptr;
    userdata=nullptr;
}

pop_request::pop_request(const pop_request &r) {
    from=r.from;
    memcpy(methodId,r.methodId,3*sizeof(unsigned));
    data=r.data;
    userdata=r.userdata;
}


void pop_request::operator =(const pop_request &r) {
    from=r.from;
    memcpy(methodId,r.methodId,3*sizeof(unsigned));
    data=r.data;
    userdata=r.userdata;
}

void broker_interupt(int /*sig*/) {
#ifndef __WIN32__
    LOG_CORE( "Interrupt on thread id %lu",(unsigned long)pthread_self());
#else
    LOG_CORE( "Interrupt on thread id %lu",(unsigned long)GetCurrentThreadId());
#endif
}


class pop_receivethread: public pop_thread {
public:
    pop_receivethread(pop_broker *br, pop_combox *com);
    ~pop_receivethread();
    virtual void start() override;
protected:
    pop_broker *broker;
    pop_combox *comm;
};

pop_receivethread::pop_receivethread(pop_broker *br, pop_combox *combox): pop_thread(true) {
    broker=br;
    comm=combox;
}
pop_receivethread::~pop_receivethread() {
}

void pop_receivethread::start() {
#ifndef __WIN32__
    popc_signal(popc_SIGHUP,broker_interupt);
#endif
    broker->ReceiveThread(comm);
}

//===pop_object: base class for all parallel object-server side


//===pop_broker: the base class for server object broker

//char pop_broker::myContact[256];

pop_accesspoint pop_broker::accesspoint;
std::string pop_broker::classname;


void broker_killed(int sig) {
    LOG_ERROR("FATAL: SIGNAL %d on %s@%s",sig, pop_broker::classname.c_str(), pop_broker::accesspoint.GetAccessString().c_str());
    exit(1);
}


pop_broker::pop_broker() {
    obj=nullptr;
    state=POP_STATE_RUNNING;
    instanceCount=0;
    mutexCount=0;
    concPendings=0;
}

pop_broker::~pop_broker() {
    int n=comboxArray.size();
    for(int i=0; i<n; i++) {
        delete comboxArray[i];
    }
    if(obj!=nullptr) {
        delete obj;
    }
}

void pop_broker::AddMethodInfo(unsigned cid, pop_method_info *methods, int sz) {
    if(sz<=0 || methods==nullptr) {
        return;
    }
    pop_class_info t;
    t.cid=cid;
    t.methods=methods;
    t.sz=sz;
    methodnames.push_back(t);
}

const char *pop_broker::FindMethodName(unsigned classID, unsigned methodID) {
    for(auto& t : methodnames){
        if(t.cid==classID) {
            pop_method_info *m=t.methods;
            int n=t.sz;
            for(int i=0; i<n; i++, m++){
                if(m->mid==methodID) {
                    return m->name;
                }
            }
        }
    }
    return nullptr;
}

bool pop_broker::FindMethodInfo(const char *name, unsigned &classID, unsigned &methodID) {
    if(name==nullptr) {
        return false;
    }

    for(auto& t : methodnames){
        pop_method_info *m=t.methods;
        int n=t.sz;
        for(int i=0; i<n; i++, m++){
            if(pop_utils::isEqual(name,m->name)) {
                methodID=m->mid;
                classID=t.cid;
                return true;
            }
        }
    }

    return false;
}

int pop_broker::Run() {
    //Create threads for each protocols for receiving requests....

    std::vector<pop_receivethread *> ptArray;
    int comboxCount = comboxArray.size();
    if(comboxCount <= 0) {
        return -1;
    }

    state = POP_STATE_RUNNING;
    ptArray.resize(comboxCount);
    int i;

    for(i = 0; i < comboxCount; i++) {
        ptArray[i] = new pop_receivethread(this, comboxArray[i]);
        int ret = ptArray[i]->create();
        if(ret != 0) {
            return errno;
        }
    }

    if(obj == nullptr) {
        popc_alarm(TIMEOUT);
    }

    while(state == POP_STATE_RUNNING) {
        try {
            pop_request req;
            if(!GetRequest(req)) {
                break;
            }
            ServeRequest(req);
            if(req.methodId[2] & INVOKE_CONSTRUCTOR) {
                popc_alarm(0);
                if(obj == nullptr) {
                    break;
                }
            }
        } catch(std::exception &e) {
            LOG_WARNING("Unknown exception in pop_broker::Run: %s", e.what());
            UnhandledException();
        }
    }


    if(obj!=nullptr && state==POP_STATE_RUNNING) {
        pop_mutex_locker test(execCond);

        //Wait for all invocations terminated....
        while(instanceCount > 0 || !request_fifo.empty()) {
            execCond.wait();
        }
    }

    state = POP_STATE_EXIT;

    for(i = 0; i < comboxCount; i++) {
        if(WakeupReceiveThread(comboxArray[i])) {
            delete ptArray[i];
        } else {
            ptArray[i]->cancel();
        }
    }

    return 0;
}

bool pop_broker::Initialize(int *argc, char ***argv) {
    if(pop_utils::checkremove(argc, argv, "-runlocal")) {
        pop_od::defaultLocalJob=true;
    }

    auto comboxFactory = pop_combox_factory::GetInstance();

    int comboxCount = comboxFactory->GetCount();
    comboxArray.resize(comboxCount);

    std::string protocolName;
    std::string url;

    int count=0;
    for(int i = 0; i < comboxCount; i++) {
        comboxArray[count] = comboxFactory->Create(i);
        if(comboxArray[count] == nullptr) {
            LOG_ERROR("Fail to create combox #%d",i);
        } else {
            count++;
        }
    }

    if(comboxCount!=count) {
        comboxCount=count;
        comboxArray.resize(comboxCount);
    }

    if(comboxCount<=0) {
        return false;
    }

    auto address = pop_utils::checkremove(argc,argv,"-address=");

    for(int i=0; i<comboxCount; i++) {
        auto pc = comboxArray[i];

        auto protocolName = pc->GetProtocol();

        char argument[1024];
        sprintf(argument, "-%s_port=", protocolName.c_str());
        char *portstr=pop_utils::checkremove(argc,argv,argument);

        LOG_DEBUG_T("BRKR", "Create combox %s with port: %s", protocolName.c_str(), portstr);

        if(portstr!=nullptr) {
            int port;
            if(sscanf(portstr,"%d",&port)!=1) {
                return false;
            }
            if(!pc->Create(port, true)) {
                pop_exception::perror("Broker");
                return false;
            }
        } else {
            if(pc->need_address()){
                if(!address){
                    //std::string default_address = "uds_0." + std::to_string(pop_system::pop_current_local_address);

                    //LOG_DEBUG_T("BRKR", "Create combox (address) with default address \"%s\"", default_address.c_str());

                    //TODO: This is highly unsafe with threads
                    //++pop_system::pop_current_local_address;

                    if(!pc->Create(nullptr, true)) {
                        pop_exception::perror("Broker");
                        return false;
                    }
                } else {
                    LOG_DEBUG_T("BRKR", "Create combox (address) with address \"%s\"", address);

                    if(!pc->Create(address, true)) {
                        pop_exception::perror("Broker");
                        return false;
                    }
                }
            } else {
                if(!pc->Create(0, true)) {
                    pop_exception::perror("Broker");
                    return false;
                }
            }
        }

        auto ap = pc->GetUrl();

        url+=ap;
        if(i<comboxCount-1) {
            url+=PROTO_DELIMIT_CHAR;
        }
    }

    LOG_DEBUG_T("[BRKR]", "%d combox have been created", comboxCount);

    accesspoint.SetAccessString(url.c_str());

    char *tmp=pop_utils::checkremove(argc,argv,"-constructor");
    if(tmp!=nullptr && !classname.empty()) {
        pop_request r;
        pop_buffer_raw tmp;
        r.data=&tmp;
        if(!FindMethodInfo(classname.c_str(),r.methodId[0],r.methodId[1]) || r.methodId[1]!=10) {
            LOG_ERROR_T("[BRKR]", "POP-C++ Error: [CORE] Broker cannot not find default constructor");
            return false;
        }
        r.methodId[2]=INVOKE_CONSTRUCTOR;
        if(!DoInvoke(r)) {
            return false;
        }
    }

    pop_object::argc=*argc;
    pop_object::argv=*argv;

    popc_signal(popc_SIGTERM, broker_killed);
    popc_signal(popc_SIGINT, broker_killed);
    popc_signal(popc_SIGILL, broker_killed);
    popc_signal(popc_SIGABRT, broker_killed);
#ifndef __WIN32__
    popc_signal(popc_SIGQUIT, broker_killed);
    popc_signal(popc_SIGPIPE, popc_SIG_IGN);
#endif

    return true;
}



bool pop_broker::WakeupReceiveThread(pop_combox  *mycombox) {
    pop_combox_factory *combox_factory = pop_combox_factory::GetInstance();

    bool ok=false;

    auto prot = mycombox->GetProtocol();
    auto url = mycombox->GetUrl();

    char *str=strdup(url.c_str());
    if(str==nullptr) {
        return false;
    }

    std::vector<std::string> tokens;
    popc_tokenize_r(tokens,str," \t\n\r");
    for(auto tok : tokens){
        if(!ok)
            break;
        pop_combox *tmp = combox_factory->Create(prot.c_str());
        tmp->SetTimeout(100000);
        std::string address = tok;
        if(address.find("uds://") == 0) {
            address = address.substr(6);
        }

        auto buffer_factory = tmp->GetBufferFactory();
        auto buffer = buffer_factory->CreateBuffer();

        bool connected = false;
        if(tmp->need_address()){
            connected = tmp->Create(address.c_str(), false) && tmp->Connect(nullptr);
        } else {
            connected = tmp->Create(0, false) && tmp->Connect(tok.c_str());
        }

        if(connected) {
            try {
                pop_message_header h(0,5, INVOKE_SYNC ,"ObjectActive");
                buffer->Reset();
                buffer->SetHeader(h);
                pop_connection* connection = tmp->get_connection();
                if(!buffer->Send((*tmp), connection)) {
                    ok = false;
                } else {
                    if(!buffer->Recv((*tmp), connection)) {
                        ok = false;
                    }
                    bool ret;
                    buffer->Push("result", "bool", 1);
                    buffer->UnPack(&ret,1);
                    buffer->Pop();
                    ok = !ret;
                }
            } catch(std::exception &e) {
                LOG_WARNING("Exception in pop_broker::WakeUpReceiveThread: %s", e.what());
                ok = true;
            }
        }
        delete buffer;
        delete tmp;
    }

    return ok;
}
