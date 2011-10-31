/**
 * File : request.cc
 * Author : Valentin Clement (clementval)
 * Description : Implementation of the request object. request is used for the resource discovery
 * Creation date : 2010/04/19
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with //End of add
 * clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with //End of modification
 * clementval  2010/11/08  Add variable and methods declaration for the ViSaG project
 */


#include "request.h"
#include <iostream>
#include <unistd.h>

// Empty constructor
Request::Request(){
    init();
}

// Full information constructor
Request::Request(int maxHops, POPString nodeId, POPString operatingSystem, int minCpuSpeed, int expectedCpuSpeed, 
                 float minMemorySize, float expectedMemorySize, int minNetworkBandwidth, int expectedNetworkBandwidth,
                 int minDiskSpace, int expectedDiskSpace, float minPower, float expectedPower, POPString protocol,
                 POPString encoding){
    init();
    _maxHops = maxHops;
    if(nodeId != NULL && nodeId.Length() > 0){
        _nodeId = nodeId;
        _hasNodeIdSet = true;
    }
    if(operatingSystem != NULL && operatingSystem.Length() > 0){
        _operatingSystem = operatingSystem;
        _hasOperatingSystemSet = true;
    }
    if(minCpuSpeed != 0){
        _minCpuSpeed = minCpuSpeed;
        _hasMinCpuSpeedSet = true;
    }
    if(expectedCpuSpeed != 0){
        _expectedCpuSpeed = expectedCpuSpeed;
        _hasExpectedCpuSpeedSet = true;
    }
    if(minMemorySize != 0){
        _minMemorySize = minMemorySize;
        _hasMinMemorySizeSet = true;
    }
    if(expectedMemorySize != 0){
        _expectedMemorySize = expectedMemorySize;
        _hasExpectedMemorySizeSet = true;
    }
    if(minNetworkBandwidth != 0){
        _minNetworkBandwidth = minNetworkBandwidth;
        _hasMinNetworkBandwidthSet = true;
    }
    if(expectedNetworkBandwidth != 0){
        _expectedNetworkBandwidth = expectedNetworkBandwidth;
        _hasExpectedNetworkBandwidthSet = true;
    }
    if(minDiskSpace != 0){
        _minDiskSpace = minDiskSpace;
        _hasMinDiskSpaceSet = true;
    }
    if(expectedDiskSpace != 0){
        _expectedDiskSpace = expectedDiskSpace;
        _hasExpectedDiskSpaceSet = true;
    }
    if(minPower != 0){
        _minPower = minPower;
	_hasMinPowerSet = true;
    }
    if(expectedPower !=0){
    	_expectedPower = expectedPower;
	_hasExpectedPowerSet = true;
    }
    if(protocol != NULL && protocol.Length() > 0){
        _protocol = protocol;
        _hasProtocolSet = true;
    }
    if(encoding != NULL && encoding.Length() > 0){
        _encoding = encoding;
        _hasEncodingSet = true;
    }

}

// method initializing the request. Put the haveXXX to false and init
// the max hops to unlimited
void Request::init(){
   _maxHops = UNLIMITED_HOPS;
   _hasNodeIdSet = false;
   _hasOperatingSystemSet = false;
   _hasMinCpuSpeedSet = false;
   _hasExpectedCpuSpeedSet = false;
   _hasMinMemorySizeSet = false;
   _hasExpectedMemorySizeSet = false;
   _hasMinNetworkBandwidthSet = false;
   _hasExpectedNetworkBandwidthSet = false;
   _hasMinDiskSpaceSet = false;
   _hasExpectedDiskSpaceSet = false;
   _hasMinPowerSet = false;
   _hasExpectedPowerSet = false;
   _hasProtocolSet = false;
   _hasEncodingSet = false;
   _endingSignal = false;
}

// destructor
Request::~Request(){}

/**
 * ViSaG : clementval
 * Check if the request is an ending request
 * @return True if the request is an ending request.
 */
bool Request::isEndRequest(){
   return _endingSignal;
}

/**
 * ViSaG : clementval
 * Set the end request flag as true
 */
void Request::setAsEndRequest(){
   _endingSignal=true;
}

// method used to pass the object in the grid.
void Request::Serialize(POPBuffer &buf, bool pack){
   if(pack){ // marshalling
      // marshalling the request's info
      buf.Pack(&_uniqueId, 1);
      buf.Pack(&_maxHops, 1);
      buf.Pack(&_hasNodeIdSet, 1);
      if(_hasNodeIdSet)
         buf.Pack(&_nodeId, 1);
      buf.Pack(&_hasOperatingSystemSet, 1);
      if(_hasOperatingSystemSet)
         buf.Pack(&_operatingSystem, 1);
      buf.Pack(&_hasMinCpuSpeedSet, 1);
      if(_hasMinCpuSpeedSet)
         buf.Pack(&_minCpuSpeed, 1);
      buf.Pack(&_hasExpectedCpuSpeedSet, 1);
      if(_hasExpectedCpuSpeedSet)
         buf.Pack(&_hasExpectedCpuSpeedSet, 1);
      buf.Pack(&_hasMinMemorySizeSet, 1);
      if(_hasMinMemorySizeSet)
         buf.Pack(&_minMemorySize, 1);
      buf.Pack(&_hasExpectedMemorySizeSet, 1);
      if(_hasExpectedMemorySizeSet)
         buf.Pack(&_expectedMemorySize, 1);
      buf.Pack(&_hasMinNetworkBandwidthSet, 1);
      if(_hasMinNetworkBandwidthSet)
         buf.Pack(&_minNetworkBandwidth, 1);
      buf.Pack(&_hasExpectedNetworkBandwidthSet, 1);
      if(_hasExpectedNetworkBandwidthSet)
         buf.Pack(&_expectedNetworkBandwidth, 1);
      buf.Pack(&_hasMinDiskSpaceSet, 1);
      if(_hasMinDiskSpaceSet)
         buf.Pack(&_minDiskSpace, 1);
      buf.Pack(&_hasExpectedDiskSpaceSet, 1);
      if(_hasExpectedDiskSpaceSet)
         buf.Pack(&_expectedDiskSpace, 1);
    	buf.Pack(&_hasMinPowerSet, 1);
	   if(_hasMinPowerSet)
         buf.Pack(&_minPower, 1);
    	buf.Pack(&_hasExpectedPowerSet, 1);
	   if(_hasExpectedPowerSet)
         buf.Pack(&_expectedPower, 1);
    	buf.Pack(&_hasProtocolSet, 1);
	   if(_hasProtocolSet)
         buf.Pack(&_protocol, 1);
	   buf.Pack(&_hasEncodingSet, 1);
	   if(_hasEncodingSet)
         buf.Pack(&_encoding, 1);

      /**
       * ViSaG : clementval
       * Marshalling the new variables for ViSaG
       */
      buf.Pack(&_pki,1);
      buf.Pack(&_mainPki,1);      
      buf.Pack(&_popappid, 1);
      buf.Pack(&_endingSignal, 1);
      _wb.Serialize(buf, true); //marshalling the POPWayback
      
      /* ViSaG */
      
      //marshalling the exploration list
      explorationList.Serialize(buf, true);

   }else{ // unmarshalling
      // unmarshalling the request's info
      buf.UnPack(&_uniqueId, 1);
      buf.UnPack(&_maxHops, 1);
      buf.UnPack(&_hasNodeIdSet, 1);
      if(_hasNodeIdSet)
         buf.UnPack(&_nodeId, 1);
      buf.UnPack(&_hasOperatingSystemSet, 1);
      if(_hasOperatingSystemSet)
         buf.UnPack(&_operatingSystem, 1);
      buf.UnPack(&_hasMinCpuSpeedSet, 1);
      if(_hasMinCpuSpeedSet)
         buf.UnPack(&_minCpuSpeed, 1);
      buf.UnPack(&_hasExpectedCpuSpeedSet, 1);
      if(_hasExpectedCpuSpeedSet)
         buf.UnPack(&_hasExpectedCpuSpeedSet, 1);
      buf.UnPack(&_hasMinMemorySizeSet, 1);
      if(_hasMinMemorySizeSet)
         buf.UnPack(&_minMemorySize, 1);
      buf.UnPack(&_hasExpectedMemorySizeSet, 1);
      if(_hasExpectedMemorySizeSet)
         buf.UnPack(&_expectedMemorySize, 1);
      buf.UnPack(&_hasMinNetworkBandwidthSet, 1);
      if(_hasMinNetworkBandwidthSet)
         buf.UnPack(&_minNetworkBandwidth, 1);
      buf.UnPack(&_hasExpectedNetworkBandwidthSet, 1);
      if(_hasExpectedNetworkBandwidthSet)
         buf.UnPack(&_expectedNetworkBandwidth, 1);
      buf.UnPack(&_hasMinDiskSpaceSet, 1);
      if(_hasMinDiskSpaceSet)
         buf.UnPack(&_minDiskSpace, 1);
      buf.UnPack(&_hasExpectedDiskSpaceSet, 1);
      if(_hasExpectedDiskSpaceSet)
         buf.UnPack(&_expectedDiskSpace, 1);
	   buf.UnPack(&_hasMinPowerSet, 1);
	   if(_hasMinPowerSet)
         buf.UnPack(&_minPower, 1);
 	   buf.UnPack(&_hasExpectedPowerSet, 1);
	   if(_hasExpectedPowerSet)
         buf.UnPack(&_expectedPower, 1);
 	   buf.UnPack(&_hasProtocolSet, 1);
	   if(_hasProtocolSet)
         buf.UnPack(&_protocol, 1);
	   buf.UnPack(&_hasEncodingSet, 1);
	   if(_hasEncodingSet)
         buf.UnPack(&_encoding, 1);



      /**
       * ViSaG : clementval
       * Unmarshalling the new variables for ViSaG
       */
	   buf.UnPack(&_pki,1);
      buf.UnPack(&_mainPki,1);      
      buf.UnPack(&_popappid, 1);
      buf.UnPack(&_endingSignal, 1);
      _wb.Serialize(buf, false); //unmarshalling the POPWayback

      /* ViSaG */

      //unmarshalling the explorationList
      explorationList.Serialize(buf, false);
    }
}

// Set the uniqueId
void Request::setUniqueId(POPString uniqueId){
    _uniqueId = uniqueId;
}

// Get the uniqueId
POPString Request::getUniqueId(){
    return _uniqueId;
}

// Set the max hops
void Request::setMaxHops(int maxHops){
    _maxHops = maxHops;
}

// Get the max hops
int Request::getMaxHops(){
    return _maxHops;
}

// Set the nodeId
void Request::setNodeId(POPString nodeId){
    _hasNodeIdSet = true;
    _nodeId = nodeId;
}

// Get the nodeId
POPString Request::getNodeId(){
    return _nodeId;
}

// Has nodeId set
bool Request::hasNodeIdSet(){
    return _hasNodeIdSet;
}

// Set operating system
void Request::setOperatingSystem(POPString operatingSystem){
    _hasOperatingSystemSet = true;
    _operatingSystem = operatingSystem;
}

// Get operating system
POPString Request::getOperatingSystem(){
    return _operatingSystem;
}

// Has operating system set
bool Request::hasOperatingSystemSet(){
    return _hasOperatingSystemSet;
}

// Set the mininal CPU speed
void Request::setMinCpuSpeed(int cpuSpeed){
    _hasMinCpuSpeedSet = true;
    _minCpuSpeed = cpuSpeed;
}

// Get the minimal CPU speed
int Request::getMinCpuSpeed(){
    return _minCpuSpeed;
}

// Has the minimal CPU speed set
bool Request::hasMinCpuSpeedSet(){
    return _hasMinCpuSpeedSet;
}

// Set the exact CPU speed
void Request::setExpectedCpuSpeed(int cpuSpeed){
    _hasExpectedCpuSpeedSet = true;
    _expectedCpuSpeed = cpuSpeed;
}

// Get the exact CPU speed
int Request::getExpectedCpuSpeed(){
    return _expectedCpuSpeed;
}

// Has the exact CPU speed set
bool Request::hasExpectedCpuSpeedSet(){
    return _hasExpectedCpuSpeedSet;
}

// Set the minimal memory size
void Request::setMinMemorySize(float memorySize){
    _hasMinMemorySizeSet = true;
    _minMemorySize = memorySize;
}

// Get the minimal memory size
float Request::getMinMemorySize(){
    return _minMemorySize;
}

// Has the minimal memory size set
bool Request::hasMinMemorySizeSet(){
    return _hasMinMemorySizeSet;
}

// Set the exact memory size set
void Request::setExpectedMemorySize(float memorySize){
    _hasExpectedMemorySizeSet = true;
    _expectedMemorySize = memorySize;
}

// Get the exact memory size
float Request::getExpectedMemorySize(){
    return _expectedMemorySize;
}

// Has the exact memory size set
bool Request::hasExpectedMemorySizeSet(){
    return _hasExpectedMemorySizeSet;
}

// Set the minimal network bandwidth
void Request::setMinNetworkBandwidth(float networkBandwidth){
    _hasMinNetworkBandwidthSet = true;
    _minNetworkBandwidth = networkBandwidth;
}

// Get the minimal network bandwidth
float Request::getMinNetworkBandwidth(){
    return _minNetworkBandwidth;
}

// Has the minimal network bandwidth set
bool Request::hasMinNetworkBandwidthSet(){
    return _hasMinNetworkBandwidthSet;
}

// Set the exact network bandwidth
void Request::setExpectedNetworkBandwidth(float networkBandwidth){
    _hasExpectedNetworkBandwidthSet = true;
    _expectedNetworkBandwidth = networkBandwidth;
}

// Get the exact network bandwidth
float Request::getExpectedNetworkBandwidth(){
    return _expectedNetworkBandwidth;
}

// Has the exact network bandwidth set
bool Request::hasExpectedNetworkBandwidthSet(){
    return _hasExpectedNetworkBandwidthSet;
}

// Set the minimal disk space
void Request::setMinDiskSpace(int diskSpace){
    _hasMinDiskSpaceSet = true;
    _minDiskSpace = diskSpace;
}

// Get the minimal disk space
int Request::getMinDiskSpace(){
    return _minDiskSpace;
}

// Has the minimal disk space set
bool Request::hasMinDiskSpaceSet(){
    return _hasMinDiskSpaceSet;
}

// Set the exact disk space
void Request::setExpectedDiskSpace(int diskSpace){
    _hasExpectedDiskSpaceSet = true;
    _expectedDiskSpace = diskSpace;
}

// Get the exact disk space
int Request::getExpectedDiskSpace(){
    return _expectedDiskSpace;
}

// Has the exact disk space
bool Request::hasExpectedDiskSpaceSet(){
    return _hasExpectedDiskSpaceSet;
}

// set the min compute power
void Request::setMinPower(float p){
    _hasMinPowerSet=true;
    _minPower=p;
}

// get the min compute power
float Request::getMinPower(){
    return _minPower;
}

// has the min compute power set
bool Request::hasMinPowerSet(){
    return _hasMinPowerSet;
}

// set the expected compute power
void Request::setExpectedPower(float p){
    _hasExpectedPowerSet=true;
    _expectedPower=p;
}

// get the expected compute power
float Request::getExpectedPower(){
    return _expectedPower;
}

// has the expected compute power set
bool Request::hasExpectedPowerSet(){
    return _hasExpectedPowerSet;
}

// set the protcol
void Request::setProtocol(POPString prot){
    _hasProtocolSet=true;
    _protocol=prot;
}

// get the protocol
POPString Request::getProtocol(){
    return _protocol;
}

// has the protocol set
bool Request::hasProtocolSet(){
    return _hasProtocolSet;
}

// set the encoding
void Request::setEncoding(POPString enc){
    _hasEncodingSet=true;
    _encoding=enc;
}

// get the encoding
POPString Request::getEncoding(){
    return _encoding;
}

// has the expected compute power set
bool Request::hasEncodingSet(){
    return _hasEncodingSet;
}

//Set the PKI of the initiator
void Request::setPKI(POPString pki){
   _pki = pki;
}

//Get the PKI of the initiator
POPString Request::getPKI(){
   return _pki;
}


void Request::setMainPKI(POPString pki){
   _mainPki = pki;
}

POPString Request::getMainPKI(){
   return _mainPki;
}


// Add a list of nodes in the exploration list (neighbors of the nodeId's node)
void Request::addNodeToExplorationList(POPString nodeId,
                                       list<POPString> neighbors){
    explorationList.addListNode(nodeId,neighbors);
    // decrement max hops if not unlimited
    if(_maxHops != UNLIMITED_HOPS)
        _maxHops--;
}

// Return the exploration list
ExplorationList Request::getExplorationList(){
    return explorationList;
}

/**
 * ViSaG : clementval
 * set the POP Application ID
 * @param popAppId The POP Application ID
 */
void Request::setPOPAppId(POPString popAppId){
   _popappid = popAppId;
}

/**
 * ViSaG : clementval
 * Get the POP Application ID
 * @return a POPString containing the POP Application ID
 */
POPString Request::getPOPAppId(){
   return _popappid;
}

/**
 * ViSaG : clementval
 * Add a node to the way back
 * @param nodeId access string of the node to add
 */
void Request::addNodeToWb(POPString nodeId){
   _wb.insertNode(nodeId);
}

/**
 * ViSaG : clementval 
 * Get the current way back to the initiator of the request
 * @return the POPWayback containg the way back to the request initiator
 */
POPWayback Request::getWayBack() const {
   return _wb;
}

/**
 * ViSaG : clementval 
 * Get the current way back to the initiator as a string
 * @return a formatted string represtanting the way back to the initiator
 */
const POPString Request::getWbAsString() const {
   POPString wb = _wb.getAsString();
   return wb;
}

