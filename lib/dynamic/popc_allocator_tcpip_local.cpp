/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of the base class POPC_AllocatorFactory. The allocator factory allows to provide the right allocator for
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...).
 *
 *
 */

#include "popc_allocator_tcpip.h"

#include "paroc_system.h"
#include "paroc_exception.h"
#include "paroc_combox.h"
#include "paroc_combox_factory.h"
#include "paroc_broker.h"
#include "paroc_utils.h"
#include "paroc_interface.h"

#include "codemgr.ph"
#include "batchmgr.ph"
#include "appservice.ph"

using namespace std;

#define ALLOC_TIMEOUT 60
/**
 * Allocator over TCP/IP with local mechanism constructor
 */
POPC_Allocator_tcpip_local::POPC_Allocator_tcpip_local() {
}

/**
 * Allocator over TCP/IP with local mechanism destrcutor
 */
POPC_Allocator_tcpip_local::~POPC_Allocator_tcpip_local() {
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @return A string representation of the access-point
 */
POPString POPC_Allocator_tcpip_local::allocate(POPString& objectname, paroc_od& od) {
    POPString codefile;

    char tmpstr[10240];
    char *argv[1024];
    char *tmp;
    const char *rport = NULL;
    bool isManual=od.getIsManual();

    string hostname = od.getURL();
    const string& ruser = od.getUser();
    const string& rcore = od.getCore();
    POPString rarch = od.getArch().c_str();
    const string& batch = od.getBatch();
    const string& cwd = od.getCwd();

    int n = 0;

    if(hostname.empty()) {
        hostname=paroc_system::GetHost().c_str();
    }

    if(!hostname.empty() &&(tmp=(char*)strchr(hostname.c_str(), ':')) !=NULL) {
        *tmp=0;
        rport=tmp+1;
    }

    // Get the executable path name
    codefile = od.getExecutable();
    // If od.executable is not defined, throw an exception as the parallel object couldn't be allocated
    if(codefile.empty()) {
        assert(!paroc_system::appservice.IsEmpty());
        CodeMgr mgr(paroc_system::appservice);
        if(rarch.empty()) {
            rarch=paroc_system::platform;
        }
        if(!mgr.QueryCode(objectname,rarch, codefile)) {
            paroc_exception::paroc_throw(OBJECT_NO_RESOURCE, objectname.c_str(), "QueryCode failed");
        }
    }

    POPString myhost = paroc_system::GetHost();
    bool isLocal = (isManual || hostname.empty() || paroc_utils::SameContact(myhost.c_str(), hostname.c_str()) || (hostname == "localhost") || (hostname == "127.0.0.1"));
    if(batch.empty()) {
        if(!isLocal) {
            char *tmp=getenv("POPC_RSH");
            argv[n++]=popc_strdup((tmp==NULL)? "/usr/bin/ssh" :tmp);
            if(!ruser.empty()) {
                char tmpstr[100];
                sprintf(tmpstr, "%s@%s", ruser.c_str(), hostname.c_str());
                argv[n++] = popc_strdup(tmpstr);
            } else {
                argv[n++] = popc_strdup(hostname.c_str());
            }
        }
    } else {
        char tmpstr[100];
        tmp=getenv("POPC_LOCATION");
        if(tmp!=NULL) {
            sprintf(tmpstr, "%s/services/popcobjrun.%s", tmp, batch.c_str());
        } else {
            sprintf(tmpstr, "popcobjrun.%s", batch.c_str());
        }
        argv[n++]=popc_strdup(tmpstr);
        /*if (!isLocal)
        {
             BatchMgr batchman(paroc_system::appservice);
             sprintf(tmpstr,"-batch-node=%d", batchman.NextNode());
             LOG_DEBUG("%s",tmpstr);
             argv[n++]=popc_strdup(tmpstr);
        }*/
    }
    tmp=getenv("POPC_LOCATION");
    if(tmp!=NULL) {
        sprintf(tmpstr, "%s/services/popcobjrun", tmp);
    } else {
        strcpy(tmpstr, "popcobjrun");
    }
    argv[n++]=popc_strdup(tmpstr);

    strcpy(tmpstr,codefile.c_str());
    char *tok=popc_strtok_r(tmpstr," \t\n",&tmp);
    while(tok!=NULL) {
        argv[n++]=popc_strdup(tok);
        tok=popc_strtok_r(NULL," \t\n",&tmp);
    }

    /**
     * Create a combox to allocate the new parallel object.
     */

    paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
    if(combox_factory == NULL) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname.c_str(), "Combox factory is null");
    }

    paroc_combox* tmpsock = combox_factory->Create("socket");
    if(tmpsock == NULL) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname.c_str(), "Creation of combox failed");
    }

    bool isServer=true;
    if(!tmpsock->Create(0, isServer)) {
        paroc_exception::paroc_throw("Creation of socket failed");
    }

    paroc_connection *connection = tmpsock->get_connection();
    POPString cburl;
    tmpsock->GetUrl(cburl);
    sprintf(tmpstr,"-callback=%s", cburl.c_str());
    argv[n++]=popc_strdup(tmpstr);

    sprintf(tmpstr,"-object=%s", objectname.c_str());
    argv[n++]=popc_strdup(tmpstr);

    if(!paroc_system::appservice.IsEmpty()) {
        sprintf(tmpstr,"-appservice=%s",paroc_system::appservice.GetAccessString());
        argv[n++]=popc_strdup(tmpstr);
    }

    if(!paroc_system::jobservice.IsEmpty()) {
        sprintf(tmpstr,"-jobservice=%s",paroc_system::jobservice.GetAccessString());
        argv[n++]=popc_strdup(tmpstr);
    }

    // Select core
    if(!rcore.empty()) {
        sprintf(tmpstr,"-core=%s",rcore.c_str());
        argv[n++]=popc_strdup(tmpstr);
    }

    // Select core
    if(rport!=NULL&&rport!=0) {
        sprintf(tmpstr,"-socket_port=%s",rport);
        argv[n++]=popc_strdup(tmpstr);
    }

#ifdef OD_DISCONNECT
    if(checkConnection) {
        sprintf(tmpstr,"-checkConnection");
        argv[n++]=popc_strdup(tmpstr);
    }
#endif

    if(paroc_od::defaultLocalJob) {
        argv[n++] = popc_strdup("-runlocal");
    }

    // Add the working directory as argument
    if(!cwd.empty()) {
        sprintf(tmpstr,"-cwd=%s",cwd.c_str());
        argv[n++]=popc_strdup(tmpstr);
    }

    argv[n]=NULL;

    int ret=0, err=0;

    if(isManual) {
        printf("\nTo launch this object, run this command on the target machine :\n");
        for(int i=0; i<n; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    } else {
#ifndef NDEBUG
        std::stringstream ss;
        ss << "--->";
        for(int i=0; i<n; i++) {
            ss << argv[i] << " ";
        }
        LOG_DEBUG("Launching a new object with command : %s", ss.str().c_str());
#endif
        ret=RunCmd(n,argv,NULL);
        err=errno;
    }

    for(int i=0; i<n; i++) if(argv[i]!=NULL) {
            free(argv[i]);
        }

    if(ret==-1) {
        LOG_WARNING("Can not start the object: code %d", ret);
        paroc_exception::paroc_throw(err, objectname.c_str(), "Can not start the object");
    }

    //Now get the return paroc_accesspoint....
    tmpsock->SetTimeout(ALLOC_TIMEOUT*1000);

    paroc_buffer * tmpbuffer = tmpsock->GetBufferFactory()->CreateBuffer();

    if(!tmpbuffer->Recv((*tmpsock), connection)) {
        LOG_WARNING("cannot receive anything");
        paroc_exception::paroc_throw("cannot receive anything");
    }

    paroc_buffer::CheckAndThrow(*tmpbuffer);

    tmpbuffer->Push("status","int",1);
    tmpbuffer->UnPack(&n,1);
    tmpbuffer->Pop();

    if(n!=0) {
        paroc_exception::paroc_throw(n, objectname.c_str(), "n is null");
    }

    POPString objectaddress;
    tmpbuffer->Push("objectaddress","paroc_accesspoint",1);
    tmpbuffer->UnPack(&objectaddress, 1);
    tmpbuffer->Pop();
    tmpbuffer->Destroy();

    tmpsock->Close();

    return objectaddress;
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @param nb          The number of object to allocate in the group
 * @return A pointer to a single combox connected with the group
 */
paroc_combox* POPC_Allocator_tcpip_local::allocate_group(POPString& objectname, paroc_od& od, int nb) {

    /* Allocation process here */

    return NULL;
}
