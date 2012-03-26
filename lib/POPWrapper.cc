/**
 * File : POPWrapper.cc
 * Author : Valentin Clement
 * Description : Implementation of the VPopCWrapper for an non-specfific driver
 * Creation date : 2010/1/27 
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  2010/1/27   Creation of this file on the basis of the original ESXWrapper.cc
 */

#include "POPWrapper.h"
#include "popcloner.ph"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <list>
/*
extern "C"{
   #include "vix.h"
}
/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
*/

//for log
#include <stdarg.h>

using namespace std;
//########## Cloning thread declaration ###################



//########## START libvirt specific declarations ##########

struct _AuthData{
   char *username;
   char *password;
};
typedef struct _AuthData AuthData;

//The list of credential types supported by the auth callback
static int credTypes[] = {
    VIR_CRED_AUTHNAME,
    VIR_CRED_PASSPHRASE
};

//Callback method for authentification
static int authCallback(virConnectCredentialPtr cred, unsigned int ncred, void *cbdata);

//########## END libvirt specific declarations ##########






//########## START Class methods ##########------------------------------

/**
 * POPWrapper constructor
 * @param clonerRef Reference object to the POPCloner parallel object
 */
POPWrapper::POPWrapper(paroc_accesspoint clonerRef){
   _connPtr = NULL;
   _domPtr = NULL;
   _popcloner = clonerRef;
}

/**
 * Destructor of the POPWrapper
 */
POPWrapper::~POPWrapper(){
   if(_connPtr != NULL)
      _popc_connectClose();
   //Check with valgrind
}



//########## START libvirt calls ##########------------------------------

/**
 * Connection to the hypervisor using libvirt
 * @param uri        URI to the ESXi hypervisor account
 * @param user       User of the ESXi hypervisor account
 * @param password   Password of the ESXi hypervisor account
 * @return 0 if succeed
 */
int POPWrapper::_popc_connectOpenAuth(string uri, string user, string password){
   AuthData authData;
   popc_wrapper_log("CONNECTION %s, %s, %s", uri.c_str(), user.c_str(), password.c_str());
   //If there is already a connection, do not connect.
   //TODO. Check if it would be better to close the other connection and reopen that one...
   if(_connPtr != NULL){
      popc_wrapper_log("ERROR: Connection pointer already initialized");
      return -2;
   }

   
   //Get username and password
   authData.username = (char*)user.c_str();
   authData.password = (char*)password.c_str();
   
   virConnectAuth auth = {
      credTypes,
      sizeof(credTypes) / sizeof(int),
      authCallback,
      &authData,
   };

   //Open connection
   _connPtr = virConnectOpenAuth((char*)uri.c_str(), &auth, 0);
   
   if (NULL == _connPtr){
      popc_wrapper_log("ERROR: Connection pointer NULL");   
      return -1;
   }
   return 0;
}


int POPWrapper::_popc_connectClose(){
   if(virConnectClose(_connPtr) < 0)
      return -1;
   
   //Reset the private pointers to NULL
   _connPtr = NULL;
   _domPtr = NULL;
/*   _ESX_hostname.clear();
   _ESX_domName.clear();
   _ESX_user.clear();
   _ESX_pass.clear();*/
   
   return 0;
}

/**
 * Look for a Virtual Machine by its name
 * @param domName Name of the VM
 * @return libvirt pointer to the VM
 */
virDomainPtr POPWrapper::_popc_domainLookupByName(string domName){
   virDomainPtr _crtDomPtr;
   //Check if connection to ESX host exists
   if(_connPtr == NULL){
      return NULL;
   }
   if((_crtDomPtr = virDomainLookupByName(_connPtr, (char*)domName.c_str())) == NULL){
      return NULL;
   }
   
   return _crtDomPtr;
}

/**
 * Get domain state
 * @param vm POPvm object pointing the the right domain
 * @param state Reference to the string that will containing the state
 * @return 0 if succeed
 */
int POPWrapper::_popc_domainState(POPvm &vm, string* state){
   virDomainInfo _domInfo;
   virDomainPtr dom = vm.getDomainPtr();
   
   //Not connected to a domain
   if(dom == NULL)
      return -2;
  
   if ((virDomainGetInfo(dom, &_domInfo)) < 0)
      return -1;

   switch(_domInfo.state){
      case VIR_DOMAIN_NOSTATE :  *state = "no_state"; break;
      case VIR_DOMAIN_RUNNING :  *state = "running"; break;
      case VIR_DOMAIN_BLOCKED :  *state ="blocked"; break;
      case VIR_DOMAIN_PAUSED :   *state = "paused"; break;
      case VIR_DOMAIN_SHUTDOWN : *state = "being_shut_down"; break;
      case VIR_DOMAIN_SHUTOFF :  *state = "shutdown"; break;
      case VIR_DOMAIN_CRASHED :  *state = "crashed"; break;
      default :                  *state = "unknown";
   }
   
   return 0;
}

/**
 * Get free memory of the ESXi node
 * @return Available free memory on success or -1, -2 on failure
 */
long long POPWrapper::_popc_nodeGetFreeMemory(){
   unsigned long long freeMemOnHost = -1;
   if(_connPtr == NULL)
      return -2;
   
   if((freeMemOnHost = virNodeGetFreeMemory(_connPtr)) <= 0)
      return -1;
   
   //libvirt function returns bytes, I will return kilobytes
   return (freeMemOnHost/1024);
}

/**
 * Get ESXi node information
 * @param reference to a node info object
 * @return 0 on success
 */
int POPWrapper::_popc_nodeGetInfo(nodeInfo* info){
   virNodeInfo libInfo;
   
   //Not connected to a node
   if(_connPtr == NULL)
      return -2;
      
   if(virNodeGetInfo(_connPtr, &libInfo) < 0)
      return -1;
   
   //Fill out specific ESX structure with the infos
   info->model = string(libInfo.model); //string indicating the CPU model
   info->memory = libInfo.memory;       //memory size in kilobytes
   info->cpus = libInfo.cpus;           //the number of active CPUs
   info->mhz = libInfo.mhz;             //expected CPU frequency
   info->nodes = libInfo.nodes;	      //the number of NUMA cell, 1 for uniform mem access
   info->sockets = libInfo.sockets;     //number of CPU socket per node
   info->cores = libInfo.cores;         //number of core per socket
   info->threads = libInfo.threads;	   //number of threads per core
   
   return 0;
}

/**
 * Get number of snapshot for a domain
 * @param vm POPvm object pointing the the right domain
 * @return Number of snapshot for this domain or -2 if domain pointer is NULL
 */
int POPWrapper::_popc_domainSnapshotNum(POPvm &vm){
   virDomainPtr dom = vm.getDomainPtr();
   if(dom == NULL)
      return -2;
   
   //Returns nbr of snapshots or -1 if failed
   return virDomainSnapshotNum(dom, 0);
}

/**
 * Get list of snapshots for a domain
 * @param vm      POPvm object pointing the the right domain
 * @param names   Reference to a string list that will contains the snapshots 
 * @param len     
 * @return Number of snapshots in the list or -2 if doamin point is NULL or -1 if failure
 */
int POPWrapper::_popc_domainSnapshotListNames(POPvm &vm, string names[], unsigned short len){
   int nbrOfSnaps, i;
   char* snapNames[len];
   virDomainPtr dom = vm.getDomainPtr();

   if(dom == NULL)
      return -2;
   
   if((nbrOfSnaps = virDomainSnapshotListNames(dom, snapNames, len, 0)) < 0)
      return -1;
   
   //Fill the result array
   for(i=0;i<nbrOfSnaps && i<len; i++)
      names[i] = string(snapNames[i]);
   
   return nbrOfSnaps;
}

/**
 * Revert the domain to a specific snapshot
 * @param vm            POPvm object pointing the the right domain
 * @param snapshotName  Name of the snapshot to be reverted
 * @return 0 on success
 */
int POPWrapper::_popc_domainRevertToSnapshot(POPvm &vm, string snapshotName){
   virDomainSnapshotPtr snapPtr;
   virDomainPtr dom = vm.getDomainPtr();

   if(dom == NULL)
      return -2;
   
   if((snapPtr = virDomainSnapshotLookupByName(dom, snapshotName.c_str(), 0)) == NULL)
      return -3;  //That snapshot does not exist
   
   if(virDomainRevertToSnapshot(snapPtr, 0) < 0)
      return -1;
      
   virDomainSnapshotFree(snapPtr);
   
   return 0;
}

/**
 * Revert a domain to the oldest snapshot
 * @param vm   POPvm object pointing the the right domain
 * @return 0 on success
 */
int POPWrapper::_popc_domainRevertToOldestSnapshot(POPvm &vm){
   string snapName;
   
   if(_popc_domainSnapshotListNames(vm, &snapName, 1) < 0)
      return -1;
   
   return _popc_domainRevertToSnapshot(vm, snapName);
}

/**
 * Create a snapshot for a domain
 * @param vm            POPvm object pointing the the right domain
 * @param name          Name of the new snapshot
 * @param description   Description of the snapshot
 * @return 0 on succeed
 */
int POPWrapper::_popc_domainSnapshotCreate(POPvm &vm, string name, string description){
   ostringstream xmlDesc;
   virDomainPtr dom = vm.getDomainPtr();
   
   if(dom == NULL)
      return -2;
   
   /*
      Preparing the xml description string.
      Please refer to http://libvirt.org/formatsnapshot.html for more information about that
   */
   xmlDesc << "<domainsnapshot>" << endl;
   xmlDesc << "<name>" << name << "</name>" << endl;
   xmlDesc << "<description>" << description << "</description>" << endl;
   xmlDesc << "</domainsnapshot>" << endl;
   
   if(virDomainSnapshotCreateXML(dom, xmlDesc.str().c_str(), 0) == NULL)
      return -1;
   
   return 0;
}

/**
 * Remove a snapshot for a domain
 * @param vm               POPvm object pointing the the right domain
 * @param snapshotName     Name of the snapshot to delete
 * @param removeChildren   True if you want to remove children
 * @return 0 on succeed
 */
int POPWrapper::_popc_domainSnapshotDelete(POPvm &vm, string snapshotName, bool removeChildren){
   virDomainSnapshotPtr snapPtr;
   unsigned int flag;
   virDomainPtr dom = vm.getDomainPtr();   
   if(dom == NULL)
      return -2;
   
   if(removeChildren)
      flag = VIR_DOMAIN_SNAPSHOT_DELETE_CHILDREN;
   else
      flag = 0;
         
   
   if((snapPtr = virDomainSnapshotLookupByName(dom, snapshotName.c_str(), 0)) == NULL)
      return -3;  //That snapshot does not exist
   
   if(virDomainSnapshotDelete(snapPtr, flag) < 0)
      return -1;
   
   virDomainSnapshotFree(snapPtr);
   
   return 0;       
}

/**
 * Set the available memory for a domain
 * @param vm         POPvm object pointing the the right domain
 * @param memoryInKb Avaiblable memory to set in Kb
 * @return 0 on succeed
 */
int POPWrapper::_popc_domainSetMemory(POPvm &vm, unsigned long memoryInKb){
   virDomainPtr dom = vm.getDomainPtr();   

   if(dom == NULL)
      return -2;
   
   return(virDomainSetMemory(dom, memoryInKb));
}

/**
 * Set the maximum memory of a domain
 * @param vm         POPvm object pointing the the right domain
 * @param memoryInKb Maximum memory for this domain in Kb
 * @return 0 on succeed
 */
int POPWrapper::_popc_domainSetMaxMemory(POPvm &vm, unsigned long memoryInKb){
   virDomainPtr dom = vm.getDomainPtr();   
   if(dom == NULL)
      return -2;
   
   return (virDomainSetMaxMemory(dom, memoryInKb));
}

/**
 * Get maximum memory of this domain
 * @param vm   POPvm object pointing the the right domain
 * @return Maxmimum memroy set if succeed, -2 or -1 on failure
 */
long POPWrapper::_popc_domainGetMaxMemory(POPvm &vm){
   virDomainPtr dom = vm.getDomainPtr();   
   long res;
   
   if(dom == NULL)
      return -2;
   
   if((res = virDomainGetMaxMemory(dom)) <= 0) /* Important: Returns 0 in case of problems and not a negative number */
      return -1;
   
   return res;
}

/**
 * Shutdown a domain
 * @param vm   POPvm object pointing the the right domain
 * @return 0 on succeed
 */
int POPWrapper::_popc_domainShutdown(POPvm &vm){
   virDomainPtr dom = vm.getDomainPtr();
   if(dom == NULL)
      return -2;
   
   if(virDomainShutdown(dom) < 0)
      return -1;
   
   dom = NULL;
   vm.setRunningState(POPvm::SHUTDOWN);
   return 0;
}

/**
 * Suspend a domain
 * @param vm   POPvm object pointing the the right domain
 * @return 0 on succeed
 */
int POPWrapper::_popc_domainSuspend(POPvm &vm){
   virDomainPtr dom = vm.getDomainPtr();
   if(dom == NULL)
      return -2;
   vm.setRunningState(POPvm::SUSPENDED);
   return (virDomainSuspend(dom));
}

/**
 * Resume a domain
 * @param vm   POPvm object pointing the the right domain
 * @return 0 on succeed
 */
int POPWrapper::_popc_domainResume(POPvm &vm){
   virDomainPtr dom = vm.getDomainPtr();
   if(dom == NULL)
      return -2;
   
   return (virDomainResume(dom));
}

/**
 * Get the MAC address of a domain
 * @param vm   POPvm object pointing the the right domain
 * @return string containing the MAC address
 */
const string POPWrapper::_popc_domainGetMAC(POPvm &vm){
   char* xmlDescPtr;
   string xmlDesc;
   size_t startPos, endPos;
   string searchFor;

   virDomainPtr dom = vm.getDomainPtr();   
   
   if(dom == NULL)
      return "";
   
   //Try to get description
   if((xmlDescPtr = virDomainGetXMLDesc(dom, 0)) == NULL)
      return "";
   
   xmlDesc = string(xmlDescPtr);
   free(xmlDescPtr);
   
   //Extract only MAC address
   searchFor = "<mac address='";
   startPos = xmlDesc.find(searchFor);
   startPos += searchFor.length();
   endPos = xmlDesc.find("'/>", startPos);
   xmlDesc = xmlDesc.substr(startPos, endPos-startPos);
   
   return xmlDesc;
}

/**
 * Get libvirt error
 * @return string value containing the error message
 */
const string POPWrapper::_popc_getError(){
   int ret;
   virErrorPtr err;
   string errMsg;
   
   if(_connPtr == NULL)
      return "No connection to the hypervisor";
      
   err = (virErrorPtr)malloc(sizeof(*err));
   if(NULL == err)
      return "Could not allocate memory for error data";

   ret = virConnCopyLastError(_connPtr, err);

   switch(ret){
      case 0:
         errMsg =  "No error found";
         break;

      case -1:
         errMsg = "Parameter error when attempting to get last error";
         break;

      default:
         errMsg = ("libvirt reported: " + string(err->message));
         break;
   }

   virResetError(err);
   free(err);

   return errMsg;
}

/**
 * Check if domain is connected
 * @param domName Name of the domain to check
 * @return 0 if succeed
 */
int POPWrapper::_popc_domainIsConnected(string domName){
   //The standard value of this method is "". So if the user does not pass anything, it will be
   //emtpy and he wants to know if he is connected to any domain.
   if(domName.empty()){
      if(_domPtr != NULL)
         return 1;   //Connected
      return 0;      //Not connected
   }
   
 /*  if(_domPtr != NULL && _ESX_domName.compare(domName) == 0)
      return 1;*/
   
   return 0;
}

//########## END libvirt calls ##########


//########## END Class methods ##########







//########## START static libvirt specific functions ##########------------------------------

/* This function will be called by libvirt to obtain credentials in order to
 * authenticate to the hypervisor */
static int authCallback(virConnectCredentialPtr cred, unsigned int ncred, void *cbdata){
   unsigned int i;
   AuthData *authData = (AuthData*)cbdata;

    /* libvirt might request multiple credentials in a single call.
     * This example supports VIR_CRED_AUTHNAME and VIR_CRED_PASSPHRASE
     * credentials only, but there are several other types.
     *
     * A request may also contain a prompt message that can be displayed
     * to the user and a challenge. The challenge is specific to the
     * credential type and hypervisor type.
     *
     * For example the ESX driver passes the hostname of the ESX or vCenter
     * server as challenge. This allows a auth callback to return the
     * proper credentials. */
   for(i = 0; i < ncred ; ++i){
      switch(cred[i].type){
         case VIR_CRED_AUTHNAME:
            cred[i].result = strdup(authData->username);
            if (cred[i].result == NULL) return -1;
            cred[i].resultlen = strlen(cred[i].result);
            break;

         case VIR_CRED_PASSPHRASE:
            cred[i].result = strdup(authData->password);
            if (cred[i].result == NULL) return -1;
            cred[i].resultlen = strlen(cred[i].result);
            break;

         default:
            return -1;
      }
   }

   return 0;
}

//########## END libvirt specific functions ##########



/**
 * Function used to write log message
 * @param format Formatted string and params
 */
int popc_wrapper_log(const char *format,...)
{
	char *tmp=getenv("POPC_TEMP");
	char logfile[256];
	if (tmp!=NULL) sprintf(logfile,"%s/popc_wrapper_log",tmp);
	else strcpy(logfile, "/tmp/pop_node.log");

	FILE *f=fopen(logfile,"a");
	if (f==NULL) return 1;
	time_t t=time(NULL);
	fprintf(f,"%s", ctime(&t));
	va_list ap;
	va_start(ap, format);
	vfprintf(f, format, ap);
	fprintf(f,"%s","\n");
	va_end(ap);
	fclose(f);
	return 0;
}
