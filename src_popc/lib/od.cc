#include "paroc_od.h"


paroc_od::paroc_od()
{
  mflops=min_mflops=ram=min_ram=net=min_net=time=-1;
}

paroc_od::~paroc_od()
{
}

void paroc_od::power(float require, float min)
{
  if (min>require)
    {
      float t=min;
      min=require;
      require=t;
    }
  mflops=require;
  min_mflops=min;
}

void paroc_od::memory(float require, float min)
{
  if (min>require)
    {
      float t=min;
      min=require;
      require=t;
    }
  ram=require;
  min_ram=min;
}

void paroc_od::bandwidth(float require, float min)
{
  if (min>require)
    {
      float t=min;
      min=require;
      require=t;
    }
  net=require;
  min_net=min;
}

void paroc_od::walltime(float t)
{
  time=t;
}

void paroc_od::url(const char *h)
{
  hostname=h;
}

void paroc_od::joburl(const char *jobservice)
{
  jobcontact=jobservice;
}

void paroc_od::executable(const char *code)
{
  codefile=code;
}


void paroc_od::protocol(const char *myproto)
{
  if (myproto==NULL) return;
  proto=myproto;
}

void paroc_od::encoding(const char *myencode)
{
  if (myencode==NULL) return;
  encode=myencode;
}

//Methods used by Runtime system
void paroc_od::getPower(float &require, float &min) const
{
  require=mflops;
  min=min_mflops;
}

void paroc_od::getMemory(float &require, float &min) const
{
  require=ram;
  min=min_ram;
}

void paroc_od::getBandwidth(float &require, float &min) const
{
  require=net;
  min=min_net;
}

float paroc_od::getWallTime() const
{
  return time;
}

void paroc_od::getURL(paroc_string &url) const
{
  url=hostname;
}

void paroc_od::getJobURL(paroc_string &joburl) const
{
  joburl=jobcontact;
}

void paroc_od::getExecutable(paroc_string &exec) const
{
  exec=codefile;
}

void paroc_od::getProtocol(paroc_string &myproto) const
{
  myproto=proto;
}

void paroc_od::getEncoding(paroc_string &myencode) const
{
  myencode=encode;
}

paroc_od &paroc_od::operator =(const paroc_od &od)
{
  if (&od!=this)
    {
      od.getPower(mflops,min_mflops);
      od.getMemory(ram,min_ram);
      od.getBandwidth(net,min_net);
      time=od.getWallTime();
      od.getURL(hostname);
      od.getJobURL(jobcontact);
      od.getExecutable(codefile);
      od.getProtocol(proto);
      od.getEncoding(encode);
    }
  return *this;
}

bool paroc_od::IsEmpty() const
{
  return (mflops<0 && min_mflops<0 && ram<0 && min_ram<0 && net<0 && min_net<0 && time<0 && hostname==NULL);
}

void paroc_od::Serialize(paroc_buffer &buf, bool pack)
{
  float val[2];
  paroc_string t;
  if (pack)
    {
      
      getPower(val[0],val[1]);
      buf.Push("power","float",2);
      buf.Pack(val,2);
      buf.Pop();

      getMemory(val[0],val[1]);
      buf.Push("memory","float",2);
      buf.Pack(val,2);
      buf.Pop();

      getBandwidth(val[0],val[1]);
      buf.Push("bandwidth","float",2);
      buf.Pack(val,2);
      buf.Pop();

      val[0]=getWallTime();
      buf.Push("walltime","float",1);
      buf.Pack(val,1);
      buf.Pop();


      getURL(t);
      buf.Push("url","paroc_string",1);
      buf.Pack(&t,1);
      buf.Pop();


      getJobURL(t);
      buf.Push("joburl","paroc_string",1);
      buf.Pack(&t,1);
      buf.Pop();

      getExecutable(t);
      buf.Push("executable","paroc_string",1);
      buf.Pack(&t,1);
      buf.Pop();

      getProtocol(t);
      buf.Push("protocol","paroc_string",1);
      buf.Pack(&t,1);
      buf.Pop();

      getEncoding(t);
      buf.Push("encoding","paroc_string",1);
      buf.Pack(&t,1);
      buf.Pop();
    }
  else
    {
      buf.Push("power","float",2);
      buf.UnPack(val,2);
      buf.Pop();
      power(val[0],val[1]);


      buf.Push("memory","float",2);
      buf.UnPack(val,2);
      buf.Pop();
      memory(val[0],val[1]);

      buf.Push("bandwidth","float",2);
      buf.UnPack(val,2);
      buf.Pop();
      bandwidth(val[0],val[1]);
  
      buf.Push("walltime","float",1);
      buf.UnPack(val,1);
      buf.Pop();
      walltime(val[0]);

  
      buf.Push("url","paroc_string",1);
      buf.UnPack(&t,1);
      buf.Pop();
      url(t);

      buf.Push("joburl","paroc_string",1);
      buf.UnPack(&t,1);
      buf.Pop();
      joburl(t);

      buf.Push("executable","paroc_string",1);
      buf.UnPack(&t,1);
      buf.Pop();
      executable(t);
      
      buf.Push("protocol","paroc_string",1);
      buf.UnPack(&t,1);
      buf.Pop();
      protocol(t);

      buf.Push("encoding","paroc_string",1);
      buf.UnPack(&t,1);
      buf.Pop();
      encoding(t);
    }
}
