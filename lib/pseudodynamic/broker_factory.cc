/**
 * File : broker_factory.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of broker factory
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 * clementval  10/27/2011  Set services accesspoint cretaed from String as service accesspoint
 * P.Kuonen     18.9.2012       Add "POP-C++ error" in error messages (PEKA)
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mpi.h>

#include "paroc_broker_factory.h"
#include "paroc_utils.h"
#include "paroc_system.h"


paroc_list_broker *paroc_broker_factory::brokerlist=NULL;
ispackedfunc paroc_broker_factory::CheckIfPacked=NULL;

paroc_broker_factory::paroc_broker_factory(initbrokerfunc func, const char *name) {
    if(brokerlist==NULL) {
        brokerlist= new paroc_list_broker;
    }
    if(name==NULL || func==NULL) {
        return;
    }
    if(test(name)) {
        return;
    }
    paroc_broker_init &t=brokerlist->AddTailNew();
    t.func=func;
    t.objname=name;
}

paroc_broker *paroc_broker_factory::Create(const char *objname) {
    DEBUG("Create broker for %s\n", objname);
    if(brokerlist==NULL || objname==NULL) {
        return NULL;
    }

    POSITION pos=brokerlist->GetHeadPosition();
    while(pos!=NULL) {
        paroc_broker_init &t=brokerlist->GetNext(pos);
        if(paroc_utils::isEqual(objname, t.objname)) {
            return t.func();
        }
    }
    return NULL;
}

void paroc_broker_factory::List(paroc_list_string &objlist) {
    if(brokerlist==NULL) {
        return;
    }
    POSITION pos=brokerlist->GetHeadPosition();
    while(pos!=NULL) {
        paroc_broker_init &t=brokerlist->GetNext(pos);
        POPString &str=objlist.AddTailNew();
        str=t.objname;
    }
}

bool paroc_broker_factory::test(const char *objname) {
    if(brokerlist==NULL) {
        return false;
    }
    POSITION pos=brokerlist->GetHeadPosition();
    while(pos!=NULL) {
        paroc_broker_init &test=brokerlist->GetNext(pos);
        if(paroc_utils::isEqual(objname, test.objname)) {
            return true;
        }
    }
    return false;
}


paroc_broker * paroc_broker_factory::Create(int *argc, char ***argv) {
    /**
     * Display the information about the parallel object executable
     */
    char *tmp = paroc_utils::checkremove(argc,argv,"-printmpi");
    if(tmp != NULL) {
        char abspath[1024];
        char *thisfile = getenv("POPC_EXE");
        if(thisfile == NULL) {
            thisfile = (*argv)[0];
        }
        paroc_utils::FindAbsolutePath(thisfile,abspath);
        PrintBrokersMPI(abspath);
        exit(0);
    }
    tmp = paroc_utils::checkremove(argc,argv,"-list");
    if(tmp!=NULL) {
        char abspath[1024];
        char *thisfile=getenv("POPC_EXE");
        if(thisfile==NULL) {
            thisfile=(*argv)[0];
        }
        paroc_utils::FindAbsolutePath(thisfile,abspath);
        PrintBrokers(abspath, strcmp(tmp,"long")==0);
        exit(0);
    }

    char *usage=paroc_utils::checkremove(argc,argv,"-help");
    char *object_classname = paroc_utils::checkremove(argc,argv,"-object=");
    if(usage != NULL || object_classname == NULL) {
        printf("\n Usage:\n\t%s [-help] [-list | -listlong] [-port=<local port>] [-callback=<host:port>] [-appservice=<host:port>] [-nostdio] [-mpi] -object=<objectname>\n",(*argv)[0]);
        return NULL;
    }

    tmp = paroc_utils::checkremove(argc,argv,"-appservice=");
    if(tmp != NULL) {
        paroc_system::appservice.SetAccessString(tmp);
        paroc_system::appservice.SetAsService();  //Set the accesspoint as a service accesspoint
    }

    // Not used in HPC environment
    /*if ((tmp = getenv("POPC_JOBSERVICE")) != NULL) {
        paroc_system::jobservice.SetAccessString(tmp);
    paroc_system::jobservice.SetAsService();  //Set the accesspoint as a service accesspoint
    } else if ((tmp = paroc_utils::checkremove(argc, argv, "-jobservice=")) != NULL) {
        paroc_system::jobservice.SetAccessString(tmp);
    paroc_system::jobservice.SetAsService();  //Set the accesspoint as a service accesspoint
    } else {
        char tmpstr[256];
        DEBUG("Jobservice is not specified. Use the default one!");
        sprintf(tmpstr, "%s:%d", (const char *)paroc_system::GetHost(), DEFAULTPORT);
        paroc_system::jobservice.SetAccessString(tmpstr);
    paroc_system::jobservice.SetAsService();  //Set the accesspoint as a service accesspoint
    }*/

    bool nostdio = (paroc_utils::checkremove(argc, argv, "-nostdio") != NULL);


    // Check the class name for the object to be instantiated
    if(object_classname == NULL || *object_classname == 0) {
        return NULL;
    }

    // Create the real Broker object
    paroc_broker *objbroker = Create(object_classname);
    if(objbroker == NULL) {
        printf("POP-C++ Error: %s: unkown object name\n", (*argv)[1]);
        return NULL;
    }

    // Set the classname for this broker
    paroc_broker::classname = object_classname;


    if(nostdio) {
        close(0);
        close(1);
        close(2);

        open("/dev/null",O_RDONLY);

#ifndef NDEBUG
        char fname[256];
        sprintf(fname,"/tmp/object_%s_%d.log", (const char *)paroc_broker::classname,getpid());
        open(fname,O_WRONLY | O_CREAT,S_IRWXU | S_IRGRP);
        dup2(1,2);
#else
        open("/dev/null",O_WRONLY);
        open("/dev/null",O_WRONLY);
#endif
    }

    return objbroker;
}


void paroc_broker_factory::PrintBrokers(const char *abspath, bool longformat) {
    if(!longformat) {
        printf("List of parallel object classes:\n====\n");
    }
    if(brokerlist!=NULL) {
        POSITION pos=brokerlist->GetHeadPosition();
        while(pos!=NULL) {
            paroc_broker_init &t=brokerlist->GetNext(pos);
            if(!(paroc_broker_factory::CheckIfPacked!=NULL && !paroc_broker_factory::CheckIfPacked(t.objname))) {
                if(longformat) {
                    printf("%s %s %s\n",(const char *)t.objname, (const char *)paroc_system::platform, abspath);
                } else {
                    printf("%s\n",(const char *)t.objname);
                }
            }
        }
    }
    if(!longformat) {
        printf("====\nArchitecture=%s\n",(const char *)paroc_system::platform);
    }
}

void paroc_broker_factory::PrintBrokersMPI(const char *abspath) {
    if(brokerlist!=NULL) {
        POSITION pos=brokerlist->GetHeadPosition();
        while(pos!=NULL) {
            paroc_broker_init &t=brokerlist->GetNext(pos);
            if(!(paroc_broker_factory::CheckIfPacked!=NULL && !paroc_broker_factory::CheckIfPacked(t.objname))) {
                printf("-host localhost -np 1 %s -mpi -object=%s\n", abspath, (const char *)t.objname);
            }
        }
    }
}
