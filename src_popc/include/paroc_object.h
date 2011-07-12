#ifndef _PAROC_OBJECTBASE_H
#define _PAROC_OBJECTBASE_H

#include "paroc_accesspoint.h"
#include "paroc_event.h"

class paroc_object
{
 public:
  paroc_object();
  virtual ~paroc_object();
  
  int GetRefCount();

  virtual int AddRef();
  virtual int DecRef();
  virtual bool CanKill();

  const paroc_accesspoint & GetAccessPoint() const;

  virtual int eventwait(int event=ANY_EVENT, int timeout=-1); //timeout in milliseconds
  virtual void eventraise(int event);
 private:
  int refcount;
  paroc_mutex lock;
  EventQueue _paroc_events;
 protected:
  paroc_mutex _paroc_omutex;
};

#endif
