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

#include "popc_intface.h"

#include <time.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "pop_interface.h"
#include "pop_allocator_factory.h"
#include "pop_buffer_factory_finder.h"
#include "pop_broker.h"
#include "pop_combox_factory.h"
#include "pop_system.h"
#include "pop_utils.h"
#include "../../config.h"
#include "appservice.ph"

#if defined POP_SECURE || defined POP_SECURE_VIRTUAL
#include "popc_security_manager.ph"
#endif

#ifndef POP_CONNECT_TIMEOUT
#define POP_CONNECT_TIMEOUT 10000
#endif


pop_accesspoint pop_interface::_pop_nobind;

//binding time out in miliseconds
int pop_interface::pop_bind_timeout=10000;

//pop_interface base class

pop_interface::pop_interface() : __pop_combox(nullptr), __pop_buf(nullptr) {
    LOG_DEBUG("Create interface for class %s (OD secure:%s)", ClassName(), (od.isSecureSet())?"true":"false");

    if(od.isSecureSet()) {
        accesspoint.SetSecure();
    }

    _ssh_tunneling=false;
    //__pop_combox = nullptr;
    //__pop_buf = nullptr;
    //_popc_async_construction_thread=nullptr;
}

pop_interface::pop_interface(const pop_accesspoint &p) {
    LOG_DEBUG("Create interface (from ap %s) for class %s (OD secure:%s)", p.GetAccessString().c_str(), ClassName(), (od.isSecureSet())?"true":"false");
    _ssh_tunneling = false;
    __pop_combox = nullptr;
    __pop_buf = nullptr;

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

pop_interface::pop_interface(const pop_interface &inf) {
    LOG_DEBUG("Create interface (from interface %s) for class %s (OD secure:%s)", inf.GetAccessPoint().GetAccessString().c_str(), ClassName(), (od.isSecureSet())?"true":"false");
    pop_accesspoint infAP = inf.GetAccessPoint();
    _ssh_tunneling=false;
    __pop_combox=nullptr;
    __pop_buf=nullptr;
    //_popc_async_construction_thread=nullptr;

    if(infAP.IsSecure()) {
        accesspoint.SetSecure();
    }

    if(infAP.IsService()) {
        accesspoint.SetAsService();
    }

    Bind(inf.GetAccessPoint());
}

/**
 * Interface destructor
 */
pop_interface::~pop_interface() {
    LOG_DEBUG("Destroy interface %s", ClassName());
    Release();
}

pop_interface & pop_interface::operator = (const pop_interface & obj) {
    //  __pop_combox = nullptr;
    //  __pop_buf = nullptr;
    LOG_DEBUG("Bind");
    //Bind(accesspoint);
    //DecRef();
    //Bind(accesspoint);
    //  const pop_accesspoint &res = obj.GetAccessPoint();

    Release();
    accesspoint = obj.GetAccessPoint();
    if(GetAccessPoint().GetAccessString().c_str()) {
        Bind(accesspoint);
        //AddRef();
    }

    return (*this);
}

void pop_interface::SetOD(const pop_od &myod) {
    od = myod;
}

const pop_od & pop_interface::GetOD() const {
    return od;
}


// const char * pop_interface::GetResource() const
// {
//   return resource;
// }

const pop_accesspoint &  pop_interface::GetAccessPoint() const {
    return accesspoint;
}

/**
 * Get the accesspoint of the parallel object and set the _noaddref variable to TRUE
 */
const pop_accesspoint &  pop_interface::GetAccessPointForThis() {
    accesspoint.SetNoAddRef();
    return accesspoint;
}

void pop_interface::Serialize(pop_buffer &buf, bool pack) {

    buf.Push("od", "pop_od", 1);
    od.Serialize(buf, pack);
    buf.Pop();

    buf.Push("accesspoint", "pop_accesspoint", 1);
    accesspoint.Serialize(buf, pack);
    buf.Pop();

    pop_buffer *old = nullptr;

    if(&buf == __pop_buf) {
        LOG_WARNING("Buffers share the same address");// TODO LW: Where does this come from ?
        old = &buf;
        __pop_buf = __pop_combox->GetBufferFactory()->CreateBuffer();
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

    if(old != nullptr) {
        delete __pop_buf;
        __pop_buf = old;
    }
}

pop_od pop_interface::get_object_description() {
    return od;
}

void pop_interface::allocate_only() {
    Release();

    std::string objectname = ClassName();
    std::string objectaddress;

    // Get the right allocator
    pop_allocatorFactory* alloc_factory = pop_allocatorFactory::get_instance();
    pop_allocator* allocator = nullptr;

    if(od.getProtocol() == pop_allocatorFactory::PREFIX_UDS) {
        allocator = alloc_factory->get_allocator(pop_allocator::UDS, pop_allocator::LOCAL);

        LOG_DEBUG_T("IFACE", "Allocate %s with UDS(local)", objectname.c_str());

        //TODO(BW) In MPI mode, this should be used (add some condition)
        //allocator = alloc_factory->get_allocator(pop_allocator::UDS, pop_allocator::INTERCONNECTOR);
    } else {
        bool localFlag = od.IsLocal();

        if(localFlag || !od.getURL().empty() || !od.getBatch().empty()) {
            allocator = alloc_factory->get_allocator(pop_allocator::TCPIP, pop_allocator::LOCAL);

            LOG_DEBUG_T("IFACE", "Allocate %s with TCP(local)", objectname.c_str());
        } else {
            allocator = alloc_factory->get_allocator(pop_allocator::TCPIP, pop_allocator::SSH);

            LOG_DEBUG_T("IFACE", "Allocate %s with TCP(ssh)", objectname.c_str());

            //Get the POPAppID
            AppCoreService acs(pop_system::appservice);
            popAppId = acs.GetPOPCAppID();
        }
    }

    if(!allocator) {
        LOG_ERROR("[Core] Allocator is nullptr");
    }

    objectaddress = allocator->allocate(objectname, od);
    accesspoint.SetAccessString(objectaddress.c_str());
}

/**
 * Allocate the remote side of the parallel object associated with this interface
 * NOTE: This method should allow various allocation techniques
 */
void pop_interface::Allocate() {
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
void pop_interface::Bind(const pop_accesspoint &dest) {
    if(dest.IsEmpty()) {
        Release();
        return;
    }

    accesspoint = dest;

    //Choose the protocol and then bind
    std::string prots = dest.GetAccessString();
    std::string od_prots = od.getProtocol();

    auto accesslist = Tokenize(prots);
    const char* tmp = getenv("POPC_COMM_PATTERN");
    ApplyCommPattern(tmp?tmp:"",accesslist);

    auto pref = Tokenize(od_prots);

    if(pref.empty()) {
        LOG_DEBUG("INTERFACE: Bind without preference");
        //No preferred protocol in OD specified, try the first protocol in dest
        for(auto& addr : accesslist){
            try {
                Bind(addr.c_str());
                return;
            } catch(std::exception &e) {
                LOG_WARNING("Can not bind to %s. Try next protocol... reason: %s",addr.c_str(),e.what());
                continue;
            }
            LOG_DEBUG("Successful bind to %s", addr.c_str());
        }
    } else {
        //The user specify the protocol in OD, select the preference and match with the access point...
        for(auto& myprot : pref){
            // Find access string that match myprot
            for(auto& addr : accesslist){
                char pattern[1024];
                sprintf(pattern,"%s://*",myprot.c_str());
                if(pop_utils::MatchWildcard(addr,pattern)) {
                    try {
                        Bind(addr.c_str());
                        return;
                    } catch(std::exception &e) {
                        LOG_WARNING("Can not bind to %s. Try next protocol... reason: %s",addr.c_str(),e.what());
                        continue;
                    }
                }
            }
        }
    }

    LOG_WARNING("Cannot find suitable protocol");
    pop_exception::pop_throw(OBJECT_BIND_FAIL, ClassName(), "Cannot find suitable protocol");
}

void pop_interface::Bind(const char *dest) {
    LOG_DEBUG("INTERFACE: Bind (%s) - %s", ClassName(), dest);
    Release();
    if(!dest || *dest==0) {
        return;
    }

    char protsep[] = "://";
    char prot[256];
    char *tmp = (char*)strstr(dest,protsep);
    char defaultprot[] = "socket";

    if(tmp == nullptr) {
        // Default protocol: use TCP socket
        strcpy(prot, defaultprot);
    } else {
        int sz = tmp-dest;
        strncpy(prot, dest, sz);
        prot[sz] = 0;
    }

    // Create combox factory
    pop_combox_factory *fact = pop_combox_factory::GetInstance();
    std::string p;
    if(!fact) {
        pop_exception::pop_throw(POP_NO_PROTOCOL, "No protocol for binding", ClassName());
    }
    fact->GetNames(p);

    // Create combox
    __pop_combox = fact->Create(prot);
    if(!__pop_combox) {
        pop_exception::pop_throw(POP_NO_PROTOCOL, ClassName(), "Cannot create combox from factory");
    }

    // Create associated buffer
    __pop_buf = __pop_combox->GetBufferFactory()->CreateBuffer();
    __pop_combox->SetTimeout(pop_bind_timeout);

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
        if(dest_node != pop_system::popc_local_mpi_communicator_rank) {
            need_redirection = true;
        }
    }

    bool create_return, connect_return;
    if(need_redirection) {

        // Spoof address with the local MPI Communicator
        // TODO LW: Why do we have this here ????
        char* local_address = new char[15];
        snprintf(local_address, 15, "uds_%d.0", pop_system::popc_local_mpi_communicator_rank);

        LOG_DEBUG("Spoof of address %s to %s", connect_dest.c_str(), local_address);
        create_return = __pop_combox->Create(local_address, false);
        connect_return = __pop_combox->Connect(local_address);

        pop_message_header header(20, 200002, INVOKE_SYNC,"_connection");
        __pop_buf->Reset();
        __pop_buf->SetHeader(header);

        __pop_buf->Push("destnode", "int", 1);
        __pop_buf->Pack(&dest_node, 1);
        __pop_buf->Pop();

        __pop_buf->Push("destid", "int", 1);
        __pop_buf->Pack(&dest_id, 1);
        __pop_buf->Pop();

        pop_connection* connection = __pop_combox->get_connection();
        popc_send_request(__pop_buf, connection);
    } else {
        if(need_uds) {
            create_return = __pop_combox->Create(connect_dest.c_str(), false);
            connect_return = __pop_combox->Connect(connect_dest.c_str());
        } else {
            create_return = __pop_combox->Create(0, false);
            connect_return = __pop_combox->Connect(dest);
        }
    }

    if(create_return && connect_return) {
        int status;
        std::string info;
        std::string peerplatform;
        BindStatus(status, peerplatform, info);
        LOG_DEBUG("INTERFACE: Got bind status %d", status);

        switch(status) {
        case BIND_OK:
            //TODO should be recovered at least in a usage with TCP/IP sockets
            //NegotiateEncoding(info,peerplatform);
            break;

        case BIND_FORWARD_SESSION:
        case BIND_FORWARD_PERMANENT: {
            pop_accesspoint old(accesspoint);
            pop_accesspoint newap;
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
            pop_exception::pop_throw(POP_BIND_BAD_REPLY, "Bad reply in interface", ClassName());
        }
    } else {
        int code = errno;

        LOG_DEBUG("Fail to connect from [%s] to [%s]. Reason: %s", pop_system::GetHost().c_str(),dest,strerror(code));
        Release();
        pop_exception::pop_throw(code, "Cannot create or connect return for combox", "Fail to connect from ... to ...");
    }

    __pop_combox->SetTimeout(-1);
}


void pop_interface::Release() {

    if(__pop_combox != nullptr) {
        // Decrement reference when the interface release its resources
        //pop_connection* connection = __pop_combox->get_connection();
        //if(connection != nullptr && !accesspoint.IsService()) {
        //DecRef();
        //}

        // Destroy the combox
        delete __pop_combox;
        __pop_combox = nullptr;
    }

    if(__pop_buf != nullptr) {
        delete __pop_buf;
        __pop_buf = nullptr;
    }
}


bool pop_interface::isBinded() {
    if(__pop_combox == nullptr || __pop_buf == nullptr) {
        return false;
    }
    return true;
}

// PopCall
void pop_interface::BindStatus(int &code, std::string &platform, std::string &info) {
    if(!__pop_combox || !__pop_buf) {
        return;
    }

    pop_message_header h(0, 0, INVOKE_SYNC, "BindStatus");
    pop_mutex_locker lock(_pop_imutex);
    __pop_buf->Reset();
    __pop_buf->SetHeader(h);

    pop_connection* connection = __pop_combox->get_connection();
    popc_send_request(__pop_buf, connection);
    popc_get_response(__pop_buf, connection);

    __pop_buf->Push("code","int",1);
    __pop_buf->UnPack(&code,1);
    __pop_buf->Pop();

    __pop_buf->Push("platform","std::string",1);
    __pop_buf->UnPack(&platform,1);
    __pop_buf->Pop();

    __pop_buf->Push("info","std::string",1);
    __pop_buf->UnPack(&info,1);
    __pop_buf->Pop();
    LOG_DEBUG("INTERFACE: request bindstatus done");
}


int pop_interface::AddRef() {
    if(!__pop_combox || !__pop_buf) {
        LOG_WARNING("AddRef cannot be called");
        return -1;
    }

    pop_message_header h(0,1, INVOKE_SYNC,"AddRef");
    pop_mutex_locker lock(_pop_imutex);
    __pop_buf->Reset();
    __pop_buf->SetHeader(h);

    pop_connection* connection = __pop_combox->get_connection();
    popc_send_request(__pop_buf, connection);
    popc_get_response(__pop_buf, connection);

    int ret;
    __pop_buf->Push("refcount","int",1);
    __pop_buf->UnPack(&ret,1);
    __pop_buf->Pop();
    return ret;
}

int pop_interface::DecRef() {
    if(!__pop_combox || !__pop_buf) {
        LOG_WARNING("DecRef cannot be called");
        return -1;
    }

    pop_message_header h(0, 2, INVOKE_SYNC,"DecRef");
    pop_mutex_locker lock(_pop_imutex);
    __pop_buf->Reset();
    __pop_buf->SetHeader(h);

    pop_connection* connection = __pop_combox->get_connection();
    popc_send_request(__pop_buf, connection);
    popc_get_response(__pop_buf, connection);

    int ret;
    __pop_buf->Push("refcount","int",1);
    __pop_buf->UnPack(&ret,1);
    __pop_buf->Pop();
    return ret;
}


bool pop_interface::Encoding(std::string encoding) {
    if(!__pop_combox || !__pop_buf) {
        LOG_WARNING("Encoding cannot be called");
        return false;
    }

    pop_buffer_factory *fact = pop_buffer_factory_finder::GetInstance()->FindFactory(encoding);

    if(!fact) {
        LOG_ERROR("[CORE] No encoding factory for %s", encoding.c_str());
        return false;
    }

    pop_message_header h(0, 3, INVOKE_SYNC, "Encoding");
    pop_mutex_locker lock(_pop_imutex);
    __pop_buf->Reset();
    __pop_buf->SetHeader(h);

    __pop_buf->Push("encoding", "std::string", 1);
    __pop_buf->Pack(&encoding, 1);
    __pop_buf->Pop();

    pop_connection* connection = __pop_combox->get_connection();
    popc_send_request(__pop_buf, connection);
    popc_get_response(__pop_buf, connection);

    bool ret;
    __pop_buf->Push("result", "bool", 1);
    __pop_buf->UnPack(&ret, 1);
    __pop_buf->Pop();

    if(ret) {
        delete __pop_buf;
        __pop_buf = fact->CreateBuffer();
        __pop_combox->SetBufferFactory(fact);
    }
    
    return ret;
}

void pop_interface::Kill() {
    if(!__pop_combox) {
        LOG_WARNING("Kill cannot be called");
        return;
    }

    pop_message_header h(0,4, 0 ,"Kill");
    pop_mutex_locker lock(_pop_imutex);
    __pop_buf->Reset();
    __pop_buf->SetHeader(h);

    pop_connection* connection = __pop_combox->get_connection();
    popc_send_request(__pop_buf, connection);
    __pop_combox->RecvAck();

    Release();
}

bool pop_interface::ObjectActive() {
    if(!__pop_combox || !__pop_buf) {
        LOG_DEBUG("ObjectActive cannot be called");
        return false;
    }

    pop_message_header h(0,5, INVOKE_SYNC ,"ObjectActive");
    pop_mutex_locker lock(_pop_imutex);
    __pop_buf->Reset();
    __pop_buf->SetHeader(h);

    pop_connection* connection = __pop_combox->get_connection();
    popc_send_request(__pop_buf, connection);
    popc_get_response(__pop_buf, connection);

    bool ret;
    __pop_buf->Push("result","bool",1);
    __pop_buf->UnPack(&ret,1);
    __pop_buf->Pop();
    return ret;
}
#ifdef OD_DISCONNECT
bool pop_interface::RecvCtrl() {
    int  time_alive;
    int  time_control;
    int oldTimeout = __pop_combox->GetTimeout();
    od.getCheckConnection(time_alive, time_control);
    if(!__pop_combox || !__pop_buf) {
        __pop_combox->SetTimeout(oldTimeout);
        LOG_ERROR("Error");
        return false;
    };

    char header_name [] = "ObjectAlive\0";
    pop_message_header h(0,6, INVOKE_SYNC ,header_name);
    pop_mutex_locker lock(_pop_imutex);
    while(true) {
        __pop_combox->SetTimeout(time_control);
        pop_connection *t = (pop_connection *) __pop_combox->Wait();
        if(t != nullptr) {
            if(!__pop_buf->Recv(*__pop_combox,t)) {
                __pop_combox->SetTimeout(oldTimeout);
                pop_exception::pop_throw("Error in od disconnect 1");
            } else {
                __pop_combox->SetTimeout(oldTimeout);
                return true;
            }
        }

        __pop_buf->Reset();
        __pop_buf->SetHeader(h);

        if(!__pop_buf->Send(*__pop_combox)) {
            __pop_combox->SetTimeout(oldTimeout);
            pop_exception::pop_throw("Error in od disconnect 2");
        }
        __pop_combox->SetTimeout(time_alive);
        if(!__pop_buf->RecvCtrl(*__pop_combox)) {
            __pop_combox->SetTimeout(oldTimeout);
            return true;
        }
    }
    __pop_combox->SetTimeout(oldTimeout);
    return false;
}
#endif

void pop_interface::NegotiateEncoding(std::string &enclist, std::string &peerplatform) {
    LOG_DEBUG("INTERFACE: Negotiate encoding start");
    std::string pref = od.getEncoding();

    auto enc_pref = Tokenize(pref);
    auto enc_avail = Tokenize(enclist);

    std::string cur_enc;
    __pop_combox->GetBufferFactory()->GetBufferName(cur_enc);

    if(enc_pref.empty()) {
        for(auto& enc : enc_avail){
            if(pop_utils::MatchWildcard(enc,"raw*") && !pop_utils::isEqual(peerplatform.c_str(),pop_system::platform.c_str())) {
                continue;
            }

            if(pop_utils::isncaseEqual(enc.c_str(),cur_enc.c_str()) || Encoding(enc)) {
                return;
            }
        }
    } else {
        for(auto& test : enc_pref){
            for(auto& enc : enc_avail){
                if(pop_utils::MatchWildcard(enc,test)) {
                    if(pop_utils::isncaseEqual(enc,"raw") && !pop_utils::isEqual(peerplatform.c_str(),pop_system::platform.c_str())) {
                        continue;
                    }

                    if(pop_utils::isncaseEqual(enc,cur_enc) || Encoding(enc)) {
                        return;
                    }
                }
            }
        }
    }

    pop_exception::pop_throw(POP_NO_ENCODING, ClassName(), "NegociateEncoding failed");
}

int pop_interface::LocalExec(const char *hostname, const char *codefile, const char *classname, const pop_accesspoint &jobserv, const pop_accesspoint &appserv, pop_accesspoint *objaccess, int howmany, const pop_od& od) {
    LOG_ERROR("This method has been commented"); // Note: This method is only used by add ons at the moment

    /* TODO should have been restored at least for TCP/IP version
    if(codefile==nullptr) {
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
      std::string ruser;
      std::string rcore;
      const char *rport=nullptr;
      std::string batch;
      std::string cwd;

      if (hostname!=nullptr&&(tmp=(char*)strchr(hostname,':'))!=nullptr) {
          *tmp=0;
          rport=tmp+1;
      }
      ruser = od.getUser();
      rcore = od.getCore();
      batch = od.getBatch();
      cwd   = od.getCwd();

      int n=0;
      //std::string myhost = pop_system::GetHost();
      //bool islocal=(isManual||hostname==nullptr || *hostname==0 || pop_utils::SameContact(myhost,hostname) || pop_utils::isEqual(hostname,"localhost") || pop_utils::isEqual(hostname,"127.0.0.1"));
      if (batch == nullptr) {
          if (!islocal) {
              char *tmp=getenv("POP_RSH");
              argv[n++]=popc_strdup((tmp==nullptr)? "/usr/bin/ssh" : tmp);
              //      argv[n++]=popc_strdup("-n");
              // Add user name to host for ssh
              if (ruser!=nullptr && *ruser!=0) {
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
          if (tmp!=nullptr) sprintf(tmpstr,"%s/services/popcobjrun.%s",tmp,(const char*)batch);
          else sprintf(tmpstr,"popcobjrun.%s",(const char*)batch);
          argv[n++]=popc_strdup(tmpstr);
          if (!islocal)
          {

              BatchMgr batchman(pop_system::appservice);
              sprintf(tmpstr,"-batch-node=%d",batchman.NextNode());
              LOG_DEBUG("%s",tmpstr);
              argv[n++]=popc_strdup(tmpstr);
          }
      }
      //  if (strncmp(codefile, "http://",7)==0 || strncmp(codefile,"ftp://",6)==0)
      //    {
      tmp=getenv("POPC_LOCATION");
      if (tmp!=nullptr) sprintf(tmpstr,"%s/services/popcobjrun",tmp);
      else strcpy(tmpstr,"popcobjrun");
      argv[n++]=popc_strdup(tmpstr);
      //    }
      //   else  if ((tmp=getenv("POP_JOB_EXEC"))!=nullptr)
      //    {
      //       argv[n++]=popc_strdup(tmp);
      //    }

      strcpy(tmpstr,codefile);
      char *tok=popc_strtok_r(tmpstr," \t\n",&tmp);
      while (tok!=nullptr)
      {
          argv[n++]=popc_strdup(tok);
          tok=popc_strtok_r(nullptr," \t\n",&tmp);
      }

      //pop_combox_socket tmpsock;
    // bool isServer = true;
      // if (!tmpsock.Create(0,isServer)) pop_exception::pop_throw_errno();
      // std::string cburl;
      // tmpsock.GetUrl(cburl);

      // sprintf(tmpstr,"-callback=%s", (const char*)cburl);
      // argv[n++]=popc_strdup(tmpstr);

      if (classname != nullptr) {
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
    if(!rcore.empty()) {
        sprintf(tmpstr,"-core=%s",rcore.c_str());
          argv[n++]=popc_strdup(tmpstr);
      }

      sprintf(tmpstr, "-address=uds_0.%d", pop_system::pop_current_local_address);
      argv[n++]=popc_strdup(tmpstr);
      sprintf(tmpstr, "uds://uds_0.%d", pop_system::pop_current_local_address);
      objaccess->SetAccessString(tmpstr);

      pop_system::pop_current_local_address++;



      if (!rport.empty())
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

      if (pop_od::defaultLocalJob)
      {
          argv[n++]=popc_popc_strdup("-runlocal");
      }

      // Add the working directory as argument
    if(!cwd.empty()) {
        sprintf(tmpstr,"-cwd=%s",cwd.c_str());
        argv[n++]=strdup(tmpstr);
      }

      argv[n]=nullptr;

      int ret=0, err=0;
      if (isManual) {
          printf("\nTo launch this object, run this command on the target machine :\n");
          for (int i=0;i<n;i++) printf("%s ", argv[i]);
          printf("\n");
      } else {
    #ifndef NDEBUG
          if (getenv("POP_DEBUG")) {
              LOG_DEBUG("Launching a new object with command : ");
              fprintf(stderr,"--->");
              for (int i=0;i<n;i++) fprintf(stderr,"%s ", argv[i]);
              fprintf(stderr,"\n");
          }
    #endif
          for (int i=0;i<n;i++) fprintf(stderr,"%s ", argv[i]);
          fprintf(stderr,"\n");
          ret=RunCmd(argv,nullptr);
          err=errno;
      }
      for (int i=0;i<n;i++) {
        if (argv[i]!=nullptr) {
          free(argv[i]);
        }
      }

      if (ret == -1) {
          LOG_DEBUG("Can not start the object code...");
          pop_exception::pop_throw(err, classname);
      }

      //Now get the return pop_accesspoint....
      tmpsock.SetTimeout(ALLOC_TIMEOUT*1000);

      for (int i=0;i<howmany;i++, objaccess++)
      {

          pop_buffer_xdr buf1;
          pop_buffer *buf=&buf1;

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
          buf->Push("address","pop_accesspoint",1);
          objaccess->Serialize(*buf,false);
          buf->Pop();

      }
    */

    return 0;
}

std::vector<std::string> pop_interface::Tokenize(const std::string &s) {
    if(s.empty()) {
        return {};
    }
    std::vector<std::string> tokens;
    popc_tokenize_r(tokens,s, " \n\t");
    return tokens;
}

void pop_interface::ApplyCommPattern(const std::string& pattern, std::vector<std::string>& accesslist) {
    if(pattern.empty()) {
        return;
    }

    auto patternlist = Tokenize(pattern);
    auto headpos = accesslist.begin();

    for(auto ptstr : patternlist){
        auto pos = headpos;

        while(pos != accesslist.end()){
            auto old = pos;
            auto t = *pos++;

            if(pop_utils::MatchWildcard(t, ptstr)) {
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

/**
 * Send the current request in the buffer to the endpoint designated by the connection
 */
void pop_interface::popc_send_request(pop_buffer *buf, pop_connection* conn) {
    if(!buf->Send((*__pop_combox), conn)) {
        pop_exception::pop_throw("Buffer sent failed");
    }
    LOG_DEBUG("INTERFACE: paroc_dispatch connection %s", (conn == nullptr) ? "is null" : "is not null");
}

/**
 * Get the response from the endpoint designated by the connection
 */
void pop_interface::popc_get_response(pop_buffer *buf, pop_connection* conn) {
    if(!buf->Recv((*__pop_combox), conn)) {
        pop_exception::pop_throw("Buffer receive failed");
    }
    LOG_DEBUG("INTERFACE: paroc_response will disconnect the connection");
    pop_buffer::CheckAndThrow(*buf);
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
int pop_interface::CreateSSHTunnel(const char *user, const char *dest_ip, int dest_port) {
    LOG_CORE("Create tunnel");
    //Save the SSH Tunnel information
    _ssh_user.erase(_ssh_user.begin(), _ssh_user.end());
    _ssh_user.insert(0, user);
    _ssh_dest_ip.erase(_ssh_dest_ip.begin(), _ssh_dest_ip.end());
    _ssh_dest_ip.insert(0, dest_ip);
    _ssh_dest_port = dest_port;

    _ssh_tunneling = true;
    srand(time(nullptr));   //Init the random generator with the current time
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
        if(fp==nullptr) {
            error_code=-1;
        }
        if(fgets(buf, BUF_SIZE, fp) == nullptr) {
            error_code=-1;
        }
    } while(error_code!=0 && attempt++ < SSH_MAX_ATTEMPT);

    if(error_code==0) {
        _ssh_local_port = local_port;
        return local_port;
    } else {
        //pop_exception::pop_throw(OBJECT_EXECUTABLE_NOTFOUND, ClassName());
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
int pop_interface::KillSSHTunnel(const char *user, const char *dest_ip, int dest_port, int local_port) {
    LOG_CORE("Kill SSH");
    _ssh_tunneling = false;
    if(dest_ip == nullptr) {
        return -1;
    }

    int BUF_SIZE=100;
    char buf[BUF_SIZE];

    //warning_remove   int error_code=0;

    std::ostringstream cmd;
    cmd << "ps aux | grep \"/usr/bin/ssh -f -N -q -o ExitOnForwardFailure=yes -L" << local_port << ":127.0.0.1:" << dest_port << " " << dest_ip << "\" | grep -v grep | head -n 1 | awk -F\" \" '{print $2}'";
    FILE *fp;
    fp = popen(cmd.str().c_str(), "r");
    if(fp==nullptr) {
        return -1;
    }
    if(fgets(buf, BUF_SIZE, fp) == nullptr) {
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
bool pop_interface::IsTunnelAlive(const char * /*user*/, const char *dest_ip, int dest_port, int local_port) {
    std::ostringstream cmd;
    int BUF_SIZE=6;
    char res[BUF_SIZE];
    FILE *fp;
    cmd << "ps aux | grep \"/usr/bin/ssh -f -N -o ExitOnForwardFailure=yes -L" << local_port << ":127.0.0.1:" << dest_port << " " << dest_ip << "\" | grep -v grep | awk -F\" \" '{print $2}'";

    fp = popen(cmd.str().c_str(), "r");
    if(fp == nullptr) {
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


