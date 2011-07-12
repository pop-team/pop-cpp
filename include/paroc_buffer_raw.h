#ifndef _PAROC_BUFFER_RAW_H
#define _PAROC_BUFFER_RAW_H

#include "paroc_array.h"
#include "paroc_buffer.h"

class paroc_buffer_raw:public paroc_buffer
{
 public:
  paroc_buffer_raw();
  ~paroc_buffer_raw();
  virtual void Reset();

/*   virtual void SetType(int type, const char *name); */
/*   virtual int GetType(); */

  virtual void Pack(const int *data, int n);
  virtual void UnPack(int *data, int n);

  virtual void Pack(const unsigned *data, int n);
  virtual void UnPack(unsigned *data, int n);

  virtual void Pack(const long *data, int n);
  virtual void UnPack(long *data, int n);

  virtual void Pack(const unsigned long *data, int n);
  virtual void UnPack(unsigned long *data, int n);

  virtual void Pack(const short *data, int n);
  virtual void UnPack(short *data, int n);

  virtual void Pack(const unsigned short *data, int n);
  virtual void UnPack(unsigned short *data, int n);

  virtual void Pack(const bool *data, int n);
  virtual void UnPack(bool *data, int n);

  virtual void Pack(const char *data, int n);
  virtual void UnPack(char *data, int n);

  virtual void Pack(const unsigned char *data, int n);
  virtual void UnPack(unsigned char *data, int n);

  virtual void Pack(const float *data, int n);
  virtual void UnPack(float *data, int n);

  virtual void Pack(const double *data, int n);
  virtual void UnPack(double *data, int n);


  virtual bool Send(paroc_combox &s, paroc_connection *conn);
  virtual bool Recv(paroc_combox &s, paroc_connection *conn);

 protected:
  void CheckUnPack(int sz);

  int unpackpos;
  paroc_array<char> packeddata;
};

#endif
