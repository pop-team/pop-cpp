/**
 * File : popc_search_node_info.cc
 * Author : Valentin Clement (clementval)
 * Description : Implementation of the object holding information about the node (resource discovery)
 * Creation date : 2010/04/19
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with //End of add
 * clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with //End of modification
 * clementval	2010/04/25	Add needed variable for POP-C++ object description
 * clementval	2010/05/19	Rename NodeInfo in POPCSearchNodeInfo and NodeInfos in POPCSearchNodeInfos
 */


#include "popc_search_node_info.h"
#include <iostream>
#include <unistd.h>

// Default constructor
POPCSearchNodeInfo::POPCSearchNodeInfo(){}

// Destructor
POPCSearchNodeInfo::~POPCSearchNodeInfo(){}

// method used to pass the object in the grid
void POPCSearchNodeInfo::Serialize(POPBuffer &buf, bool pack){
   if(pack){ // marshalling all the information
      buf.Pack(&nodeId, 1);
      buf.Pack(&operatingSystem, 1);
      buf.Pack(&power, 1);
      buf.Pack(&cpuSpeed, 1);
      buf.Pack(&memorySize, 1);
      buf.Pack(&networkBandwidth, 1);
      buf.Pack(&diskSpace, 1);
   	buf.Pack(&protocol, 1);
   	buf.Pack(&encoding, 1);
      buf.Pack(&pki,1);
   }else{ // unmarshalling all the information
      buf.UnPack(&nodeId, 1);
      buf.UnPack(&operatingSystem, 1);
   	buf.UnPack(&power, 1);
      buf.UnPack(&cpuSpeed, 1);
      buf.UnPack(&memorySize, 1);
      buf.UnPack(&networkBandwidth, 1);
      buf.UnPack(&diskSpace, 1);
   	buf.UnPack(&protocol, 1);
   	buf.UnPack(&encoding, 1);
      buf.UnPack(&pki,1);
   }
}

POPString POPCSearchNodeInfo::getPOPCSearchNodeId(){
	return nodeId;
}

POPString POPCSearchNodeInfo::getPKI(){
   return pki;
}

// Default constructor
POPCSearchNodeInfos::POPCSearchNodeInfos(){}

// Default destructor
POPCSearchNodeInfos::~POPCSearchNodeInfos(){}

// method used to pass the object in the grid
void POPCSearchNodeInfos::Serialize(POPBuffer &buf, bool pack){
    if(pack){
        // marshalling all the 'DNodeInfo' contained in the list '_DNodeInfos'
        list<POPCSearchNodeInfo>::iterator i;
        int nElts;
        nElts = _nodeInfos.size();
        buf.Pack(&nElts, 1);
        for(i = _nodeInfos.begin(); i != _nodeInfos.end(); i++){
            i->Serialize(buf, true);
        }
    }else{
        // unmarshalling all the 'DNodeInfo' in the list '_DNodeInfos)
        int nElts;
        buf.UnPack(&nElts, 1);
        int i;
        for(i=0; i<nElts; i++){
            POPCSearchNodeInfo info;
            info.Serialize(buf, false);
            _nodeInfos.push_back(info);
        }
    }
}
void POPCSearchNodeInfos::addANodeInfo(POPCSearchNodeInfo node){
    _nodeInfos.push_back(node);
}
list<POPCSearchNodeInfo> POPCSearchNodeInfos::getNodeInfos(){
    return _nodeInfos;
}

