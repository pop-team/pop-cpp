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
    POPC_Broker instead of paroc_broker
 */

#include "popc_intface.h"
#include "popc_logger.h"

#include "paroc_broker.h"
#include "paroc_interface.h"
#include "paroc_event.h"
#include "paroc_buffer_factory_finder.h"
#include "paroc_buffer_raw.h"
#include "paroc_utils.h"
#include "paroc_thread.h"
#include "paroc_system.h"

#define TIMEOUT 1800

#define MINMETHODID 2
paroc_request::paroc_request() {
    from=NULL;
    data=NULL;
    userdata=NULL;
}

paroc_request::paroc_request(const paroc_request &r) {
    from=r.from;
    memcpy(methodId,r.methodId,3*sizeof(unsigned));
    data=r.data;
    userdata=r.userdata;
}


void paroc_request::operator =(const paroc_request &r) {
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


class paroc_receivethread: public paroc_thread {
public:
    paroc_receivethread(paroc_broker *br, paroc_combox *com);
    ~paroc_receivethread();
    virtual void start();
protected:
    paroc_broker *broker;
    paroc_combox *comm;
};

paroc_receivethread::paroc_receivethread(paroc_broker *br, paroc_combox *combox): paroc_thread(true) {
    broker=br;
    comm=combox;
}
paroc_receivethread::~paroc_receivethread() {
}

void paroc_receivethread::start() {
#ifndef __WIN32__
    popc_signal(popc_SIGHUP,broker_interupt);
#endif
    broker->ReceiveThread(comm);
}

//===paroc_object: base class for all parallel object-server side


//===paroc_broker: the base class for server object broker

//char paroc_broker::myContact[256];

paroc_accesspoint paroc_broker::accesspoint;
POPString paroc_broker::classname;


void broker_killed(int sig) {
    LOG_ERROR("FATAL: SIGNAL %d on %s@%s",sig, (const char *)paroc_broker::classname,paroc_broker::accesspoint.GetAccessString());
    exit(1);
}


paroc_broker::paroc_broker() {
    obj=NULL;
    state=POPC_STATE_RUNNING;
    instanceCount=0;
    mutexCount=0;
    concPendings=0;
}

paroc_broker::~paroc_broker() {
    int n=comboxArray.size();
    for(int i=0; i<n; i++) {
        comboxArray[i]->Destroy();
    }
    if(obj!=NULL) {
        delete obj;
    }
}

void paroc_broker::AddMethodInfo(unsigned cid, paroc_method_info *methods, int sz) {
    if(sz<=0 || methods==NULL) {
        return;
    }
    paroc_class_info &t=methodnames.AddHeadNew();
    t.cid=cid;
    t.methods=methods;
    t.sz=sz;
}

const char *paroc_broker::FindMethodName(unsigned classID, unsigned methodID) {
    POSITION pos=methodnames.GetHeadPosition();
    while(pos!=NULL) {
        paroc_class_info &t=methodnames.GetNext(pos);
        if(t.cid==classID) {
            paroc_method_info *m=t.methods;
            int n=t.sz;
            for(int i=0; i<n; i++, m++) if(m->mid==methodID) {
                    return m->name;
                }
        }
    }
    return NULL;
}

bool paroc_broker::FindMethodInfo(const char *name, unsigned &classID, unsigned &methodID) {
    if(name==NULL) {
        return false;
    }

    POSITION pos=methodnames.GetHeadPosition();
    while(pos!=NULL) {
        paroc_class_info &t=methodnames.GetNext(pos);
        paroc_method_info *m=t.methods;
        int n=t.sz;
        for(int i=0; i<n; i++, m++) if(paroc_utils::isEqual(name,m->name)) {
                methodID=m->mid;
                classID=t.cid;
                return true;
            }
    }
    return false;
}


int paroc_broker::Run() {
    //Create threads for each protocols for receiving requests....

    paroc_array<paroc_receivethread *> ptArray;
    int comboxCount = comboxArray.size();
    if(comboxCount <= 0) {
        return -1;
    }

    state = POPC_STATE_RUNNING;
    ptArray.resize(comboxCount);
    int i;

    for(i = 0; i < comboxCount; i++) {
        ptArray[i] = new paroc_receivethread(this, comboxArray[i]);
        int ret = ptArray[i]->create();
        if(ret != 0) {
            return errno;
        }
    }

    if(obj == NULL) {
        popc_alarm(TIMEOUT);
    }

    while(state == POPC_STATE_RUNNING) {
        try {
            paroc_request req;
            if(!GetRequest(req)) {
                break;
            }
            ServeRequest(req);
            if(req.methodId[2] & INVOKE_CONSTRUCTOR) {
                popc_alarm(0);
                if(obj == NULL) {
                    break;
                }
            }
        } catch(...) {
            LOG_WARNING("Unknown exception in paroc_broker::Run");
            UnhandledException();
        }
    }


    if(obj!=NULL && state==POPC_STATE_RUNNING) {
        paroc_mutex_locker test(execCond);

        //Wait for all invocations terminated....
        while(instanceCount > 0 || !request_fifo.IsEmpty()) {
            execCond.wait();
        }
    }

    state = POPC_STATE_EXIT;

    for(i = 0; i < comboxCount; i++) {
        if(WakeupReceiveThread(comboxArray[i])) {
            delete ptArray[i];
        } else {
            ptArray[i]->cancel();
        }
    }

    return 0;
}

bool paroc_broker::Initialize(int *argc, char ***argv) {
    if(paroc_utils::checkremove(argc, argv, "-runlocal")) {
        paroc_od::defaultLocalJob=true;
    }

    char *address = paroc_utils::checkremove(argc,argv,"-address=");
    (void)address; // Note: this line avoids a warning

    paroc_combox_factory  *comboxFactory = paroc_combox_factory::GetInstance();
    int comboxCount = comboxFactory->GetCount();
    comboxArray.resize(comboxCount);
    POPString protocolName;
    POPString url;

    int count=0;
    for(int i = 0; i < comboxCount; i++) {
        comboxArray[count] = comboxFactory->Create(i);
        if(comboxArray[count] == NULL) {
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

    for(int i=0; i<comboxCount; i++) {
        paroc_combox * pc = comboxArray[i];
        pc->GetProtocol(protocolName);

        char argument[1024];
        sprintf(argument, "-%s_port=", (const char *)protocolName);
        char *portstr=paroc_utils::checkremove(argc,argv,argument);
        if(portstr!=NULL) {
            int port;
            if(sscanf(portstr,"%d",&port)!=1) {
                return false;
            }
            if(!pc->Create(port, true)) {
                paroc_system::perror("Broker");
                return false;
            }
        } else {
#ifdef DEFINE_UDS_SUPPORT
            if(!pc->Create(address, true)) {
#else
            if(!pc->Create(0, true)) {
#endif
                paroc_system::perror("Broker");
                return false;
            }
        }


        POPString ap;
        pc->GetUrl(ap);
        url+=ap;
        if(i<comboxCount-1) {
            url+=PROTO_DELIMIT_CHAR;
        }
    }

    accesspoint.SetAccessString(url.GetString());

    char *tmp=paroc_utils::checkremove(argc,argv,"-constructor");
    if(tmp!=NULL && classname!=NULL) {
        paroc_request r;
        paroc_buffer_raw tmp;
        r.data=&tmp;
        if(!FindMethodInfo(classname,r.methodId[0],r.methodId[1]) || r.methodId[1]!=10) {
            LOG_ERROR("POP-C++ Error: [CORE] Broker cannot not find default constructor");
            return false;
        }
        r.methodId[2]=INVOKE_CONSTRUCTOR;
        if(!DoInvoke(r)) {
            return false;
        }
    }

    paroc_object::argc=*argc;
    paroc_object::argv=*argv;

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



bool paroc_broker::WakeupReceiveThread(paroc_combox  *mycombox) {

    paroc_combox_factory *combox_factory = paroc_combox_factory::GetInstance();
    POPString url, prot;

    bool ok=false;
    mycombox->GetProtocol(prot);
    mycombox->GetUrl(url);

    char *str=url.GetString();
    if(str==NULL) {
        return false;
    }

    char *ptr;
    char *tok = popc_strtok_r(str," \t\n\r",&ptr);
    while(tok != NULL && !ok) {
        paroc_combox *tmp = combox_factory->Create(prot);
        tmp->SetTimeout(100000);
        std::string address(tok);
        if(address.find("uds://") == 0) {
            address = address.substr(6);
        }
        paroc_buffer_factory* buffer_factory = tmp->GetBufferFactory();
        paroc_buffer* buffer = buffer_factory->CreateBuffer();
#ifdef DEFINE_UDS_SUPPORT
        if(tmp->Create(address.c_str(), false) && tmp->Connect(NULL)) {
#else
        if(tmp->Create(0, false) && tmp->Connect(tok)) {
#endif
            try {
                paroc_message_header h(0,5, INVOKE_SYNC ,"ObjectActive");
                buffer->Reset();
                buffer->SetHeader(h);
                paroc_connection* connection = tmp->get_connection();
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
            } catch(...) {
                LOG_WARNING("Unknown exception in paroc_broker::WakeUpReceiveThread");
                ok = true;
            }
        }
        buffer->Destroy();
        tmp->Destroy();
        tok = popc_strtok_r(NULL, " \t\n\r", &ptr);
    }

    return ok;
}
