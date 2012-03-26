/* 
UPDATES : 
Authors		Date			Comment
clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with //End of add
clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with //End of modification
clementval  2010/10/08  Add variable and methods declaration for the ViSaG project
*/

#ifndef _REQUEST_H
#define _REQUEST_H
#include "explorationList.h"
#include "paroc_base.h"
#include "popwayback.h"
#include <string>

#define MAXREQUNIQUEIDLENGTH 100    // Maximum length of uniqueId of a request
#define UNLIMITED_HOPS -20         // Fixed value indicating unlimited hops

using namespace std;

/*
 *  Class representing a request of resource discovery. This class must
 *  inherit from POPBase to be passed in the network.
 */ 
class Request : public POPBase{
public :
   // default constructor without information on the request
   Request();
        
   // constructor with all information
   Request(int maxHops,
   POPString nodeId,
   POPString operatingSystem, 
   int minCpuSpeed,
   int expectedCpuSpeed,
   float minMemorySize,
   float expectedMemorySize,
   int minNetworkBandwidth,
   int expectedNetworkBandwidth,
   int minDiskSpace,
   int expectedDiskSpace,
	float minPower,
	float expectedPower,
	POPString protocol,
   POPString encoding);
                
   // Destructor
   ~Request();

   // Inherited method to serialize the object
   virtual void Serialize(POPBuffer &buf, bool pack);

   // Getters, setters and havers for different information
   void         setUniqueId(POPString uniqueId);
   POPString getUniqueId();
        
   void         setMaxHops(int maxHops);
   int          getMaxHops();
        
   void         setNodeId(POPString nodeId);
   POPString getNodeId();
   bool         hasNodeIdSet();
        
   void         setOperatingSystem(POPString operatingSystem);
   POPString getOperatingSystem();
   bool         hasOperatingSystemSet();
        
   void         setMinCpuSpeed(int cpuSpeed);
   int          getMinCpuSpeed();
   bool         hasMinCpuSpeedSet();
        
   void         setExpectedCpuSpeed(int cpuSpeed);
   int          getExpectedCpuSpeed();
   bool         hasExpectedCpuSpeedSet();
        
   void         setMinMemorySize(float memorySize);
   float        getMinMemorySize();
   bool         hasMinMemorySizeSet();
        
   void         setExpectedMemorySize(float memorySize);
   float        getExpectedMemorySize();
   bool         hasExpectedMemorySizeSet();
        
   void         setMinNetworkBandwidth(float networkBandwidth);
   float        getMinNetworkBandwidth();
   bool         hasMinNetworkBandwidthSet();
        
   void         setExpectedNetworkBandwidth(float networkBandwidth);
   float        getExpectedNetworkBandwidth();
   bool         hasExpectedNetworkBandwidthSet();
        
   void         setMinDiskSpace(int diskSpace);
   int          getMinDiskSpace();
   bool         hasMinDiskSpaceSet();
      
   void         setExpectedDiskSpace(int diskSpace);
   int          getExpectedDiskSpace();
   bool         hasExpectedDiskSpaceSet();

	void 	     setExpectedPower(float power);
	float	     getExpectedPower();
	bool 	     hasExpectedPowerSet();

	void 	     setMinPower(float power);
	float	     getMinPower();
	bool 	     hasMinPowerSet();

	void 	     setProtocol(POPString power);
	POPString getProtocol();
	bool 	     hasProtocolSet();

	void 	     setEncoding(POPString power);
	POPString getEncoding();
	bool 	     hasEncodingSet();

   /**
    * ViSaG : clementval
    */
   void setPKI(POPString pki);
   POPString getPKI();

   void setMainPKI(POPString pki);
   POPString getMainPKI();

   void setPOPAppId(POPString pki);
   POPString getPOPAppId();
   void addNodeToWb(POPString nodeId);
   const POPString getWbAsString() const;
   POPWayback getWayBack() const;
   
   /* ViSaG */
	
		
        
   // method allowing adding nodes to the exploration list of the request
   void addNodeToExplorationList(POPString nodeId, list<POPString> neighbors);

   // return the exploration list of the request
   ExplorationList getExplorationList();
        
   // method telling if a node (identified by its name) is present in the
   // exploration list of the request
   bool isInExplorationList(POPString nodeId);

   bool isEndRequest();

   void setAsEndRequest();
private :
   POPString _uniqueId;    //Unique identifier of the request
   int _maxHops;              //Maximum number of hops for this request

   /**
    * ViSaG : clementval
    */
   POPWayback _wb;         //List containing the way back to the initiator
   POPString _popappid; //POP Application ID
   POPString _pki;      //Pki of the initiator node
   POPString _mainPki;  //Pki of the main node
   bool _endingSignal;
   /* ViSaG */


   // request parameters
   POPString _nodeId;
   bool _hasNodeIdSet;
   POPString _operatingSystem;
   bool _hasOperatingSystemSet;
   int _minCpuSpeed;
   bool _hasMinCpuSpeedSet;
   int _expectedCpuSpeed;
   bool _hasExpectedCpuSpeedSet;
   float _minMemorySize;
   bool _hasMinMemorySizeSet;
   float _expectedMemorySize;
   bool _hasExpectedMemorySizeSet;
   int _minNetworkBandwidth;
   bool _hasMinNetworkBandwidthSet;
   int _expectedNetworkBandwidth;
   bool _hasExpectedNetworkBandwidthSet;
   int _minDiskSpace;
   bool _hasMinDiskSpaceSet;
   int _expectedDiskSpace;
   bool _hasExpectedDiskSpaceSet;
	float _expectedPower;
	bool _hasExpectedPowerSet;
	float _minPower;
	bool _hasMinPowerSet;
	POPString	_protocol;
	bool _hasProtocolSet;
	POPString	_encoding;
	bool _hasEncodingSet;

        
   ExplorationList explorationList;    // exploration list of the request
        
   // initiator of the request
   void init();
};

#endif
