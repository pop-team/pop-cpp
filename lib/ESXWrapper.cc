/**
 * File : ESXWrapper.cc
 * Author : Adrian Wyssen, Clement Valentin
 * Description : Implementation of the VPopCWrapper for an ESX driver
 * Creation date : 04/08/2010
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  2010/1/27   move all non-secific methods to the POPWrapper object
 */

#include "ESXWrapper.h"

#include "popcloner.ph"

#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>

extern "C"{
   #include "vix.h"
}


//for log
#include <stdarg.h>

using namespace std;

//########## START Class methods ##########------------------------------
/**
 * ESXWrapper constructor
 * @clonerRef Reference to the POPCloner parallel object
 */
ESXWrapper::ESXWrapper(paroc_accesspoint clonerRef) : POPWrapper(clonerRef) {

}

/**
 * ESXWrapper destructor
 */
ESXWrapper::~ESXWrapper(){

}



//########## START libvirt calls ##########------------------------------

/**
 * Connection to the hypervisor using libvirt
 * @param uri        URI to the ESXi hypervisor account
 * @param user       User of the ESXi hypervisor account
 * @param password   Password of the ESXi hypervisor account
 * @return 0 if succeed
 */
int ESXWrapper::_popc_connectOpenAuth(string uri, string user, string password){

   //Call super method to authenticate 
   POPWrapper::_popc_connectOpenAuth(uri, user, password);

   //Get the hostname of the hypervisor
   _ESX_hostname = string(virConnectGetHostname(_connPtr));
   _ESX_user = user;
   _ESX_pass = password;
   
   
   //Creation of the SDK URL
   size_t fst_slash, snd_slash, end;
   fst_slash = _ESX_hostname.find("/");
   snd_slash = _ESX_hostname.find("/", fst_slash+1);
   end = _ESX_hostname.find("/", snd_slash+1);
   string ipaddress = _ESX_hostname.substr(snd_slash+1, end);
   _ESX_ipaddress.append(ipaddress);
   _ESX_sdkurl.append("https://");
   _ESX_sdkurl.append(ipaddress);
   _ESX_sdkurl.append("/sdk");
   
   POPCloner cloner(_popcloner);
   POPString tmphost(_ESX_hostname.c_str());
   POPString tmpuser(_ESX_user.c_str());
   POPString tmppass(_ESX_pass.c_str());
   POPString tmpurlsdk(_ESX_sdkurl.c_str());
   POPString tmpip(_ESX_ipaddress.c_str());
   cloner.setESXiHypervisorData(tmphost, tmpuser, tmppass, tmpurlsdk, tmpip);

   return 0;
}


//########## END libvirt calls ##########




//########## START VIX API methods ##########------------------------------


/**
 * ViSaG : clementval
 * Set the address IP in the POPvm object passed in parameter
 * @param The POPvm object associated with the worker Vm to contact
 * @return 0 if success, -1 if failed. Errors are reported in the Wrapper log file
 */
int ESXWrapper::_popc_domainGetIpAddress(POPvm &vm){
   //Prepare the VM config path <cfg>
   string vm_path;
   vm_path.append("[");
   vm_path.append(vm.getVolumeName().GetString());
   vm_path.append("] ");
   vm_path.append(vm.getName().GetString());
   vm_path.append("/");
   vm_path.append(vm.getConfigFileName().GetString());

   //Delcare all necessary handle
   VixHandle hostHandle;
   VixHandle jobHandle;
   VixHandle vmHandle;
   VixError err;
   char *readvalue = NULL;


   //Connect to hypervisor
   jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_VI_SERVER,  _ESX_sdkurl.c_str(), 0, _ESX_user.c_str(), _ESX_pass.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("ERROR (hypervisor connection): %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      VixHost_Disconnect(hostHandle);
      return -1;
   }
   Vix_ReleaseHandle(jobHandle);


   //Get VM handle
   jobHandle = VixHost_OpenVM(hostHandle, vm_path.c_str(), VIX_VMOPEN_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("ERROR (opening VM): %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      return -1;
   }
   Vix_ReleaseHandle(jobHandle);   

   //Power on the guest
   jobHandle = VixVM_PowerOn(vmHandle, 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("ERROR (powering on VM): %s", Vix_GetErrorText(err, NULL));
      return -1;
   }
   Vix_ReleaseHandle(jobHandle);

   //Wait power on on guest
   jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 300, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("ERROR (waiting for tools): %s", Vix_GetErrorText(err, NULL));
      return -1; 
   }
   Vix_ReleaseHandle(jobHandle);

   do{
      jobHandle = VixVM_ReadVariable(vmHandle, VIX_VM_GUEST_VARIABLE, "ip", 0, NULL, NULL); 
      err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_VM_VARIABLE_STRING, &readvalue, VIX_PROPERTY_NONE);
      if(VIX_OK != err){
         popc_wrapper_log("ERROR (reading var): %s", Vix_GetErrorText(err, NULL));
         return -1;
      }
      Vix_ReleaseHandle(jobHandle);
   } while (strcmp(readvalue, "unknown") == 0 || strcmp(readvalue, "") == 0);

   //Set the IP in the POPvm object
   vm.setIPAddress(readvalue);


   return 0;
}




/**
 * ViSaG : clementval
 * Get the local public key of the worker VM
 * @param The POPvm object associated with the worker VM to contact
 * @return 0 if success, -1 if failed. Errors are reported in the wrapper log file
 */
int ESXWrapper::_popc_getLocalPublicKey(POPvm &vm){
  //Prepare the VM config path <cfg>
   string vm_path;
   vm_path.append("[");
   vm_path.append(vm.getVolumeName().GetString());
   vm_path.append("] ");
   vm_path.append(vm.getName().GetString());
   vm_path.append("/");
   vm_path.append(vm.getConfigFileName().GetString());
   
   //Declare necessary handles
   VixHandle hostHandle;
   VixHandle jobHandle;
   VixHandle vmHandle;
   VixError err;

   //Get the Host handle
   jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_VI_SERVER, _ESX_sdkurl.c_str(), 0, _ESX_user.c_str(), _ESX_pass.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Get PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -1;
   }
   Vix_ReleaseHandle(jobHandle);

   //Get VM handle
   jobHandle = VixHost_OpenVM(hostHandle, vm_path.c_str(), VIX_VMOPEN_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Get PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -2;   
   }
   Vix_ReleaseHandle(jobHandle);   

   //Power on the guest
   jobHandle = VixVM_PowerOn(vmHandle, 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Get PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -3;   
   }
   Vix_ReleaseHandle(jobHandle);

   //Wait power on on guest
   jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 300, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Get PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -4;   
   }
   Vix_ReleaseHandle(jobHandle);

   //Login in the guest 
   jobHandle = VixVM_LoginInGuest(vmHandle, vm.getHostUsername().GetString(), vm.getHostPassword().GetString(), 0, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Get PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -5;   
   }
   Vix_ReleaseHandle(jobHandle);

   popc_wrapper_log("login in guest ok");

   //Create the local key path
   string localKeyPath("/home/");
   localKeyPath.append(vm.getHostUsername().GetString());
   localKeyPath.append("/.ssh/id_rsa.pub");
   popc_wrapper_log("dest: %s", localKeyPath.c_str());

   //Create the destination path
   string destPath("/tmp/");
   destPath.append(vm.getName().GetString());
   destPath.append("_id_rsa.pub");
   popc_wrapper_log("dest: %s", destPath.c_str());

   //Copying the file
   jobHandle = VixVM_CopyFileFromGuestToHost(vmHandle, localKeyPath.c_str(), destPath.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Get PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -6;   
   }
   Vix_ReleaseHandle(jobHandle);


   //read the key file
   ifstream keyfile(destPath.c_str());
   string line;
   string key;
   if(keyfile.is_open()){
      while(keyfile.good()){
         getline(keyfile, line); 
         if(line.length() > 0)
            key.append(line);
      }
   }
   keyfile.close();
   POPString pki = key.c_str();
   vm.setPKI(pki);

   return 0;
}

/**
 * ViSaG : clementval
 * Send the local public key (admin VM pki) to the worker VM and write it in the authorized_keys file.
 * @param The POPvm object associated with the worker to contact
 * @return 0 if success, -1 if failed. Errors are reported in the wrapper log file.
 */
int ESXWrapper::_popc_sendLocalPublicKey(POPvm &vm){
   //If the key has already been sent, do not send it again for nothing
   if(vm.isKeySent())
      return 0;

   //Prepare the VM config path <cfg>
   string vm_path;
   vm_path.append("[");
   vm_path.append(vm.getVolumeName().GetString());
   vm_path.append("] ");
   vm_path.append(vm.getName().GetString());
   vm_path.append("/");
   vm_path.append(vm.getConfigFileName().GetString());
   popc_wrapper_log("cfg: %s", vm_path.c_str());
   
   //Declare necessary handles
   VixHandle hostHandle;
   VixHandle jobHandle;
   VixHandle vmHandle;
   VixError err;

   //Get the Host handle
   jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_VI_SERVER, _ESX_sdkurl.c_str(), 0, _ESX_user.c_str(), _ESX_pass.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send Admin PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -1;
   }
   Vix_ReleaseHandle(jobHandle);

   popc_wrapper_log("connection ok");

   //Get VM handle
   jobHandle = VixHost_OpenVM(hostHandle, vm_path.c_str(), VIX_VMOPEN_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send Admin PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -2;   
   }
   Vix_ReleaseHandle(jobHandle);   

   popc_wrapper_log("vm handle ok");

   //Power on the guest
   jobHandle = VixVM_PowerOn(vmHandle, 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send Admin PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -3;   
   }
   Vix_ReleaseHandle(jobHandle);

   popc_wrapper_log("power on ok");

   //Wait power on on guest
   jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 300, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send Admin PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -4;   
   }
   Vix_ReleaseHandle(jobHandle);

   popc_wrapper_log("wait for tools ok");

   popc_wrapper_log("user: %s, pass: %s", vm.getHostUsername().GetString(), vm.getHostPassword().GetString());
   //Login in the guest 
   jobHandle = VixVM_LoginInGuest(vmHandle, vm.getHostUsername().GetString(), vm.getHostPassword().GetString(), 0, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send Admin PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -5;   
   }
   Vix_ReleaseHandle(jobHandle);

   //Create the local key path
   string localKeyPath("/home/");
   localKeyPath.append(vm.getHostUsername().GetString());
   localKeyPath.append("/.ssh/id_rsa.pub");
   popc_wrapper_log("dest: %s", localKeyPath.c_str());

   //Create the destination path
   string destPath("/tmp/");
   destPath.append(vm.getName().GetString());
   destPath.append("_id_rsa.pub");
   popc_wrapper_log("dest: %s", destPath.c_str());

   //Copying the file
   jobHandle = VixVM_CopyFileFromHostToGuest(vmHandle, localKeyPath.c_str(), destPath.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send Admin PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -6;   
   }
   Vix_ReleaseHandle(jobHandle);


   //create command to execute on host
   string cmd(destPath);
   cmd.append(" >> /home/");
   cmd.append(vm.getHostUsername().GetString());
   cmd.append("/.ssh/authorized_keys");
   popc_wrapper_log("cmd: %s", cmd.c_str());   

   //Write key
   jobHandle = VixVM_RunProgramInGuest(vmHandle, "/bin/cat", cmd.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send Admin PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -1;   
   }
   Vix_ReleaseHandle(jobHandle);
   Vix_ReleaseHandle(vmHandle);
   VixHost_Disconnect(hostHandle);
   Vix_ReleaseHandle(hostHandle);

   //Set the key sent flag to true
   vm.keySent();

   return 0;
}

/**
 * ViSaG : clementval
 * Send a pki to the VM
 * @param vm   The destination VM
 * @param pki  The PKI
 * @return 0 if succeed, -1 if failed
 */
int ESXWrapper::_popc_sendPublicKey(POPvm &vm, POPString pki){
 //Prepare the VM config path <cfg>
   string vm_path;
   vm_path.append("[");
   vm_path.append(vm.getVolumeName().GetString());
   vm_path.append("] ");
   vm_path.append(vm.getName().GetString());
   vm_path.append("/");
   vm_path.append(vm.getConfigFileName().GetString());
   popc_wrapper_log("cfg: %s", vm_path.c_str());
   
   //Declare necessary handles
   VixHandle hostHandle;
   VixHandle jobHandle;
   VixHandle vmHandle;
   VixError err;

   //Get the Host handle
   jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_VI_SERVER, _ESX_sdkurl.c_str(), 0, _ESX_user.c_str(), _ESX_pass.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -1;
   }
   Vix_ReleaseHandle(jobHandle);


   //Get VM handle
   jobHandle = VixHost_OpenVM(hostHandle, vm_path.c_str(), VIX_VMOPEN_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -2;   
   }
   Vix_ReleaseHandle(jobHandle);   


   //Power on the guest
   jobHandle = VixVM_PowerOn(vmHandle, 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -3;   
   }
   Vix_ReleaseHandle(jobHandle);


   //Wait power on on guest
   jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 300, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -4;   
   }
   Vix_ReleaseHandle(jobHandle);


   //popc_wrapper_log("user: %s, pass: %s", vm.getHostUsername().GetString(), vm.getHostPassword().GetString());
   //Login in the guest 
   jobHandle = VixVM_LoginInGuest(vmHandle, vm.getHostUsername().GetString(), vm.getHostPassword().GetString(), 0, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -5;   
   }
   Vix_ReleaseHandle(jobHandle);

   //Write the pki in a file
   string localKeyPath("/tmp/main_");
   localKeyPath.append(vm.getReservedPOPAppId().GetString());

   ofstream keyFile(localKeyPath.c_str());
   if(keyFile.is_open()){
      keyFile << pki.GetString();
      //Return character is very important. Without this, keys will be attached to each other and unusable for the ssh server
      keyFile << "\n";  
      keyFile.close();
   } else {
      popc_wrapper_log("Unable to write the pki in a file");
      return -1;
   }

   //Create the destination path
   string destPath("/tmp/");
   destPath.append(vm.getName().GetString());
   destPath.append("_id_rsa.pub");

   //Copying the file
   jobHandle = VixVM_CopyFileFromHostToGuest(vmHandle, localKeyPath.c_str(), destPath.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -6;   
   }
   Vix_ReleaseHandle(jobHandle);


   //create command to execute on host
   string cmd(destPath);
   cmd.append(" >> /home/");
   cmd.append(vm.getHostUsername().GetString());
   cmd.append("/.ssh/authorized_keys");
   //popc_wrapper_log("cmd: %s", cmd.c_str());   

   //Write key
   jobHandle = VixVM_RunProgramInGuest(vmHandle, "/bin/cat", cmd.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("[Send PKI] ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -1;   
   }
   Vix_ReleaseHandle(jobHandle);
   Vix_ReleaseHandle(vmHandle);
   VixHost_Disconnect(hostHandle);
   Vix_ReleaseHandle(hostHandle);
   return 0;
}


//########## END VIX API methods ##########

/**
 * ViSaG : clementval
 * Clone one or more times a VM
 * @param original   The original Vm to be cloned (The POPvm object state MUST be busy)
 * @param number     Number of VM to be cloned
 * @param vjm        Access point to the JobMgr to send a callback    
 * @param baseName   Base name of the clone VM
 * @param suffix     Start number which will be suffixed to the base name of the VM
 * @return 0 if the call succeed, -1 if POPCloner couldn't be called
 */
int ESXWrapper::_popc_domainClone(POPvm &original, int number, POPString baseName, int suffix, paroc_accesspoint clonerAP){
   //Reserver the VM for cloning   
   POPString clonerAppId("CLONER_RESERVATION");
   original.vm_reserve(clonerAppId);
   if(!clonerAP.IsEmpty()){
      POPCloner cloner(clonerAP);
      //Create the new VM name
      int i;
      for(i=0; i < number; i++){
         POPString nname;
         string newName(baseName.GetString());
         stringstream convert;
         convert << ++suffix;
         newName.append(convert.str());
         popc_wrapper_log("VM %s will be cloned as %s", original.getName().GetString(), newName.c_str());
         nname = newName.c_str();
         original.incrCloneProcess();
         cloner.cloneESXi(original, nname);
      }
   } else {
      popc_wrapper_log("POPCloner is not running, unable to clone VM");
      return -1;
   }
   
  
  
   
 
   return 0;
}


/**
 * ViSaG : clementval
 * Waiting for VM guest tools
 * @param vm POPvm object associated with the VM
 * @return 0 if succeed, -1 if failed. 
 */
int ESXWrapper::_popc_domainWaitingForTools(POPvm &vm){
   //Prepare the VM config path <cfg>
   string vm_path;
   vm_path.append("[");
   vm_path.append(vm.getVolumeName().GetString());
   vm_path.append("] ");
   vm_path.append(vm.getName().GetString());
   vm_path.append("/");
   vm_path.append(vm.getConfigFileName().GetString());
   
   //Declare necessary handles
   VixHandle hostHandle;
   VixHandle jobHandle;
   VixHandle vmHandle;

   VixError err;

   //Get the Host handle
   jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_VI_SERVER, _ESX_sdkurl.c_str(), 0, _ESX_user.c_str(), _ESX_pass.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -1;
   }
   Vix_ReleaseHandle(jobHandle);


   //Get VM handle
   jobHandle = VixHost_OpenVM(hostHandle, vm_path.c_str(), VIX_VMOPEN_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -2;   
   }
   Vix_ReleaseHandle(jobHandle);   

   //Power on the guest
   jobHandle = VixVM_PowerOn(vmHandle, 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -3;   
   }
   Vix_ReleaseHandle(jobHandle);

   //Wait power on on guest
   jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 300, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_wrapper_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return -4;   
   }
   Vix_ReleaseHandle(jobHandle);
   vm.setRunningState(POPvm::RUNNING);
   return 0;
}


//########## END Class methods ##########








