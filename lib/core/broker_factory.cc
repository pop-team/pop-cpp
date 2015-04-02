/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of broker factory.
 *
 *
 * Modifications :
 * Authors      Date            Comment
 * clementval  10/27/2011  Set services accesspoint cretaed from String as service accesspoint
 * P.Kuonen     18.9.2012       Add "POP-C++ error" in error messages (PEKA)
 */

/*
  Deeply need refactoring:
    POPC_BrokerFactory instead of pop_broker_factory
 */

#include "popc_intface.h"
#include "pop_broker_factory.h"
#include "paroc_utils.h"
#include "paroc_system.h"

std::vector<pop_broker_init> *pop_broker_factory::brokerlist=nullptr;
ispackedfunc pop_broker_factory::CheckIfPacked=nullptr;

pop_broker_factory::pop_broker_factory(initbrokerfunc func, const char *name) {
    if(!brokerlist) {
        brokerlist = new std::vector<pop_broker_init>;
    }

    if(!name || !func || test(name)) {
        return;
    }

    brokerlist->push_back({func, name});
}

pop_broker *pop_broker_factory::Create(const char *objname) {
    LOG_DEBUG("Create broker for %s", objname);
    if(brokerlist == nullptr || objname == nullptr) {
        return nullptr;
    }

    for(auto& t : *brokerlist){
        if(paroc_utils::isEqual(objname, t.objname.c_str())) {
            return t.func();
        }
    }

    return nullptr;
}

void pop_broker_factory::List(std::vector<std::string>& objlist) {
    if(brokerlist == nullptr) {
        return;
    }
    for(auto& t : *brokerlist){
        objlist.emplace_back(t.objname);
    }
}

bool pop_broker_factory::test(const char *objname) {
    if(brokerlist == nullptr) {
        return false;
    }
    for(auto& test : *brokerlist){
        if(paroc_utils::isEqual(objname, test.objname.c_str())) {
            return true;
        }
    }
    return false;
}


pop_broker * pop_broker_factory::Create(int *argc, char ***argv) {
    /**
     * Display the information about the parallel object executable
     * note: this bit of code existed in pseudodynamic version and is
     * kept just in case.
     */
/*
    char *tmp1 = paroc_utils::checkremove(argc,argv,"-printmpi");
    if(tmp1 != nullptr) {
        char abspath[1024];
        char *thisfile = getenv("POPC_EXE");
        if(thisfile == nullptr) {
            thisfile = (*argv)[0];
        }
        paroc_utils::FindAbsolutePath(thisfile,abspath);
        PrintBrokersMPI(abspath);
        exit(0);
    }
*/
    char *tmp=paroc_utils::checkremove(argc,argv,"-list");
    if(tmp!=nullptr) {
        // char abspath[1024];
        char *thisfile=getenv("POPC_EXE");
        if(thisfile==nullptr) {
            thisfile=(*argv)[0];
        }
        PrintBrokers(paroc_utils::FindAbsolutePath(thisfile).c_str(), strcmp(tmp,"long")==0);
        exit(0);
    }

    char *usage=paroc_utils::checkremove(argc,argv,"-help");
    char *object=paroc_utils::checkremove(argc,argv,"-object=");
    if(usage!=nullptr || object==nullptr) {
        printf("\n Usage:\n\t%s [-help] [-list | -listlong] [-port=<local port>] [-callback=<host:port>] [-appservice=<host:port>] [-nostdio] -object=<objectname>\n",(*argv)[0]);
        return nullptr;
    }


    tmp=paroc_utils::checkremove(argc,argv,"-appservice=");
    if(tmp!=nullptr) {
        paroc_system::appservice.SetAccessString(tmp);
        paroc_system::appservice.SetAsService();  //Set the accesspoint as a service accesspoint
    }

    /*#ifndef DEFINE_UDS_SUPPORT
        if ((tmp=getenv("POPC_JOBSERVICE"))!=nullptr) {
            paroc_system::jobservice.SetAccessString(tmp);
          paroc_system::jobservice.SetAsService();  //Set the accesspoint as a service accesspoint
        } else if ((tmp=paroc_utils::checkremove(argc,argv,"-jobservice=")) != nullptr) {
            paroc_system::jobservice.SetAccessString(tmp);
          paroc_system::jobservice.SetAsService();  //Set the accesspoint as a service accesspoint
        } else {
            char tmpstr[256];
            LOG_DEBUG("Jobservice is not specified. Use the default one!");
            sprintf(tmpstr,"%s:%d",(const char *)paroc_system::GetHost(),DEFAULTPORT);
            paroc_system::jobservice.SetAccessString(tmpstr);
          paroc_system::jobservice.SetAsService();  //Set the accesspoint as a service accesspoint
        }
    #endif*/

    bool nostdio=(paroc_utils::checkremove(argc,argv,"-nostdio")!=nullptr);

    //Now create the broker
    if(object==nullptr || *object==0) {
        return nullptr;
    }

    // Create the real Broker object
    pop_broker *objbroker=Create(object);
    if(objbroker==nullptr) {
        printf("POP-C++ Error: %s: unkown object name\n", (*argv)[1]);
        return nullptr;
    }

    // Set the classname for this broker
    pop_broker::classname=object;

    if(nostdio) {
        popc_close(0);
        popc_close(1);
        popc_close(2);

        // If the nostdio option is used, either redirect stdout to a .log file or ignore it
        // TODO LW logging, see if we keep
        popc_open("/dev/null",O_RDONLY);
#ifndef NDEBUG
        char fname[256];
        sprintf(fname,"/tmp/object_%s_%d.log", pop_broker::classname.c_str(),popc_getpid());
        popc_open(fname,O_WRONLY | O_CREAT,S_IRWXU | S_IRGRP);
        popc_dup2(1,2);
#else
        popc_open("/dev/null",O_WRONLY);
        popc_open("/dev/null",O_WRONLY);
#endif
    }

    return objbroker;
}


void pop_broker_factory::PrintBrokers(const char *abspath, bool longformat) {
    if(!longformat) {
        printf("List of parallel object classes:\n====\n");
    }
    if(brokerlist) {
        for(auto& t : *brokerlist){
            if(!(pop_broker_factory::CheckIfPacked!=nullptr && !pop_broker_factory::CheckIfPacked(t.objname.c_str()))) {
                if(longformat) {
                    printf("%s %s %s\n", t.objname.c_str(), paroc_system::platform.c_str(), abspath);
                } else {
                    printf("%s\n",t.objname.c_str());
                }
            }
        }
    }
    if(!longformat) {
        printf("====\nArchitecture=%s\n",paroc_system::platform.c_str());
    }
}

/* note: this coded existed in the pseudodynamic version of the code but is now disabled.
void pop_broker_factory::PrintBrokersMPI(const char *abspath) {
    if(brokerlist!=nullptr) {
        POSITION pos=brokerlist->GetHeadPosition();
        while(pos!=nullptr) {
            pop_broker_init &t=brokerlist->GetNext(pos);
            if(!(pop_broker_factory::CheckIfPacked!=nullptr && !pop_broker_factory::CheckIfPacked(t.objname))) {
                printf("-host localhost -np 1 %s -mpi -object=%s\n", abspath, (const char *)t.objname);
            }
        }
    }
}

*/
