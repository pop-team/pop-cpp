#ifndef PAROC_BUFFER_FACTORY_H
#define PAROC_BUFFER_FACTORY_H

#include <paroc_buffer.h>

/*This abstract class declares an interface creating abstract buffer*/
class paroc_buffer;

class paroc_buffer_factory
{
public:
  paroc_buffer_factory();
 protected:
  virtual ~paroc_buffer_factory();

 public:
  virtual void Destroy();

  virtual paroc_buffer* CreateBuffer()=0; 

  virtual bool GetBufferName(paroc_string & bufferName)=0;
};

#endif // PAROC_BUFFER_FACTORY_H
