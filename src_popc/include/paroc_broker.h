#ifndef _PAROC_BROKERBASE_H
#define _PAROC_BROKERBASE_H

#include <assert.h>
#include <strings.h>

#define INVOKE_SYNC 1
//#define INVOKE_ASYNC 2
#define INVOKE_CONSTRUCTOR 4
#define INVOKE_CONC 8
#define INVOKE_MUTEX 16

#define PROTO_DELIMIT_CHAR " "
#define PROTO_NAME_MAX_LENGTH 1024

#define PAROC_QUEUE_NORMAL 50
#define PAROC_QUEUE_MAX 200

#define IMPLEMENT_TYPE(aparclass) aparclass##__parocobj

#include "paroc_exception.h"
#include "paroc_buffer.h"
#include "paroc_buffer_xdr.h"
#include "paroc_accesspoint.h"
#include "paroc_memspool.h"
#include "paroc_combox_factory.h"
#include <paroc_object.h>
struct paroc_request
{
  paroc_connection *from;
  unsigned methodId[3];
  paroc_buffer *data;
  void operator = (const paroc_request &r);
};

typedef paroc_list<paroc_request> paroc_request_fifo_list;

class paroc_broker
{
 public:
  paroc_broker();
  virtual ~paroc_broker();

  bool Setup(paroc_array<paroc_combox *> & comboxList);

  virtual bool Invoke(unsigned method[3], paroc_buffer &buf, paroc_connection *peer) { return false; };

  virtual int Run();
  bool WakeupReceiveThread(paroc_combox *mycombox);


  static bool Init(int *argc, char ***argv, paroc_array<paroc_combox *> & comboxList);
  static bool SendCallback(paroc_accesspoint &pap);
  static paroc_accesspoint accesspoint;
  static paroc_string classname;

 public:
  //Methods for thread that receive requests and put in the fifo list
  void ReceiveThread(paroc_combox *server); // Receive request and put request in the FIFO
  bool ReceiveRequest(paroc_combox *server, paroc_request &req);
  void RegisterRequest(paroc_request&);
  bool OnNewConnection(paroc_connection *conn);
  bool OnCloseConnection(paroc_connection *conn);


  bool ParocCall(paroc_request &req);//Remote call of Paroc methods
  //  virtual bool ReplyOK(paroc_connection *conn);

 public:
  //Methods to serve the request

  bool GetRequest(paroc_request &req);
  void ServeRequest(paroc_request &req);
  virtual bool DoInvoke(unsigned methodid[3],  paroc_buffer &buf, paroc_connection *peer);


 protected:

  paroc_condition mutexCond;
  int mutexCount;

  paroc_array<paroc_combox*> * comboxArrayPtr;  

  paroc_object *obj;
  paroc_request_fifo_list request_fifo;  
  paroc_condition execCond;

  int instanceCount;
  int state; // 0=Running, 1=Terminate, 2= Abort

};

#define PAROC_STATE_RUNNING 0
#define PAROC_STATE_EXIT 1
#define PAROC_STATE_ABORT 2

#endif
