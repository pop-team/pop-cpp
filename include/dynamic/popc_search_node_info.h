/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 2012/04/19
 * @brief POPCSearchNodeInfo declaration. Holds information about a node for resource discovery algorithm.
 *
 *
 */


#ifndef _NODEINFO_H
#define _NODEINFO_H
#include <list>
#include <map>
#include "paroc_string.h"
#include "paroc_base.h"


/*
 *  Class representing information about a node. This class must inherit from
 *  POPBase to be passed in the network.
 */
class POPCSearchNodeInfo : public POPBase {
public:
    // default constructor
    POPCSearchNodeInfo();

    // destructor
    ~POPCSearchNodeInfo();

    // Inherited method to serialize the object
    virtual void Serialize(POPBuffer &buf, bool pack);

    paroc_string   nodeId;           // node's unique identifier
    paroc_accesspoint jobmgr;
    paroc_string   operatingSystem;  // node's operating system
    float               power;            // node's compute power in MFlops
    int            cpuSpeed;         // node's cpu speed
    float          memorySize;       // node's memory size
    float          networkBandwidth; // node's network bandwidth
    int            diskSpace;        // node's disk space
    paroc_string    protocol;     // node's supported protocol
    paroc_string    encoding;     // node's supported encoding
    paroc_string   pki;

    paroc_string getPOPCSearchNodeId();
    paroc_string getPKI();  //Return SSH Public key
};

/*
 *  Class representing a set of nodes. This class must inherit from POPBase to
 *  be passed in the network.
 */
class POPCSearchNodeInfos : public POPBase {
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
    std::list<POPCSearchNodeInfo> getNodeInfos();
private:
    std::list<POPCSearchNodeInfo> _nodeInfos;  // The nodes'"NodeInfo" to store
};

#endif
