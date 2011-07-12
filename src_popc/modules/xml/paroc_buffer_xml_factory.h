#ifndef PAROC_BUFFER_XML_FACTORY_H
#define PAROC_BUFFER_XML_FACTORY_H

#include "paroc_buffer_factory.h"

class paroc_buffer_xml_factory:public paroc_buffer_factory{
public:

  paroc_buffer_xml_factory();
  ~paroc_buffer_xml_factory();
  virtual paroc_buffer* CreateBuffer(); 
  virtual bool GetBufferName(paroc_string & bufferName);

};


#endif // PAROC_BUFFER_XML_FACTORY_H
