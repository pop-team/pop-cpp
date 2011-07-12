#ifndef PAROC_EVENT_H_
#define PAROC_EVENT_H_

#define ANY_EVENT -1

#include "paroc_list.h"
#include "paroc_mutex.h"

class EventQueue
{
 public:
  EventQueue();
  ~EventQueue();
  void PostEvent(int e);
  int  WaitEvent(int e=ANY_EVENT, int timeout=-1);
  //timeout=0: return imediately if the event did not occur,
  // -1: disable timeout control, 
  //otherwise, timeout in "timeout" miliseconds
  
 protected:
  paroc_condition cond;
  paroc_list<int> queue;

};

#endif
