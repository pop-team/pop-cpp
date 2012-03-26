/**
 * File : VPopCWrapper.h
 * Author : Adrian Wyssen
 * Description : Interface of any wrapper implementation
 * Creation date : 04/08/2010
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#ifndef VPOPCWRAPPER_H
#define VPOPCWRAPPER_H

#include <iostream>
#include "popvm.h"
#include "paroc_accesspoint.h"

extern "C"{
   #include <libvirt/libvirt.h>
   #include <libvirt/virterror.h>
}

using namespace std;



/*
   This structure will hold information about a hypervisor
*/
struct nodeInfo{
   string	      model;   //string indicating the CPU model
   unsigned long	memory;  //memory size in kilobytes
   unsigned int	cpus;    //the number of active CPUs
   unsigned int	mhz;     //expected CPU frequency
   unsigned int	nodes;	//the number of NUMA cell, 1 for uniform mem access
   unsigned int	sockets; //number of CPU socket per node
   unsigned int	cores;   //number of core per socket
   unsigned int	threads;	//number of threads per core
};


class VPopCWrapper{
   //Private attributes   
   
public:   
   
   /*
      Opens a connection to a ESX(i) host / hypervisor
      Return 0 on success, -1 on error and -2 when there is already a connection open with this instance.
   */
   virtual int _popc_connectOpenAuth(string uri, string user, string password) = 0;
   
   
   /*
      Closes a connection to a host / node.
      Return 0 on success, -1 on error.
   */
   virtual int _popc_connectClose() = 0;
   
   
   /*
      Tries to get a pointer to a domain / virtual machine called 'domName'.
      Return 0 on success, -1 on error and -2 when there is no connection to a hypervisor.
   */
   virtual virDomainPtr _popc_domainLookupByName(string domName) = 0;
   
   
   /*
      Get the current state of a virtual domain. The state is returned in the passed string pointer.
      Return 0 on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainState(POPvm &vm, string* state) = 0;
   
   
   /*
      Return # of free kilobytes on success, -1 on error and -2 when there is no connection to a host / node.
   */
   virtual long long _popc_nodeGetFreeMemory() = 0;
   
   
   /*
      Get infos about host. The infos will be saved in the passed nodeInfo structure.
      Return 0 on success, -1 on error and -2 when there is no connection to a host / node.
   */
   virtual int _popc_nodeGetInfo(nodeInfo* info) = 0;
   
   
   /*
      Get the number of snapshots in the currently connected domain.
      Return the # of snapshots on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainSnapshotNum(POPvm &vm) = 0;
   
   
   /*
      Get the snapshot list of the currently connected domain.
      The names will be returned in the names array. A maximum of 'len' names will be returned.
      Return the # of snapshots returned on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainSnapshotListNames(POPvm &vm, string names[], unsigned short len) = 0;
   
   
   /*
      Reverts the currently connected domain to the passed snapshot.
      Return 0 on success, -1 on error, -2 when there is no connection to a domain and -3 if the snapshot does not exist.
   */
   virtual int _popc_domainRevertToSnapshot(POPvm &vm, string snapshotName) = 0;
   
   
   /*
      Reverts the currently connected domain to the oldest snapshot.
      Return 0 on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainRevertToOldestSnapshot(POPvm &vm) = 0;
   
   
   /*
      Takes a new snapshot of the currently connected domain.
      This method takes some time.
      Return 0 on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainSnapshotCreate(POPvm &vm, string name, string description) = 0;
   
   
   /*
      Delete a snapshot. If removeChildren is false, then just this snapshot is deleted, 
      and changes from this snapshot are automatically merged into children snapshots.
      If the removeChildren is true, then this snapshot and any children snapshots are deleted.
      
      Return 0 on success, -1 on error, -2 when there is no connection to a domain and -3 if the snapshot does not exist.
   */
   virtual int _popc_domainSnapshotDelete(POPvm &vm, string snapshotName, bool removeChildren = false) = 0;
   
   
   /*
      Set the actual memory allocated to a certain domain.
      Return 0 on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainSetMemory(POPvm &vm, unsigned long memoryInKb) = 0;
   
   
   /*
      Change the maximum memory allocated to a certain domain. The domain needs to be suspended or shutdown.
      Return 0 on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainSetMaxMemory(POPvm &vm, unsigned long memoryInKb) = 0;
   
   
   /*
      Retrieve the maximum amount of physical memory allocated to the currently connected domain.
      Return the memory in kilobytes on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual long _popc_domainGetMaxMemory(POPvm &vm) = 0;
   
   
   /*
      Shuts down the currently connected domain.
      Return 0 on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainShutdown(POPvm &vm) = 0;
   
   
   /*
      Suspends an active domain, the process is frozen without further access to CPU resources and I/O
      but the memory used by the domain at the hypervisor level will stay allocated.
      Use domainResume() to reactivate the domain.
      
      Return 0 on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainSuspend(POPvm &vm) = 0;
   
   
   /*
      Resume a suspended domain, the process is restarted from the state where it was frozen by calling domainSuspend().
      Return 0 on success, -1 on error and -2 when there is no connection to a domain.
   */
   virtual int _popc_domainResume(POPvm &vm) = 0;
   
   
   /*
      Get the MAC address of the currently connected domain. The domain can or cannot be running.
      Return the MAC address on success or an empty string on any error.
   */
   virtual const string _popc_domainGetMAC(POPvm &vm) = 0;
   
   /*
      Get the IP address of the currently connected domain. The domain needs to be active in order to get the IP address.
      Return the IP address on success or an empty string on any error.
   */
   virtual int _popc_domainGetIpAddress(POPvm &vm) = 0;
   
   
   /**
    * ViSaG : clementval, wyssen
    * Return if the instance is connected to the passed domain.
    * The standard value of this method is "". So if the user does not pass anything, it will be
    * emtpy and he wants to know if he is connected to any domain.
    * @param The name of the domain
    * @return 1 if connected and 0 if not connected.
    */
   virtual int _popc_domainIsConnected(string domName = "") = 0;
   
   
   /**
    * ViSaG : clementval, wyssen
    * Sends the local public key to the worker guest.
    * @param vm   The POPvm object holding information about the target VM
    * @return 0 on success, -1 on error and -2 when there is no connection to a domain.
    */
   virtual int _popc_sendLocalPublicKey(POPvm &vm) = 0;

   /**
    * ViSaG : clementval
    * Send a public key to the VM and write it in the authorized_keys file
    * @param vm   The POPvm object holding information about the target VM
    * @param pki  The public key 
    * @return 0 if succeed, -1 if failed (error are reported in the popc_wrapper_log file)
    */
   virtual int _popc_sendPublicKey(POPvm &vm, POPString pki) = 0;

   /**
    * ViSaG : clementval
    * Read the public key of the targeted VM and save it in the POPvm object
    * @param vm   The POPvm object holding information about the target VM
    * @return 0 if succeed, -1 if failed (error are reported in the popc_wrapper_log file)
    */
   virtual int _popc_getLocalPublicKey(POPvm &vm) = 0;

   /**
    * ViSaG : clementval
    * Clone a virtual machine
    * @param original   The original VM. This VM will be unusable during the cloning process
    * @param baseName   The baseName of the new VM
    * @param suffix     The suffix (number) appended to the VM baseName
    * @param clonerAP   The access point to the POPCloner object
    * @return 0 if succeed (call to the cloner), -1 if failed (error are reported in the popc_wrapper_log file)
    */
   virtual int _popc_domainClone(POPvm &original, int number, POPString baseName, int suffix, paroc_accesspoint clonerAP) = 0;

   /**
    * ViSaG : clementval
    * Block until the inside tools of the VM are ready to receive command (ESXi = VMware-tools)
    * @param vm   The POPvm object holding information about the target VM
    * @return 0 if succeed, -1 if failed (error are reported in the popc_wrapper_log file)
    */
   virtual int _popc_domainWaitingForTools(POPvm &vm) = 0;
   
   /*
      Returns an error string, which explains the cause of the problem on livbirt side.
   */
   virtual const string _popc_getError() = 0;
};

#endif /* VPOPCWRAPPER_H */
