/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief broker declaration for parclass objects
 *
 *
 */

#ifndef _POPC_BROKERBASE_H
#define _POPC_BROKERBASE_H

#include <assert.h>
#include <strings.h>
#include <deque>

#define INVOKE_SYNC 1
//#define INVOKE_ASYNC 2
#define INVOKE_CONSTRUCTOR 4
#define INVOKE_CONC 8
#define INVOKE_MUTEX 16

#define PROTO_DELIMIT_CHAR " "
#define PROTO_NAME_MAX_LENGTH 1024

#define POPC_QUEUE_NORMAL 50
#define POPC_QUEUE_MAX 200

#define IMPLEMENT_TYPE(aparclass) aparclass##_popcobject

#include "paroc_exception.h"
#include "paroc_buffer.h"
#include "paroc_buffer_xdr.h"
#include "paroc_accesspoint.h"
#include "paroc_combox_factory.h"
#include "paroc_combox_socket.h"
#include "paroc_object.h"

struct paroc_request {
    paroc_connection *from;
    unsigned methodId[3];
    paroc_buffer *data;
    void *userdata;
    void operator = (const paroc_request &r);
    paroc_request();
    paroc_request(const paroc_request &r);
};

typedef std::deque<paroc_request> paroc_request_fifo_list;

//Method names....
struct paroc_method_info {
    unsigned mid;
    char *name;
};

struct paroc_class_info {
    unsigned cid;
    paroc_method_info *methods;
    int sz;
};

typedef std::vector<paroc_class_info> paroc_method_map_list;

/**
 * @class paroc_broker
 * @brief Broker declaration for parclass objects, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */

class paroc_broker {
public:
    paroc_broker();
    virtual ~paroc_broker();

    //To acquire info of method names....
    //This method is used by the compiler to register method names
    void AddMethodInfo(unsigned cid, paroc_method_info *methods, int sz);

    //These 2 methods are ussually used for debuging and visualization of class execution....
    const char *FindMethodName(unsigned classID, unsigned methodID);
    bool FindMethodInfo(const char *name, unsigned &classID, unsigned &methodID);

    virtual bool Invoke(unsigned method[3], paroc_buffer &buf, paroc_connection *peer);

    virtual int Run();

    bool Initialize(int *argc, char ***argv);
    bool WakeupReceiveThread(paroc_combox *mycombox);

    static paroc_accesspoint accesspoint;
    static paroc_string classname;

public:
    //Methods for thread that receive requests and put in the fifo list
    void ReceiveThread(paroc_combox *server); // Receive request and put request in the FIFO
    virtual bool ReceiveRequest(paroc_combox *server, paroc_request &req);
    void RegisterRequest(paroc_request&);
    bool OnNewConnection(paroc_connection *conn);
    bool OnCloseConnection(paroc_connection *conn);


    bool ParocCall(paroc_request &req);           //Remote call of Paroc methods
    paroc_object * GetObject();                   // Get the associated object

#ifdef OD_DISCONNECT
    bool checkConnection;
#endif

public:
    //Methods to serve the request
    bool GetRequest(paroc_request &req);            // Get a request from the fifo queue
    void ServeRequest(paroc_request &req);          // Get the request and do the invocation
    void UnhandledException();                      // Handle for unknown exception
    virtual bool DoInvoke(paroc_request &request);  // Invoke the method on the associated object

protected:

    paroc_method_map_list methodnames;

    paroc_condition mutexCond;  // Lock condition for mutex call
    int mutexCount;             // Number of mutex call pending
    int concPendings;           // Number of concurrent call pending

    std::vector<paroc_combox*> comboxArray;

    paroc_object *obj;                    // Real object associated with this broker
    paroc_request_fifo_list request_fifo; // Queue storing the request received by the broker
    paroc_condition execCond;
    int instanceCount;  //
    int connclosecount;  //Count the number of connection close on an object
    int state; // 0=Running, 1=Terminate, 2= Abort
};

#define POPC_STATE_RUNNING 0
#define POPC_STATE_EXIT 1
#define POPC_STATE_ABORT 2

#endif
