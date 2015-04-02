/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief interface base declaration for parclass objects
 *
 * UPDATES:
 * Authors      Date              Comment
 * clementval 2011/09/13  Add the method GetAccessPointForThis() to be able to handle the THIS keyword correctly
 * clementval 2012/08/22  Add thread variable for asynchronous parallel object allocation
 */

#ifndef _POPC_INTERFACE_CORE_H
#define _POPC_INTERFACE_CORE_H

#include <stdio.h>
#include <string>
#include <pthread.h>    // Added for asynchronous object construction

#include <paroc_base.h>
#include <pop_accesspoint.h>
#include <paroc_od.h>
#include <pop_buffer.h>
#include <paroc_allocobj.h>
#include "popwayback.h"


#define BIND_OK 0
#define BIND_FORWARD_SESSION 1
#define BIND_FORWARD_PERMANENT 2

#define POPC_ALLOC_RETRY 3


/**
 * @class pop_interface
 * @brief Interface base declaration for parclass objects, used by POP-C++ runtime.
 *
 *
 * @author Tuan Anh Nguyen
 *
 */
class pop_interface: paroc_base {
public:
    pop_interface();
    pop_interface(const pop_accesspoint &p);
    pop_interface(const pop_interface &inf);

    virtual ~pop_interface();

    //Assign an interface from the others.....
    pop_interface & operator = (const pop_interface &obj);

    virtual void SetOD(const paroc_od &myod);
    virtual const paroc_od &GetOD() const;

    //  virtual const char * GetResource() const;

    const pop_accesspoint & GetAccessPoint() const;

    //Get the access point and set the variable _noaddref to TRUE in this access point
    const pop_accesspoint & GetAccessPointForThis();

    virtual void Serialize(pop_buffer &buf, bool pack);

    //Find the resource that satisfies the OD, output the resource name or the jobcontact..
    // This method only exist in the pseudodynamic version of the code (this may cause a linking error is used)
    bool TryLocal(pop_accesspoint &objaccess);

    //Connect the interface to the existed object located at resource dest...
    void Bind(const pop_accesspoint &dest);
    void Bind(const char *dest);

    //Disconnect the interface from its object
    void Release();
    //Get Binding status...
    void BindStatus(int &code, std::string &platform, std::string &info);

    bool isBinded();

    //Add the object reference counter...return the new counter value...Use with care
    int AddRef();

    //Release the reference counter...and destroy the object if the counter equals 0...Use with care
    int DecRef();

    //Ask the server to use specific encoding method
    bool Encoding(std::string encoding);

    // Force the remote object to be terminated...
    void Kill();

    //Ask the server its state (active or inactive)
    bool ObjectActive();

#ifdef OD_DISCONNECT
    //Make a receive with a check connection alive ping during the calculation
    bool RecvCtrl();
#endif

    /**
    * Create a POPC object locally (JobMgr not involved)
     * This method creates a commands to run the .obj file and execute it with method pop_interface::Exec
     * @param *hostname Host address or IP. If set the .obj is run via rsh/ssh on this host.
     * @param codefile Name of the .obj executable file
     * @param classname Name of the POPC++ parclass
     * @param rport Socket port
     * @param jobserv
     * @param appserv
     * @param objaccess
     * @param howmany
     * @param ruser Specify a user name for the ssh command
     * @param rcore Specify a core number
     * @return Zero
    */

    static int LocalExec(const char *hostname, const char *codefile, const char *classname, const pop_accesspoint &jobservice, const pop_accesspoint &appservice, pop_accesspoint *objaccess, int howmany, const paroc_od &od);

    static pop_accesspoint _paroc_nobind;
    static int paroc_bind_timeout;



    /**
     * Asynchronous Parallel Object Allocation (APOA)
     * Thread used for asynchronous allocation of the parallel object. Do not change its name as it is used in the POP-C++ parser
     * to generate code.
     */
    pthread_t _popc_async_construction_thread;
    volatile bool _popc_async_joined;

    //Find a resource that satisfies the Qos and allocate an object on it
    void Allocate();
    void allocate_only();

    paroc_od od;

    paroc_od get_object_description();
protected:
    virtual const char *ClassName() {
        return "pop_interface";
    }

    virtual void popc_send_request(pop_buffer *buf, pop_connection* conn);
    virtual void popc_get_response(pop_buffer *buf, pop_connection* conn);

    pop_combox *__pop_combox;
    pop_buffer *__paroc_buf;
    pop_accesspoint accesspoint;

    paroc_mutex _paroc_imutex;

private:

    /**
     * POP-C++ Secure version with SSH tunneling
     * The followings variables are used for SSH Tunneling between the interface and the broker.
     */
    bool _ssh_tunneling;
    int _ssh_local_port;
    int _ssh_dest_port;
    std::string _ssh_dest_ip;
    std::string _ssh_user;
    POPWayback wayToNode;   //Save the way to the node running the object
    std::string popAppId;

    void NegotiateEncoding(std::string &enclist, std::string &peerplatform);
    std::vector<std::string> Tokenize(const std::string &s);
    void ApplyCommPattern(const std::string& pattern, std::vector<std::string> &accesslist);
    int CreateSSHTunnel(const char *user, const char *dest_ip, int dest_port);
    int KillSSHTunnel(const char *user, const char *dest_ip, int dest_port, int local_port);
    bool IsTunnelAlive(const char *user, const char *dest_ip, int dest_port, int local_port);

public:
    static int batchindex;
    static int batchsize;


private:
    static pop_accesspoint *batchaccesspoint;
};

#endif

