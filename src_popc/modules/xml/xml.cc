#include <string.h>
#include "paroc_buffer_xml_factory.h"

extern "C"
{

  paroc_buffer_factory *ParocBufferFactory()
  {
    return new paroc_buffer_xml_factory;
  }
}
