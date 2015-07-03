/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 2010/04/19
 * @brief Request class declaration used in the resource discovery algorithm
 *
 *
 * UPDATES :
 * Authors      Date            Comment
 * clementval   2010/04/19  All code added for the semester project begins with this comment //Added by clementval, ends
 *with //End of add
 * clementval   2010/04/19  All code modified during the semester project begins with //Modified by clementval, ends
 *with //End of modification
 * clementval  2010/10/08  Add variable and methods declaration for the ViSaG project
 */

#ifndef _REQUEST_H
#define _REQUEST_H
#include "pop_exploration_list.h"
#include "pop_base.h"
#include "pop_wayback.h"
#include <string>

#define MAXREQUNIQUEIDLENGTH 100  // Maximum length of uniqueId of a request
#define UNLIMITED_HOPS -20        // Fixed value indicating unlimited hops

/*
 *  Class representing a request of resource discovery. This class must
 *  inherit from POPBase to be passed in the network.
 */
class Request : public POPBase {
public:
    // default constructor without information on the request
    Request();

    // constructor with all information
    Request(int maxHops, std::string nodeId, std::string operatingSystem, int minCpuSpeed, int expectedCpuSpeed,
            float minMemorySize, float expectedMemorySize, int minNetworkBandwidth, int expectedNetworkBandwidth,
            int minDiskSpace, int expectedDiskSpace, float minPower, float expectedPower, std::string protocol,
            std::string encoding);

    // Destructor
    ~Request();

    // Inherited method to serialize the object
    virtual void Serialize(POPBuffer& buf, bool pack);

    // Getters, setters and havers for different information
    void setUniqueId(std::string uniqueId);
    std::string getUniqueId();

    void setMaxHops(int maxHops);
    int getMaxHops();

    void setNodeId(std::string nodeId);
    std::string getNodeId();
    bool hasNodeIdSet();

    void setOperatingSystem(std::string operatingSystem);
    std::string getOperatingSystem();
    bool hasOperatingSystemSet();

    void setMinCpuSpeed(int cpuSpeed);
    int getMinCpuSpeed();
    bool hasMinCpuSpeedSet();

    void setExpectedCpuSpeed(int cpuSpeed);
    int getExpectedCpuSpeed();
    bool hasExpectedCpuSpeedSet();

    void setMinMemorySize(float memorySize);
    float getMinMemorySize();
    bool hasMinMemorySizeSet();

    void setExpectedMemorySize(float memorySize);
    float getExpectedMemorySize();
    bool hasExpectedMemorySizeSet();

    void setMinNetworkBandwidth(float networkBandwidth);
    float getMinNetworkBandwidth();
    bool hasMinNetworkBandwidthSet();

    void setExpectedNetworkBandwidth(float networkBandwidth);
    float getExpectedNetworkBandwidth();
    bool hasExpectedNetworkBandwidthSet();

    void setMinDiskSpace(int diskSpace);
    int getMinDiskSpace();
    bool hasMinDiskSpaceSet();

    void setExpectedDiskSpace(int diskSpace);
    int getExpectedDiskSpace();
    bool hasExpectedDiskSpaceSet();

    void setExpectedPower(float power);
    float getExpectedPower();
    bool hasExpectedPowerSet();

    void setMinPower(float power);
    float getMinPower();
    bool hasMinPowerSet();

    void setProtocol(std::string power);
    std::string getProtocol();
    bool hasProtocolSet();

    void setEncoding(std::string power);
    std::string getEncoding();
    bool hasEncodingSet();

    /**
     * ViSaG : clementval
     */
    void setPKI(std::string pki);
    std::string getPKI();

    void setMainPKI(std::string pki);
    std::string getMainPKI();

    void setPOPAppId(std::string pki);
    std::string getPOPAppId();
    void addNodeToWb(std::string nodeId);
    const std::string getWbAsString() const;
    POPWayback getWayBack() const;

    /* ViSaG */

    // method allowing adding nodes to the exploration list of the request
    void addNodeToExplorationList(std::string nodeId, std::list<std::string> neighbors);

    // return the exploration list of the request
    ExplorationList getExplorationList();

    // method telling if a node (identified by its name) is present in the
    // exploration list of the request
    bool isInExplorationList(std::string nodeId);

    bool isEndRequest();

    void setAsEndRequest();

private:
    std::string _uniqueId;  // Unique identifier of the request
    int _maxHops;  // Maximum number of hops for this request

    /**
     * ViSaG : clementval
     */
    POPWayback _wb;  // List containing the way back to the initiator
    std::string _popappid;  // POP Application ID
    std::string _pki;  // Pki of the initiator node
    std::string _mainPki;  // Pki of the main node
    bool _endingSignal;
    /* ViSaG */

    // request parameters
    std::string _nodeId;
    bool _hasNodeIdSet;
    std::string _operatingSystem;
    bool _hasOperatingSystemSet;
    int _minCpuSpeed;
    bool _hasMinCpuSpeedSet;
    int _expectedCpuSpeed;
    bool _hasExpectedCpuSpeedSet;
    float _minMemorySize;
    bool _hasMinMemorySizeSet;
    float _expectedMemorySize;
    bool _hasExpectedMemorySizeSet;
    float _minNetworkBandwidth;
    bool _hasMinNetworkBandwidthSet;
    float _expectedNetworkBandwidth;
    bool _hasExpectedNetworkBandwidthSet;
    int _minDiskSpace;
    bool _hasMinDiskSpaceSet;
    int _expectedDiskSpace;
    bool _hasExpectedDiskSpaceSet;
    float _expectedPower;
    bool _hasExpectedPowerSet;
    float _minPower;
    bool _hasMinPowerSet;
    std::string _protocol;
    bool _hasProtocolSet;
    std::string _encoding;
    bool _hasEncodingSet;

    ExplorationList explorationList;  // exploration list of the request

    // initiator of the request
    void init();
};

#endif
