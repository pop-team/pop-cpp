#ifndef PAROC_PROTOCOL_GM_FACTORY_H
#define PAROC_PROTOCOL_GM_FACTORY_H

#include "paroc_protocol_factory.h"

/*This abstract class declares an interface creating abstract combox*/
class paroc_protocol_gm_factory:public paroc_protocol_factory{
public:

  paroc_protocol_gm_factory();
  virtual paroc_combox* CreateCombox(); 
  virtual paroc_comset* CreateComSet();
  virtual bool GetProtocolName(paroc_string & protocolName);

};


#endif // PAROC_PROTOCOL_GM_FACTORY_H
