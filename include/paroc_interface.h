#ifndef _PAROC_INTERFACE_CORE_H
#define _PAROC_INTERFACE_CORE_H

#include <stdio.h>
#include <paroc_base.h>

#include <paroc_accesspoint.h>
#include <paroc_od.h>
#include <paroc_buffer.h>
#include <paroc_list.h>


#define BIND_OK 0
#define BIND_FORWARD_SESSION 1
#define BIND_FORWARD_PERMANENT 2

#define PAROC_ALLOC_RETRY 3

class paroc_interface: paroc_base
{
 public:
  paroc_interface();
  paroc_interface(const paroc_accesspoint &p);
  paroc_interface(const paroc_interface &inf);

  virtual ~paroc_interface();

  //Assign an interface from the others.....
  paroc_interface & operator = (const paroc_interface &obj);

  virtual void SetOD(const paroc_od &myod);
  virtual const paroc_od &GetOD() const;

  //  virtual const char * GetResource() const;

  const paroc_accesspoint & GetAccessPoint() const;

  virtual void Serialize(paroc_buffer &buf, bool pack); 

  //Find the resource that satisfies the OD, output the resource name or the jobcontact..
  int LocateResource(paroc_string &hostname, paroc_string &codefile, paroc_accesspoint &jobcontact);

  //Connect the interface to the existed object located at resource dest...
  void Bind(const paroc_accesspoint &dest);
  void Bind(const char *dest);
  
  //Disconnect the interface from its object
  void Release();
  

  //Get Binding status...
  void BindStatus(int &code, paroc_string &platform, paroc_string &info);

  //Add the object reference counter...return the new counter value...Use with care
  int AddRef();
  
  //Release the reference counter...and destroy the object if the counter equals 0...Use with care
  int DecRef();
  
  //Ask the server to use specific encoding method
  bool Encoding(paroc_string encoding);

  // Force the remote object to be terminated...
  void Kill();
  
  //Ask the server its state (active or inactive)
  bool ObjectActive();


  static int LocalExec(const char *hostname, const char *codefile, const char *classname, const char *rport, const paroc_accesspoint &jobservice, const paroc_accesspoint &appservice, paroc_accesspoint *objaccess, int howmany);

  static paroc_accesspoint _paroc_nobind;
  static int paroc_bind_timeout;
 protected:

  virtual const char *ClassName() { return "paroc_interface"; };
  //Find a resource that satisfies the Qos and allocate an object on it

  void Allocate();

  paroc_combox *__paroc_combox;
  paroc_buffer *__paroc_buf;

  paroc_accesspoint accesspoint;

  paroc_od od;

  paroc_mutex _paroc_imutex; 

 private:
  void NegotiateEncoding(paroc_string &enclist, paroc_string &peerplatform);

  void Tokenize(paroc_string &s, paroc_list<char *> &tokens);
  void ApplyCommPattern(const char *pattern, paroc_list<char *> &accesslist);


};


#endif

