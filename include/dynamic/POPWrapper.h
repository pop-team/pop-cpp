/**
 * File : POPWrapper.cc
 * Author : Valentin Clement
 * Description : Declaration of the basic driver wrapper implementation
 * Creation date : 2010/1/27
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  2010/1/27   Creation of this file on the basis of the original ESXWrapper.h
 */

#ifndef POPWRAPPER_H
#define POPWRAPPER_H


#include "VPopCWrapper.h"
#include "popvm.h"
#include "paroc_accesspoint.h"

extern "C"{
   #include <libvirt/libvirt.h>
   #include <libvirt/virterror.h>
}
#include <cstring>


class POPWrapper : public VPopCWrapper {
   //Private attributes
protected:
   virConnectPtr _connPtr;    // Internal ESX(i) connection pointer
   virDomainPtr _domPtr;      // Internal ESX(i) domain pointer
 
   paroc_accesspoint _popcloner; //Access Point to the POPCloner parallel object   
public:
   POPWrapper(paroc_accesspoint clonerRef);
   ~POPWrapper(); 
   
   /* Please check out VPopCWrapper for any comments */
   int virtual _popc_connectOpenAuth(string uri, string user, string password);
   int _popc_connectClose();
   virDomainPtr _popc_domainLookupByName(string domName);
   int _popc_domainState(POPvm &vm, string* state);
   long long _popc_nodeGetFreeMemory();
   int _popc_nodeGetInfo(nodeInfo* info);
   int _popc_domainSnapshotNum(POPvm &vm);
   int _popc_domainSnapshotListNames(POPvm &vm, string names[], unsigned short len);
   int _popc_domainRevertToSnapshot(POPvm &vm, string snapshotName);
   int _popc_domainRevertToOldestSnapshot(POPvm &vm);
   int _popc_domainSnapshotCreate(POPvm &vm, string name, string description);
   int _popc_domainSnapshotDelete(POPvm &vm, string snapshotName, bool removeChildren = false);
   int _popc_domainSetMemory(POPvm &vm, unsigned long memoryInKb);
   int _popc_domainSetMaxMemory(POPvm &vm, unsigned long memoryInKb);
   long _popc_domainGetMaxMemory(POPvm &vm);
   int _popc_domainShutdown(POPvm &vm);
   int _popc_domainSuspend(POPvm &vm);
   int _popc_domainResume(POPvm &vm);
   const string _popc_domainGetMAC(POPvm &vm);
   int _popc_domainIsConnected(string domName = "");
   int virtual _popc_domainGetIpAddress(POPvm &vm) = 0;
   int virtual _popc_sendLocalPublicKey(POPvm &vm) = 0;
   int virtual _popc_sendPublicKey(POPvm &vm, POPString pki) = 0;
   int virtual _popc_getLocalPublicKey(POPvm &vm) = 0;
   int virtual _popc_domainClone(POPvm &original, int number, POPString baseName, int suffix, paroc_accesspoint clonerAP) = 0;
   int virtual _popc_domainWaitingForTools(POPvm &vm) = 0;
   
   const string _popc_getError();

};

int popc_wrapper_log(const char *format,...);

#endif /* POPWRAPPER_H */
