/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Base implementation of the parallel object interface class.
 *
 *
 * Modifications :
 * Authors      Date            Comment
 * clementval  ViSaG pro.  Add support for POP-C++ Virtual-Secure version
 * P.Kuonen    2011/3/25   Cosmetic on printed error messages
 * clementval  2011/9/13   Add the method GetAccessPointForThis() to be able to handle the THIS keyword correctly
 */

/*
  Deeply need refactoring:
    POPC_Interface instead of paroc_interface
 */

#include "popc_intface.h"

#include <time.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "paroc_interface.h"
#include "popc_allocator_factory.h"
#include "paroc_buffer_factory_finder.h"
#include "paroc_broker.h"
#include "paroc_combox_factory.h"
#include "paroc_system.h"
#include "paroc_utils.h"
#include "../../config.h"
#include "appservice.ph"

#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL
#include "popc_security_manager.ph"
#endif

#ifndef POPC_CONNECT_TIMEOUT
#define POPC_CONNECT_TIMEOUT 10000
#endif

using namespace std;


paroc_accesspoint paroc_interface::_paroc_nobind;

//binding time out in miliseconds
int paroc_interface::paroc_bind_timeout=10000;

//paroc_interface base class

paroc_interface::paroc_interface() : __paroc_combox(NULL), __paroc_buf(NULL) {
    LOG_DEBUG("Create interface for class %s (OD secure:%s)", ClassName(), (od.isSecureSet())?"true":"false");

    if(od.isSecureSet()) {
        accesspoint.SetSecure();
    }

    _ssh_tunneling=false;
    //__paroc_combox = NULL;
    //__paroc_buf = NULL;
    //_popc_async_construction_thread=NULL;
}

paroc_interface::paroc_interface(const paroc_accesspoint &p) {
    LOG_DEBUG("Create interface (from ap %s) for class %s (OD secure:%s)", p.GetAccessString().c_str(), ClassName(), (od.isSecureSet())?"true":"false");
    _ssh_tunneling = false;
    __paroc_combox = NULL;
    __paroc_buf = NULL;

    // For SSH tunneling
    if(p.IsService()) {
        accesspoint.SetAsService();
    }

    if(!p.IsEmpty()) {
        Bind(p);
    }

    if(p.GetNoAddRef()) {
        //AddRef();
        DecRef();
    }
}

paroc_interface::paroc_interface(const paroc_interface &inf) {
    LOG_DEBUG("Create interface (from interface %s) for class %s (OD secure:%s)", inf.GetAccessPoint().GetAccessString().c_str(), ClassName(), (od.isSecureSet())?"true":"false");
    paroc_accesspoint infAP = inf.GetAccessPoint();
    _ssh_tunneling=false;
    __paroc_combox=NULL;
    __paroc_buf=NULL;
    //_popc_async_construction_thread=NULL;

    if(infAP.IsSecure()) {
        accesspoint.SetSecure();
    }

    if(infAP.IsService()) {
        accesspoint.SetAsService();
    }

    Bind(inf.GetAccessPoint());
}

/* TODO LW: Used by pseudodyn version ?
paroc_interface::paroc_interface(paroc_combox *combox, paroc_buffer *buffer) {
    _ssh_tunneling=false;
    __paroc_combox = combox;
    __paroc_buf = buffer;

    //_popc_async_construction_thread=NULL;
    if(combox != NULL) {
        POPString url;
        combox->GetUrl(url);
        accesspoint.SetAccessString(url);
        if(__paroc_buf == NULL) {
            __paroc_buf=combox->GetBufferFactory()->CreateBuffer();
        }
    }
}
*/


/**
 * Interface destructor
 */
paroc_interface::~paroc_interface() {
    LOG_DEBUG("Destroy interface %s", ClassName());
    Release();
}

paroc_interface & paroc_interface::operator = (const paroc_interface & obj) {
    //  __paroc_combox = NULL;
    //  __paroc_buf = NULL;
    LOG_DEBUG("Bind");
    //Bind(accesspoint);
    //DecRef();
    //Bind(accesspoint);
    //  const paroc_accesspoint &res = obj.GetAccessPoint();

    Release();
    accesspoint = obj.GetAccessPoint();
    if(GetAccessPoint().GetAccessString().c_str()) {
        Bind(accesspoint);
        //AddRef();
    }

    return (*this);
}

void paroc_interface::SetOD(const paroc_od &myod) {
    od = myod;
}

const paroc_od & paroc_interface::GetOD() const {
    return od;
}


// const char * paroc_interface::GetResource() const
// {
//   return resource;
// }

const paroc_accesspoint &  paroc_interface::GetAccessPoint() const {
    return accesspoint;
}

/**
 * Get the accesspoint of the parallel object and set the _noaddref variable to TRUE
 */
const paroc_accesspoint &  paroc_interface::GetAccessPointForThis() {
    accesspoint.SetNoAddRef();
    return accesspoint;
}

void paroc_interface::Serialize(paroc_buffer &buf, bool pack) {

    buf.Push("od", "paroc_od", 1);
    od.Serialize(buf, pack);
    buf.Pop();

    buf.Push("accesspoint", "paroc_accesspoint", 1);
    accesspoint.Serialize(buf, pack);
    buf.Pop();

    paroc_buffer *old = NULL;

    if(&buf == __paroc_buf) {
        LOG_WARNING("Buffers share the same address");// TODO LW: Where does this come from ?
        old = &buf;
        __paroc_buf = __paroc_combox->GetBufferFactory()->CreateBuffer();
    }

    if(pack) {
        int ref = AddRef();
        buf.Push("refcount","int",1);
        buf.Pack(&ref,1);
        buf.Pop();
    } else {
        int ref;
        buf.Push("refcount", "int", 1);
        buf.UnPack(&ref, 1);
        buf.Pop();
        if(ref > 0) {
            Bind(accesspoint);
            LOG_DEBUG("Bound %s", accesspoint.GetAccessString().c_str());
            //AddRef();
            DecRef();
        }
    }

    if(old != NULL) {
        __paroc_buf->Destroy();
        __paroc_buf = old;
    }
}

paroc_od paroc_interface::get_object_description() {
    return od;
}

void paroc_interface::allocate_only() {
    Release();
    POPString objectname = ClassName();
    POPString objectaddress;

    bool localFlag = od.IsLocal();

    const string& hostname = od.getURL();
    const string& batch    = od.getBatch();
    const string& protocol = od.getProtocol();

    // Get the right allocator
    POPC_AllocatorFactory* alloc_factory = POPC_AllocatorFactory::get_instance();
    POPC_Allocator* allocator = NULL;


    // for obscure reason, cannot use strcmp here
    if(protocol == POPC_AllocatorFactory::PREFIX_UDS) {
        allocator = alloc_factory->get_allocator(POPC_Allocator::UDS, POPC_Allocator::INTERCONNECTOR);
    } else {
        if(localFlag || !hostname.empty() || !batch.empty()) {
            allocator = alloc_factory->get_allocator(POPC_Allocator::TCPIP, POPC_Allocator::LOCAL);
        } else {
            allocator = alloc_factory->get_allocator(POPC_Allocator::TCPIP, POPC_Allocator::SSH);
            //Get the POPAppID
            AppCoreService acs(paroc_system::appservice);
            popAppId = acs.GetPOPCAppID();
        }
    }

    if(allocator == NULL) {
        LOG_ERROR("[Core] Allocator is NULL");
    }

    objectaddress = allocator->allocate(objectname, od);
    accesspoint.SetAccessString(objectaddress.c_str());
}

/**
 * Allocate the remote side of the parallel object associated with this interface
 * NOTE: This method should allow various allocation techniques
 */
void paroc_interface::Allocate() {
    allocate_only();

    //Add for SSH tunneling
    if(od.isSecureSet()) {
        accesspoint.SetSecure();
    }

    if(od.isServiceSet()) {
        accesspoint.SetAsService();
    }

    Bind(accesspoint);
}

/**
 *
 */
void paroc_interface::Bind(const paroc_accesspoint &dest) {
    if(dest.IsEmpty()) {
        Release();
        return;
    }

    accesspoint = dest;

    //Choose the protocol and then bind
    POPString prots = dest.GetAccessString();
    POPString od_prots = od.getProtocol();

    auto accesslist = Tokenize(prots);
    ApplyCommPattern(getenv("POPC_COMM_PATTERN"),accesslist);

    auto pref = Tokenize(od_prots);

    if(pref.empty()) {
        LOG_DEBUG("INTERFACE: Bind without preference");
        //No preferred protocol in OD specified, try the first protocol in dest
        for(auto& addr : accesslist){
            try {
                Bind(addr);
                return;
            } catch(std::exception &e) {
                LOG_WARNING("Can not bind to %s. Try next protocol... reason: %s",addr,e.what());
                continue;
            }
            LOG_DEBUG("Successful bind to %s", addr);
        }
    } else {
        //The user specify the protocol in OD, select the preference and match with the access point...
        for(auto& myprot : pref){
            // Find access string that match myprot
            for(auto& addr : accesslist){
                char pattern[1024];
                sprintf(pattern,"%s://*",myprot);
                if(paroc_utils::MatchWildcard(addr,pattern)) {
                    try {
                        Bind(addr);
                        return;
                    } catch(std::exception &e) {
                        LOG_WARNING("Can not bind to %s. Try next protocol... reason: %s",addr,e.what());
                        continue;
                    }
                }
            }
        }
    }

    LOG_WARNING("Cannot find suitable protocol");
    paroc_exception::paroc_throw(OBJECT_BIND_FAIL, ClassName(), "Cannot find suitable protocol");
}

void paroc_interface::Bind(const char *dest) {
    LOG_DEBUG("INTERFACE: Bind (%s) - %s", ClassName(), dest);
    Release();
    if(!dest || *dest==0) {
        return;
    }

    char protsep[] = "://";
    char prot[256];
    char *tmp = (char*)strstr(dest,protsep);
    char defaultprot[] = "socket";

    if(tmp == NULL) {
        // Default protocol: use TCP socket
        strcpy(prot, defaultprot);
    } else {
        int sz = tmp-dest;
        strncpy(prot, dest, sz);
        prot[sz] = 0;
    }

    // Create combox factory
    paroc_combox_factory *fact = paroc_combox_factory::GetInstance();
    POPString p;
    if(!fact) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "No protocol for binding", ClassName());
    }
    fact->GetNames(p);

    // Create combox
    __paroc_combox = fact->Create(prot);
    if(!__paroc_combox) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, ClassName(), "Cannot create factory");
    }

    // Create associated buffer
    __paroc_buf = __paroc_combox->GetBufferFactory()->CreateBuffer();
    __paroc_combox->SetTimeout(paroc_bind_timeout);

    // Check if need proxy
    std::string connect_dest(dest);
    connect_dest = connect_dest.substr(6);

    size_t pos = connect_dest.find("uds_");

    std::string destination_node;
    bool need_redirection = false;
    bool need_uds = false;
    int dest_node, dest_id;
    if(pos != std::string::npos) {
        need_uds = true;
        destination_node = connect_dest.substr(pos+4);
        pos = destination_node.find(".");
        std::string destination_id = destination_node.substr(pos+1);
        destination_node = destination_node.substr(0, destination_node.length()-pos);
        dest_node = atoi(destination_node.c_str());
        dest_id = atoi(destination_id.c_str());
        if(dest_node != paroc_system::popc_local_mpi_communicator_rank) {
            need_redirection = true;
        }
    }

    bool create_return, connect_return;
    if(need_redirection) {

        // Spoof address with the local MPI Communicator
        char* local_address = new char[15];
        snprintf(local_address, 15, "uds_%d.0", paroc_system::popc_local_mpi_communicator_rank);

        LOG_DEBUG("Spoof of address %s to %s", connect_dest.c_str(), local_address);
        create_return = __paroc_combox->Create(local_address, false);
        connect_return = __paroc_combox->Connect(local_address);

        paroc_message_header header(20, 200002, INVOKE_SYNC,"_connection");
        __paroc_buf->Reset();
        __paroc_buf->SetHeader(header);

        __paroc_buf->Push("destnode", "int", 1);
        __paroc_buf->Pack(&dest_node, 1);
        __paroc_buf->Pop();

        __paroc_buf->Push("destid", "int", 1);
        __paroc_buf->Pack(&dest_id, 1);
        __paroc_buf->Pop();

        paroc_connection* connection = __paroc_combox->get_connection();
        popc_send_request(__paroc_buf, connection);
    } else {
        if(need_uds) {
            create_return = __paroc_combox->Create(connect_dest.c_str(), false);
            connect_return = __paroc_combox->Connect(connect_dest.c_str());
        } else {
            create_return = __paroc_combox->Create(0, false);
            connect_return = __paroc_combox->Connect(dest);
        }
    }

    if(create_return && connect_return) {
        int status;
        POPString info;
        POPString peerplatform;
        BindStatus(status, peerplatform, info);
        LOG_DEBUG("INTERFACE: Got bind status %d", status);

        switch(status) {
        case BIND_OK:
            //TODO should be recovered at least in a usage with TCP/IP sockets
            //NegotiateEncoding(info,peerplatform);
            break;

        case BIND_FORWARD_SESSION:
        case BIND_FORWARD_PERMANENT: {
            paroc_accesspoint old(accesspoint);
            paroc_accesspoint newap;
            newap.SetAccessString(info.c_str());
            LOG_INFO("Forward current session to %s", info.c_str());
            Bind(newap);

            if(status == BIND_FORWARD_SESSION) {
                accesspoint = old;
            }

            break;
        }

        default:
            LOG_WARNING("Unknown binding status");
            Release();
            paroc_exception::paroc_throw(POPC_BIND_BAD_REPLY, "Bad reply in interface", ClassName());
        }
    } else {
        int code = errno;

        LOG_DEBUG("Fail to connect from [%s] to [%s]. Reason: %s", paroc_system::GetHost().c_str(),dest,strerror(code));
        Release();
        paroc_exception::paroc_throw(code, "Cannot create or connect return for combox", "Fail to connect from ... to ...");
    }

    __paroc_combox->SetTimeout(-1);
}


void paroc_interface::Release() {

    if(__paroc_combox != NULL) {
        // Decrement reference when the interface release its resources
        //paroc_connection* connection = __paroc_combox->get_connection();
        //if(connection != NULL && !accesspoint.IsService()) {
        //DecRef();
        //}

        // Destroy the combox
        __paroc_combox->Destroy();
        __paroc_combox = NULL;
    }

    if(__paroc_buf != NULL) {
        __paroc_buf->Destroy();
        __paroc_buf = NULL;
    }
}


bool paroc_interface::isBinded() {
    if(__paroc_combox == NULL || __paroc_buf == NULL) {
        return false;
    }
    return true;
}

// ParocCall
void paroc_interface::BindStatus(int &code, POPString &platform, POPString &info) {
    if(!__paroc_combox || !__paroc_buf) {
        return;
    }

    paroc_message_header h(0, 0, INVOKE_SYNC, "BindStatus");
    paroc_mutex_locker lock(_paroc_imutex);
    __paroc_buf->Reset();
    __paroc_buf->SetHeader(h);

    paroc_connection* connection = __paroc_combox->get_connection();
    popc_send_request(__paroc_buf, connection);
    popc_get_response(__paroc_buf, connection);

    __paroc_buf->Push("code","int",1);
    __paroc_buf->UnPack(&code,1);
    __paroc_buf->Pop();

    __paroc_buf->Push("platform","POPString",1);
    __paroc_buf->UnPack(&platform,1);
    __paroc_buf->Pop();

    __paroc_buf->Push("info","POPString",1);
    __paroc_buf->UnPack(&info,1);
    __paroc_buf->Pop();
    LOG_DEBUG("INTERFACE: request bindstatus done");
}


int paroc_interface::AddRef() {
    if(!__paroc_combox || !__paroc_buf) {
        LOG_WARNING("AddRef cannot be called");
        return -1;
    }

    paroc_message_header h(0,1, INVOKE_SYNC,"AddRef");
    paroc_mutex_locker lock(_paroc_imutex);
    __paroc_buf->Reset();
    __paroc_buf->SetHeader(h);

    paroc_connection* connection = __paroc_combox->get_connection();
    popc_send_request(__paroc_buf, connection);
    popc_get_response(__paroc_buf, connection);

    int ret;
    __paroc_buf->Push("refcount","int",1);
    __paroc_buf->UnPack(&ret,1);
    __paroc_buf->Pop();
    return ret;
}

int paroc_interface::DecRef() {
    if(!__paroc_combox || !__paroc_buf) {
        LOG_WARNING("DecRef cannot be called");
        return -1;
    }

    paroc_message_header h(0, 2, INVOKE_SYNC,"DecRef");
    paroc_mutex_locker lock(_paroc_imutex);
    __paroc_buf->Reset();
    __paroc_buf->SetHeader(h);

    paroc_connection* connection = __paroc_combox->get_connection();
    popc_send_request(__paroc_buf, connection);
    popc_get_response(__paroc_buf, connection);

    int ret;
    __paroc_buf->Push("refcount","int",1);
    __paroc_buf->UnPack(&ret,1);
    __paroc_buf->Pop();
    return ret;
}


bool paroc_interface::Encoding(POPString encoding) {
    if(!__paroc_combox || !__paroc_buf) {
        LOG_WARNING("Encoding cannot be called");
        return false;
    }

    paroc_buffer_factory *fact = paroc_buffer_factory_finder::GetInstance()->FindFactory(encoding);

    if(!fact) {
        LOG_ERROR("[CORE] No encoding factory for %s", encoding.c_str());
        return false;
    }

    paroc_message_header h(0, 3, INVOKE_SYNC, "Encoding");
    paroc_mutex_locker lock(_paroc_imutex);
    __paroc_buf->Reset();
    __paroc_buf->SetHeader(h);

    __paroc_buf->Push("encoding", "POPString", 1);
    __paroc_buf->Pack(&encoding, 1);
    __paroc_buf->Pop();

    paroc_connection* connection = __paroc_combox->get_connection();
    popc_send_request(__paroc_buf, connection);
    popc_get_response(__paroc_buf, connection);

    bool ret;
    __paroc_buf->Push("result", "bool", 1);
    __paroc_buf->UnPack(&ret, 1);
    __paroc_buf->Pop();

    if(ret) {
        __paroc_buf->Destroy();
        __paroc_buf = fact->CreateBuffer();
        __paroc_combox->SetBufferFactory(fact);
    }

    return ret;
}

void paroc_interface::Kill() {
    if(!__paroc_combox) {
        LOG_WARNING("Kill cannot be called");
        return;
    }

    paroc_message_header h(0,4, 0 ,"Kill");
    paroc_mutex_locker lock(_paroc_imutex);
    __paroc_buf->Reset();
    __paroc_buf->SetHeader(h);

    paroc_connection* connection = __paroc_combox->get_connection();
    popc_send_request(__paroc_buf, connection);
    __paroc_combox->RecvAck();

    Release();
}

bool paroc_interface::ObjectActive() {
    if(!__paroc_combox || !__paroc_buf) {
        LOG_DEBUG("ObjectActive cannot be called");
        return false;
    }

    paroc_message_header h(0,5, INVOKE_SYNC ,"ObjectActive");
    paroc_mutex_locker lock(_paroc_imutex);
    __paroc_buf->Reset();
    __paroc_buf->SetHeader(h);

    paroc_connection* connection = __paroc_combox->get_connection();
    popc_send_request(__paroc_buf, connection);
    popc_get_response(__paroc_buf, connection);

    bool ret;
    __paroc_buf->Push("result","bool",1);
    __paroc_buf->UnPack(&ret,1);
    __paroc_buf->Pop();
    return ret;
}
#ifdef OD_DISCONNECT
bool paroc_interface::RecvCtrl() {
    int  time_alive;
    int  time_control;
    int oldTimeout = __paroc_combox->GetTimeout();
    od.getCheckConnection(time_alive, time_control);
    if(!__paroc_combox || !__paroc_buf) {
        __paroc_combox->SetTimeout(oldTimeout);
        LOG_ERROR("Error");
        return false;
    };

    char header_name [] = "ObjectAlive\0";
    paroc_message_header h(0,6, INVOKE_SYNC ,header_name);
    paroc_mutex_locker lock(_paroc_imutex);
    while(true) {
        __paroc_combox->SetTimeout(time_control);
        paroc_connection *t = (paroc_connection *) __paroc_combox->Wait();
        if(t != NULL) {
            if(!__paroc_buf->Recv(*__paroc_combox,t)) {
                __paroc_combox->SetTimeout(oldTimeout);
                paroc_exception::paroc_throw("Error in od disconnect 1");
            } else {
                __paroc_combox->SetTimeout(oldTimeout);
                return true;
            }
        }

        __paroc_buf->Reset();
        __paroc_buf->SetHeader(h);

        if(!__paroc_buf->Send(*__paroc_combox)) {
            __paroc_combox->SetTimeout(oldTimeout);
            paroc_exception::paroc_throw("Error in od disconnect 2");
        }
        __paroc_combox->SetTimeout(time_alive);
        if(!__paroc_buf->RecvCtrl(*__paroc_combox)) {
            __paroc_combox->SetTimeout(oldTimeout);
            return true;
        }
    }
    __paroc_combox->SetTimeout(oldTimeout);
    return false;
}
#endif

void paroc_interface::NegotiateEncoding(POPString &enclist, POPString &peerplatform) {
    LOG_DEBUG("INTERFACE: Negotiate encoding start");
    POPString pref = od.getEncoding();

    auto enc_pref = Tokenize(pref);
    auto enc_avail = Tokenize(enclist);

    POPString cur_enc;
    __paroc_combox->GetBufferFactory()->GetBufferName(cur_enc);

    if(enc_pref.empty()) {
        for(auto& enc : enc_avail){
            if(paroc_utils::MatchWildcard(enc,"raw*") && !paroc_utils::isEqual(peerplatform.c_str(),paroc_system::platform.c_str())) {
                continue;
            }

            if(paroc_utils::isncaseEqual(enc,cur_enc.c_str()) || Encoding(enc)) {
                return;
            }
        }
    } else {
        for(auto& test : enc_pref){
            for(auto& enc : enc_avail){
                if(paroc_utils::MatchWildcard(enc,test)) {
                    if(paroc_utils::isncaseEqual(enc,"raw") && !paroc_utils::isEqual(peerplatform.c_str(),paroc_system::platform.c_str())) {
                        continue;
                    }

                    if(paroc_utils::isncaseEqual(enc,cur_enc.c_str()) || Encoding(enc)) {
                        return;
                    }
                }
            }
        }
    }

    paroc_exception::paroc_throw(POPC_NO_ENCODING, ClassName(), "NegociateEncoding failed");
}

int paroc_interface::LocalExec(const char *hostname, const char *codefile, const char *classname, const paroc_accesspoint &jobserv, const paroc_accesspoint &appserv, paroc_accesspoint *objaccess, int howmany, const paroc_od& od) {
    LOG_ERROR("This method has been commented"); // Note: This method is only used by add ons at the moment
    /* TODO should have been restored at least for TCP/IP version
    if(codefile==NULL) {
        return ENOENT;
    }
      popc_signal(SIGCHLD, SIG_IGN);

      while (isspace(*codefile)) codefile++;

      char tmpstr[10240];
      const char *argv[1024];
      char *tmp;

      bool isManual=od.getIsManual();
    #ifdef OD_DISCONNECT
      bool checkConnection=od.getCheckConnection();
    #endif
      POPString ruser;
      POPString rcore;
      const char *rport=NULL;
      POPString batch;
      POPString cwd;

      if (hostname!=NULL&&(tmp=(char*)strchr(hostname,':'))!=NULL) {
          *tmp=0;
          rport=tmp+1;
      }
      od.getUser(ruser);
      od.getCore(rcore);
      od.getBatch(batch);
      od.getDirectory(cwd);

      int n=0;
      //POPString myhost = paroc_system::GetHost();
      //bool islocal=(isManual||hostname==NULL || *hostname==0 || paroc_utils::SameContact(myhost,hostname) || paroc_utils::isEqual(hostname,"localhost") || paroc_utils::isEqual(hostname,"127.0.0.1"));
      if (batch == NULL) {
          if (!islocal) {
              char *tmp=getenv("POPC_RSH");
              argv[n++]=popc_strdup((tmp==NULL)? "/usr/bin/ssh" : tmp);
              //      argv[n++]=popc_strdup("-n");
              // Add user name to host for ssh
              if (ruser!=NULL && *ruser!=0) {
                  char tmpstr[100];
                  sprintf(tmpstr,"%s@%s",(const char*)ruser,(const char*)hostname);
                  argv[n++]=popc_strdup(tmpstr);
              } else {
                  argv[n++]=popc_strdup(hostname);
              }
          }
      } else {
          char tmpstr[100];
          tmp=getenv("POPC_LOCATION");
          if (tmp!=NULL) sprintf(tmpstr,"%s/services/popcobjrun.%s",tmp,(const char*)batch);
          else sprintf(tmpstr,"popcobjrun.%s",(const char*)batch);
          argv[n++]=popc_strdup(tmpstr);
          if (!islocal)
          {

              BatchMgr batchman(paroc_system::appservice);
              sprintf(tmpstr,"-batch-node=%d",batchman.NextNode());
              LOG_DEBUG("%s",tmpstr);
              argv[n++]=popc_strdup(tmpstr);
          }
      }
      //  if (strncmp(codefile, "http://",7)==0 || strncmp(codefile,"ftp://",6)==0)
      //    {
      tmp=getenv("POPC_LOCATION");
      if (tmp!=NULL) sprintf(tmpstr,"%s/services/popcobjrun",tmp);
      else strcpy(tmpstr,"popcobjrun");
      argv[n++]=popc_strdup(tmpstr);
      //    }
      //   else  if ((tmp=getenv("POPC_JOB_EXEC"))!=NULL)
      //    {
      //       argv[n++]=popc_strdup(tmp);
      //    }

      strcpy(tmpstr,codefile);
      char *tok=popc_strtok_r(tmpstr," \t\n",&tmp);
      while (tok!=NULL)
      {
          argv[n++]=popc_strdup(tok);
          tok=popc_strtok_r(NULL," \t\n",&tmp);
      }

      //paroc_combox_socket tmpsock;
    // bool isServer = true;
      // if (!tmpsock.Create(0,isServer)) paroc_exception::paroc_throw_errno();
      // POPString cburl;
      // tmpsock.GetUrl(cburl);

      // sprintf(tmpstr,"-callback=%s", (const char*)cburl);
      // argv[n++]=popc_strdup(tmpstr);

      if (classname != NULL) {
          sprintf(tmpstr,"-object=%s", classname);
          argv[n++]=popc_strdup(tmpstr);
      }

      if (!appserv.IsEmpty()) {
          sprintf(tmpstr,"-appservice=%s",appserv.GetAccessString());
          argv[n++]=popc_strdup(tmpstr);
      }

      if (!jobserv.IsEmpty()) {
          sprintf(tmpstr,"-jobservice=%s",jobserv.GetAccessString());
          argv[n++]=popc_strdup(tmpstr);
      }
      // Select core
      if (rcore!=NULL&&rcore!=0) {
          sprintf(tmpstr,"-core=%s",(const char*)rcore);
          argv[n++]=popc_strdup(tmpstr);
      }

      sprintf(tmpstr, "-address=uds_0.%d", paroc_system::pop_current_local_address);
      argv[n++]=popc_strdup(tmpstr);
      sprintf(tmpstr, "uds://uds_0.%d", paroc_system::pop_current_local_address);
      objaccess->SetAccessString(tmpstr);

      paroc_system::pop_current_local_address++;



      if (rport!=NULL && *rport!=0)
      {
          sprintf(tmpstr,"-socket_port=%s",rport);
          argv[n++]=popc_strdup(tmpstr);
      }
    #ifdef OD_DISCONNECT
      if (checkConnection) {
          sprintf(tmpstr,"-checkConnection");
          argv[n++]=popc_strdup(tmpstr);
      }
    #endif

      if (paroc_od::defaultLocalJob)
      {
          argv[n++]=popc_popc_strdup("-runlocal");
      }

      // Add the working directory as argument
      if (cwd!=NULL && *cwd!=0) {
          sprintf(tmpstr,"-cwd=%s",(const char*)cwd);
          argv[n++]=popc_strdup(tmpstr);
      }

      argv[n]=NULL;

      int ret=0, err=0;
      if (isManual) {
          printf("\nTo launch this object, run this command on the target machine :\n");
          for (int i=0;i<n;i++) printf("%s ", argv[i]);
          printf("\n");
      } else {
    #ifndef NDEBUG
          if (getenv("POPC_DEBUG")) {
              LOG_DEBUG("Launching a new object with command : ");
              fprintf(stderr,"--->");
              for (int i=0;i<n;i++) fprintf(stderr,"%s ", argv[i]);
              fprintf(stderr,"\n");
          }
    #endif
          for (int i=0;i<n;i++) fprintf(stderr,"%s ", argv[i]);
          fprintf(stderr,"\n");
          ret=RunCmd(argv,NULL);
          err=errno;
      }
      for (int i=0;i<n;i++) {
        if (argv[i]!=NULL) {
          free(argv[i]);
        }
      }

      if (ret == -1) {
          LOG_DEBUG("Can not start the object code...");
          paroc_exception::paroc_throw(err, classname);
      }

      //Now get the return paroc_accesspoint....
      tmpsock.SetTimeout(ALLOC_TIMEOUT*1000);

      for (int i=0;i<howmany;i++, objaccess++)
      {

          paroc_buffer_xdr buf1;
          paroc_buffer *buf=&buf1;

          if (!buf->Recv(tmpsock))
          {
              err=errno;
              return err;
          }
          buf->Push("status","int",1);
          buf->UnPack(&n,1);
          buf->Pop();

          if (n!=0)
          {
              return n;
          }
          buf->Push("address","paroc_accesspoint",1);
          objaccess->Serialize(*buf,false);
          buf->Pop();

      }
    */

    return 0;
}

std::vector<char*> paroc_interface::Tokenize(POPString &s) {
    if(s.empty()) {
        return {};
    }
    std::vector<char*> result;

    char sep[]=" \n\t";
    char *ptrptr;
    char *tok=popc_strtok_r(s,sep,&ptrptr);

    while(tok!=NULL) {
        result.push_back(tok);
        tok=popc_strtok_r(NULL,sep,&ptrptr);
    }

    return result;
}

void paroc_interface::ApplyCommPattern(const char *pattern, std::vector<char*>& accesslist) {
    if(!pattern) {
        return;
    }

    POPString p(pattern);
    auto patternlist = Tokenize(p);

    auto ptpos = patternlist.begin();
    auto headpos = accesslist.begin();

    while(ptpos != patternlist.end()){
        auto ptstr = *ptpos++;

        if(!ptstr) {
            continue;
        }

        auto pos = headpos;

        while(pos != accesslist.end()){
            auto old = pos;
            auto t = *pos++;

            if(paroc_utils::MatchWildcard(t, ptstr)) {
                if(headpos != old) {
                    //TODO(BW) this does not seem very smart since iterators will probably be invalidated
                    accesslist.insert(headpos, t);
                    accesslist.erase(old);
                } else {
                    ++headpos;
                    if(headpos == accesslist.end()) {
                        return;
                    }
                }
            }
        }
    }
}

// DEPRECATED
void paroc_interface::paroc_Dispatch(paroc_buffer *buf) {
    if(!buf->Send(*__paroc_combox)) {
        paroc_exception::paroc_throw("Buffer sent failed (old)");
    }
}

// DEPRECATED // TODO LW: See what to do
void paroc_interface::paroc_Response(paroc_buffer *buf) {
    if(!buf->Recv(*__paroc_combox)) {
        paroc_exception::paroc_throw("Buffer receive failed (old)");
    }

    paroc_buffer::CheckAndThrow(*buf);
}

/**
 * Send the current request in the buffer to the endpoint designated by the connection
 */
void paroc_interface::popc_send_request(paroc_buffer *buf, paroc_connection* conn) {
    if(!buf->Send((*__paroc_combox), conn)) {
        paroc_exception::paroc_throw("Buffer sent failed");
    }
    LOG_DEBUG("INTERFACE: paroc_dispatch connection %s", (conn == NULL) ? "is null" : "is not null");
}

/**
 * Get the response from the endpoint designated by the connection
 */
void paroc_interface::popc_get_response(paroc_buffer *buf, paroc_connection* conn) {
    if(!buf->Recv((*__paroc_combox), conn)) {
        paroc_exception::paroc_throw("Buffer receive failed");
    }
    LOG_DEBUG("INTERFACE: paroc_response will disconnect the connection");
    paroc_buffer::CheckAndThrow(*buf);
}

/* ################################################################################################
 *
 *                                SSH TUNNELING FUNCTION
 *
 * ################################################################################################
 */





/**
 * ViSaG : clementval
 * Create a SSH Tunnel from the local IP to the destination IP
 * @param user       User who initiate the SSH Tunnel (not used yet) TODO
 * @param dest_ip    Destination IP of the SSH Tunnel
 * @param dest_port  Destination port of the SSH Tunnel
 * @param local_port Local port of the SSH Tunnel
 * @return PID of the SSH Tunnel on success, -1 if the SSH Tunnel can't be created
 */
int paroc_interface::CreateSSHTunnel(const char *user, const char *dest_ip, int dest_port) {
    LOG_CORE("Create tunnel");
    //Save the SSH Tunnel information
    _ssh_user.erase(_ssh_user.begin(), _ssh_user.end());
    _ssh_user.insert(0, user);
    _ssh_dest_ip.erase(_ssh_dest_ip.begin(), _ssh_dest_ip.end());
    _ssh_dest_ip.insert(0, dest_ip);
    _ssh_dest_port = dest_port;

    _ssh_tunneling = true;
    srand(time(NULL));   //Init the random generator with the current time
    int BUF_SIZE=15;
    char buf[BUF_SIZE];
    FILE *fp;
    int attempt=0;
    int error_code=0;
    int local_port;
    std::ostringstream cmd;

    do {
        error_code=0;
        local_port = (rand() % SSH_PORT_MOD) + SSH_PORT_FIRST;
        LOG_DEBUG("SSH TUNNELING ON %s:%d",dest_ip, local_port);
        cmd.str("");
        cmd.clear();

        cmd << "/usr/bin/ssh -f -N -q -o ExitOnForwardFailure=yes -L" << local_port << ":127.0.0.1:" << dest_port << " " << _ssh_dest_ip << " && echo TUNNEL_OPEN";


        fp = popen(cmd.str().c_str(), "r");
        if(fp==NULL) {
            error_code=-1;
        }
        if(fgets(buf, BUF_SIZE, fp) == NULL) {
            error_code=-1;
        }
    } while(error_code!=0 && attempt++ < SSH_MAX_ATTEMPT);

    if(error_code==0) {
        _ssh_local_port = local_port;
        return local_port;
    } else {
        //paroc_exception::paroc_throw(OBJECT_EXECUTABLE_NOTFOUND, ClassName());
        LOG_WARNING("Executable not found");
    }
    LOG_WARNING("CreateSSHTunnel returned with error code %d", error_code);
    return error_code;
}

/**
 * ViSaG : clementval
 * Kill a SSH Tunnel
 * @param user       User who initiate the SSH Tunnel (not used yet) TODO
 * @param dest_ip    Destination IP of the SSH Tunnel
 * @param dest_port  Destination port of the SSH Tunnel
 * @param local_port Local port of the SSH Tunnel
 * @return PID if the proccess is killed, -1 if the method can't find the SSH Tunnel PID, -2 if the method can't read the PID
 */
int paroc_interface::KillSSHTunnel(const char *user, const char *dest_ip, int dest_port, int local_port) {
    LOG_CORE("Kill SSH");
    _ssh_tunneling = false;
    if(dest_ip == NULL) {
        return -1;
    }

    int BUF_SIZE=100;
    char buf[BUF_SIZE];

    //warning_remove   int error_code=0;

    std::ostringstream cmd;
    cmd << "ps aux | grep \"/usr/bin/ssh -f -N -q -o ExitOnForwardFailure=yes -L" << local_port << ":127.0.0.1:" << dest_port << " " << dest_ip << "\" | grep -v grep | head -n 1 | awk -F\" \" '{print $2}'";
    FILE *fp;
    fp = popen(cmd.str().c_str(), "r");
    if(fp==NULL) {
        return -1;
    }
    if(fgets(buf, BUF_SIZE, fp) == NULL) {
        return -2;
    }
    int pid = atoi(buf);
    LOG_WARNING("KILL SSH-T REQUESTED (user=%s, lport=%d, dport=%d, dip=%s, PID=%d)",user, local_port, dest_port, dest_ip, pid);
    /*if(pid!=0)
       popc_kill(pid, popc_SIGKILL);*/
    return pid;
}

/**
 * ViSaG : clementval
 * Check if the SSH Tunnel is alive
 * @param user       User who initiate the SSH Tunnel (not used yet) TODO
 * @param dest_ip    Destination IP of the SSH Tunnel
 * @param dest_port  Destination port of the SSH Tunnel
 * @param local_port Local port of the SSH Tunnel
 * @return TRUE if the SSH Tunnel is alive, FALSE if the SSH Tunnel is not alive
 */
bool paroc_interface::IsTunnelAlive(const char * /*user*/, const char *dest_ip, int dest_port, int local_port) {
    std::ostringstream cmd;
    int BUF_SIZE=6;
    char res[BUF_SIZE];
    FILE *fp;
    cmd << "ps aux | grep \"/usr/bin/ssh -f -N -o ExitOnForwardFailure=yes -L" << local_port << ":127.0.0.1:" << dest_port << " " << dest_ip << "\" | grep -v grep | awk -F\" \" '{print $2}'";

    fp = popen(cmd.str().c_str(), "r");
    if(fp == NULL) {
        LOG_WARNING("cannot launch %s", cmd.str().c_str());
        return false;
    }

    fgets(res, BUF_SIZE, fp);

    int pid = atoi(res);
    if(pid != 0) {
        return true;
    }
    LOG_WARNING("pid=0");
    return false;
}


