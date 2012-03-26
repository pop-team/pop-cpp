/* 
UPDATES : 
Authors		Date			Comment
clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with //End of add
clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with //End of modification
clementval	2010/05/19	Rename NodeInfo in POPCSearchNodeInfo and NodeInfos in POPCSearchNodeInfos
*/


#ifndef _NODEINFO_H
#define _NODEINFO_H
#include <list>
#include <map>
#include "../include/paroc_string.h"
#include "../include/paroc_base.h"

using namespace std;

/*
 *  Class representing information about a node. This class must inherit from
 *  POPBase to be passed in the network.
 */
class POPCSearchNodeInfo : public POPBase{
    public:
         // default constructor
         POPCSearchNodeInfo();
        
         // destructor
         ~POPCSearchNodeInfo();
        
         // Inherited method to serialize the object
         virtual void Serialize(POPBuffer &buf, bool pack);
        
         paroc_string 	nodeId;           // node's unique identifier
			paroc_accesspoint jobmgr;	
         paroc_string 	operatingSystem;  // node's operating system
			float				power;	          // node's compute power in MFlops
         int          	cpuSpeed;         // node's cpu speed
         float          memorySize;       // node's memory size
         float         	networkBandwidth; // node's network bandwidth
         int          	diskSpace;        // node's disk space
			paroc_string	protocol;	  // node's supported protocol
			paroc_string	encoding;	  // node's supported encoding
         paroc_string   pki;

			paroc_string getPOPCSearchNodeId();
         paroc_string getPKI();  //Return SSH Public key
};

/*
 *  Class representing a set of nodes. This class must inherit from POPBase to
 *  be passed in the network.
 */
class POPCSearchNodeInfos : public POPBase{
    public:
        //default constructor
        POPCSearchNodeInfos();
        
        // destructor
        ~POPCSearchNodeInfos();
        
        // Inherited method to serialize the object
        virtual void Serialize(POPBuffer &buf, bool pack);
        
        // Method allowing to add a node's nodeInfo to this set
        void addANodeInfo(POPCSearchNodeInfo nodeInfo);
        
        // Method returning a list of NodeInfo from this set
        list<POPCSearchNodeInfo> getNodeInfos();
    private:
        list<POPCSearchNodeInfo> _nodeInfos;  // The nodes'"NodeInfo" to store
};

#endif
