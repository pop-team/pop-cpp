#ifndef PAROC_BUFFER_RAW_FACTORY_H
#define PAROC_BUFFER_RAW_FACTORY_H

#include "paroc_buffer_factory.h"

/*This abstract class declares an interface creating abstract combox*/
class paroc_buffer_raw_factory:public paroc_buffer_factory{
public:

  paroc_buffer_raw_factory();
  virtual paroc_buffer* CreateBuffer(); 
  virtual bool GetBufferName(paroc_string & bufferName);

};


#endif // PAROC_PROTOCOL_SOCKET_FACTORY_H
