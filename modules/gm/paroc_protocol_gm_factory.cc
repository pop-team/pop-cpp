#include <unistd.h>
#include <stdio.h>

#include "paroc_protocol_gm_factory.h"
#include "paroc_combox_gm.h"
#include "paroc_comset_gm.h"

paroc_protocol_gm_factory::paroc_protocol_gm_factory(){

}

paroc_combox * paroc_protocol_gm_factory::CreateCombox(){
  return new paroc_combox_gm(this);
}

paroc_comset * paroc_protocol_gm_factory::CreateComSet(){
  return new paroc_comset_gm();
}

bool paroc_protocol_gm_factory::GetProtocolName(paroc_string & protocolName){
   protocolName="gm";
   return true;
}


