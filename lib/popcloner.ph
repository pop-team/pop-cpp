/**
 * File : popcloner.ph
 * Author : Valentin Clement
 * Description : Declaration of the parallel object POPCloner (POP-C++ Global Services). This object is responsible of the 
 *               VM cloning.
 * Creation date : 2010/11/12
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2010/11/12  Creation of this file
 */

#include "paroc_service_base.ph"
#include "popvm.h"
#include <string>
#include <semaphore.h>

using namespace std;

parclass POPCloner : virtual public paroc_service_base {
public:
   
   //POPCloner constructor
   POPCloner(const POPString &challenge, bool deamon) @{ od.runLocal(true);};
   
   //POPCloner destrcutor   
   ~POPCloner();

   //Cloning function for a ESXi hypervisor
   async seq void cloneESXi(POPvm original, POPString cloneName); 
   
   //Set the information about an ESXi hypervisor
   sync seq void setESXiHypervisorData(POPString hostname, POPString username, POPString password, POPString urlsdk, 
      POPString ipaddress);

   //Set a defined class UID
   classuid(1020);
private:
   
   bool hypervisorInfoSet;       //Tell if the ESXi hypervisor information are set
   paroc_accesspoint callback;   //Access point of the object to call when the cloning is finished
   string _ESX_ipaddress;        //IP address of the ESXi hypervisor
   string _ESX_host;             //Hostname of the ESXi hypervisor
   string _ESX_user;             //Username of the ESXi hypervisor
   string _ESX_pass;             //Password of the ESXi hypervisor
   string _ESX_sdkurl;           //SDK formatted url of the ESXi hypervisor

   void startNStopVMESXi(string vm_path); //Function to start and stop a VM on a ESXi hypervisor

   bool cloningEnable;           //tell if the cloning process is enable or not
};

int popc_clone_log(const char *format,...);  //log function for error
