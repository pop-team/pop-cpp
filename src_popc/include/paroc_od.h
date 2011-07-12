#ifndef _PAROC_OD_H
#define _PAROC_OD_H
#include "paroc_string.h"
#include "paroc_base.h"

class paroc_od: public paroc_base
{
 public:
  paroc_od();
  ~paroc_od();
  void power(float require, float min=-1.0f);

  void memory(float require, float min=-1.0f);

  void bandwidth(float require, float min=-1.0f);

  void walltime(float time);
  
  void url(const char *h);
  void joburl(const char *jobcontact);
  void executable(const char *codefile);

  void protocol(const char *myproto);
  void encoding(const char *myencode);

  void getPower(float &require, float &min) const;
  void getMemory(float &require, float &min) const;
  void getBandwidth(float &require, float &min) const;
  float getWallTime() const;
  void getURL(paroc_string & url) const;
  void getJobURL(paroc_string &joburl) const;
  void getExecutable(paroc_string &exec) const;
  
  void getProtocol(paroc_string &proto) const;
  void getEncoding(paroc_string &encode) const;

  paroc_od &operator =(const paroc_od &od);

  bool IsEmpty() const;

  virtual void Serialize(paroc_buffer &buf, bool pack);

 protected:
  float mflops, min_mflops;
  float ram, min_ram;
  float net, min_net;
  float time;
  paroc_string hostname;
  paroc_string jobcontact;
  paroc_string codefile;

  paroc_string proto; //space-separate protocol lists
  paroc_string encode; //space-separate encoding lists
};

#endif
