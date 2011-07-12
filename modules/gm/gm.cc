#include <string.h>
#include "paroc_protocol_gm_factory.h"

extern "C"
{

  paroc_protocol_factory *ParocProtocolFactory()
  {
    return new paroc_protocol_gm_factory;
  }
}
