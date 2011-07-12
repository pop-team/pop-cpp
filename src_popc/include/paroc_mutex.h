#ifndef _PAROC_MUTEX_H
#define _PAROC_MUTEX_H
#include <pthread.h>


class paroc_mutex
{
 public:
  paroc_mutex();
  ~paroc_mutex();
  void lock();
  void unlock();
 protected:
  pthread_mutex_t _mutex;
};


class paroc_condition: public paroc_mutex
{
 public:
  paroc_condition();
  ~paroc_condition();

  void signal();
  void broadcast();
  void wait();
  bool wait(int timeout);

 protected:
  pthread_cond_t _cond;
};

class paroc_mutex_locker
{
 public:
  paroc_mutex_locker(paroc_mutex &_mutex);
  ~paroc_mutex_locker();
 private:
  paroc_mutex *pmutex;
};

class POPSynchronizer: public paroc_condition
{
public:
  void raise() { broadcast(); };
};
#endif
