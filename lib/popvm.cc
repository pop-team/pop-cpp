/**
 * File : popvm.cc
 * Author : Valentin Clement (clementval)
 * Description : Implementation of the POPvm object (This object holds information abouth the Virtual Machine)
 * Creation date : 2010/11/09
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2010/11/09	Creation of this file
 */


#include "popvm.h"

/**
 * ViSaG : clementval
 * POPvm default constructor
 */
POPvm::POPvm(){
   vm_crtState = FREE;
   vm_jobscount=0;
   POPString no_id("NO_ID");
   vm_snapshot_name = no_id;
   setReservedPOPAppId(no_id);
   vm_keySent = false;
   cloneProcess = 0;
}


/**
 * ViSaG : clementval
 * POPvm full parameter constructor
 * @param name          Name of the VM
 * @param os            OS running on the VM
 * @param snapshot_name Name of the snapshot used to revert the VM
 * @param ip_address    IP address of the VM
 * @param memory        Memory allocated for this VM
 * @param power         Power allocated for this VM
 * @param bandwidth     Bandwidth allocated for this VM
 */
POPvm::POPvm(POPString name, POPString os, POPString snapshot_name, POPString ip_address){
   vm_crtState = FREE;
   vm_name = name;
   vm_os = os;
   vm_snapshot_name = snapshot_name;
   vm_ip_address = ip_address;
   POPString no_id("NO_ID");
   vm_snapshot_name = no_id;
   vm_keySent = false;   
   cloneProcess = 0;
}

/**
 * ViSaG : clementval
 * POPvm destructor
 */
POPvm::~POPvm(){

}

/**
 * ViSaG : clementval
 * Set the max jobs for this VM
 * @param max The number of job executed 
 */
void POPvm::setMaxjobs(int max){
   vm_maxjobs = max;
}

/**
 * ViSaG : clementval
 * Return the maximum jobs that can be executed on this VM
 * @return The maximum number of jobs executed on this VM
 */
int POPvm::getMaxjobs(){
   return vm_maxjobs;
}

/**
 * ViSaG : clementval
 * Tell if the VM can accept one more job
 * @return TRUE if the Vm can accept one more job
 */
bool POPvm::canExecuteAJob(){
   if(vm_maxjobs == 0)
      return true;
   if(vm_jobscount >= vm_maxjobs)
      return false;
   return true;
}

/**
 * ViSaG : clementval
 * Reserve this VM for a specific POP Application
 * @param popAppId The POP Application ID of the Application
 */
void POPvm::vm_reserve(POPString popAppId){
   setReservedPOPAppId(popAppId);
   vm_crtState = RESERVED;    
   vm_jobscount++;
}

/**
 * ViSaG : clementval
 * Release some resource on the VM
 * @param mem        Memory to be released
 * @param power      Power to be released
 * @param bandwidth  Bandwidth to be released
 * @return TRUE if the VM has no more jobs
 */
bool POPvm::vm_release(){
   vm_jobscount--;
   if(vm_jobscount<=0)
      return true;
   return false;
}

/**
 * ViSaG : clementval
 * Set the VM state to FREE
 */
void POPvm::vm_free(){
   vm_crtState = FREE;
   vm_jobscount = 0;
   vm_keySent = false;
}

/**
 * ViSaG : clementval 
 * Check if this VM is free for reservation
 * @return True if the VM is free
 */
bool POPvm::isFree(){
   if(vm_crtState == (FREE))
      return true;
   return false;
}

/**
 * ViSaG : clementval
 * Get the POPAppID 
 * @return The POPAppID for which this VM is reserved
 */
POPString POPvm::getReservedPOPAppId(){
   return vm_reservedPOPAppId;
}

/**
 * ViSaG : clementval
 *
 * @param popAppId The POPAppId to associate with this VM
 */
void POPvm::setReservedPOPAppId(POPString popAppId){
   vm_reservedPOPAppId = popAppId;
}

/**
 * ViSaG : clementval
 * Get the name of the VM
 * @return VM name
 */
POPString POPvm::getName(){
   return vm_name;
}

/** 
 * ViSaG : clementval
 * Get the number of jobs reservation on this VM
 * @return Number of Jobs on this VM
 */
int POPvm::getJobsCount(){
   return vm_jobscount;
}

/**
 * ViSaG : clementval
 * Set the name of the VM
 * @param VM name
 */
void POPvm::setName(POPString name){
   vm_name = name;
}

/**
 * ViSaG : clementval
 * Set the snapshot name of for this VM
 * @param VM snapshot name
 */
void POPvm::setSnapshotName(POPString ssname){
   vm_snapshot_name = ssname;
}



/**
 * ViSaG : clementval
 * Get the snapshot name of for this VM
 * @return VM snapshot name
 */
POPString POPvm::getSnapshotName(){
   return vm_snapshot_name;
}

/**
 * ViSaG : clementval
 * Get the current state of this VM
 * @return An integer representing the current state
 */
int POPvm::getCurrentState(){
   return vm_crtState;
}

/**
 * ViSaG : clementval
 * Get the username associated with the POP-C++ account on this host
 * @return The username associated with the POP-C++ account on this host
 */
POPString POPvm::getHostUsername(){
   return vm_host_username;
}

/**
 * ViSaG : clementval
 * Set the username associated with the POP-C++ account on this host
 * @param The username associated with the POP-C++ account on this host
 */
void POPvm::setHostUsername(POPString username){
   vm_host_username = username;
}

/**
 * ViSaG : clementval
 * Set the password associated with the POP-C++ account on this host
 * @return The password associated with the POP-C++ account on this host
 */
POPString POPvm::getHostPassword(){
   return vm_host_password;
}

/**
 * ViSaG : clementval
 * Set the password associated with the POP-C++ account on this host
 * @param The password associated with the POP-C++ account on this host
 */
void POPvm::setHostPassword(POPString password){
   vm_host_password = password;
}

/**
 * ViSaG : clementval
 * Set the domain pointer of this VM
 * @param Libvirt domain pointer for this VM
 */
void POPvm::setDomainPtr(virDomainPtr domainPtr){
   vm_domainPtr = domainPtr;
}

/**
 * ViSaG : clementval
 * Get the domain pointer of this VM
 * @return The domain pointer associated with this VM
 */
virDomainPtr POPvm::getDomainPtr(){
   return vm_domainPtr;
}

/**
 * ViSaG : clementval
 * Get the configuration file name for this VM
 * @return The configuration file name. If the platform you are using does not use configuration file for VM, the return string
 * will be empty.
 */
POPString POPvm::getConfigFileName(){
   return vm_config_file;
}

/**
 * ViSaG : clementval
 * Set the configuration filename of this VM. If the platform you are using does not use configuration file for VM this method is
 * not used. 
 * @param The configuration filename
 */
void POPvm::setConfigFileName(POPString configFile){
   vm_config_file = configFile;
}

/**
 * ViSaG : clementval
 * Get the volume name where this VM is stored
 * ESXi : the datastore name
 * @return The volume name
 */
POPString POPvm::getVolumeName(){
   return vm_volume;
}

/**
 * ViSaG : clementval
 * Set the volume name where this VM is stored
 * ESXi : the datastore name
 * @param The volume name
 */
void POPvm::setVolumeName(POPString volume){
   vm_volume = volume;
}

/**
 * ViSaG : clementval
 * Set the IP address associated with this VM
 * @param ip The IP address
 */
void POPvm::setIPAddress(POPString ip){
   vm_ip_address = ip;
}

/**
 * ViSaG : clementval
 * Get the IP address associated with this VM
 * @return The IP address
 */
POPString POPvm::getIPAddress(){
   return vm_ip_address;
}

/**
 * ViSaG : clementval
 * Check if the admin key has already been sent to the worker
 * @return True if the key has already been sent
 */
bool POPvm::isKeySent(){
   return vm_keySent;
}

/**
 * ViSaG : clementval
 * Set the key sent flag to true
 */
void POPvm::keySent(){
   vm_keySent = true;
}

/**
 * ViSaG : clementval
 * Get the Public Key Identifier associated with this VM
 * @return The PKI
 */
POPString POPvm::getPKI(){
   return vm_pki;
}

/**
 * ViSaG : clementval
 * Set the Public Key Identifier associated with this VM
 * @param pki The PKI
 */
void POPvm::setPKI(POPString pki){
   vm_pki = pki;
}

/**
 * ViSaG : clementval
 * Tell if the POPvm object has a PKI stored inside
 * @return TRUE if the PKI is set, FALSE if no PKI stored
 */
bool POPvm::hasPKI(){
   if(vm_pki.Length() <= 0)
      return false;
   return true;
}

/**
 * ViSaG : clementval
 * Set the running state of this VM (RUNNING, SHUTDOWN, SUSPENDED)
 * @param state New running state
 */
void POPvm::setRunningState(int state){
   vm_rstate = state;
}

/**
 * ViSaG : clementval
 * Get the current running state for this VM 
 * @return The current running state of this VM
 */
int POPvm::getRunningState(){
   return vm_rstate;
}

/**
 * ViSaG : clementval
 * Increase the cloning process counter of this VM
 */
void POPvm::incrCloneProcess(){
   cloneProcess++;
}

/**
 * ViSaG : clementval
 * Get the cloning process counter of this VM
 */
int POPvm::getCloneProcess(){
   return cloneProcess;
}

/**
 * ViSaG : clementval
 * Decrease the cloning process counter of this VM
 */
void POPvm::decrCloneProcess(){
   cloneProcess--;
}

//##### POPBase inherited methods #####

/**
 * ViSaG : clementval
 * Method used to marshall/unmarshall data into a buffer
 * @param buf  Buffer to pack in or unpack from
 * @param pack If true marshalling, if false unmarshalling
 */
void POPvm::Serialize(paroc_buffer &buf, bool pack)
{
   //Marshalling
	if (pack)   
	{
		POPString name(vm_name);
		buf.Push("vm_name","POPString",1);
		buf.Pack(&name,1);
		buf.Pop();
      
      POPString os(vm_os);
      buf.Push("vm_os", "POPString",1);
      buf.Pack(&os,1);
      buf.Pop();

      POPString snap(vm_snapshot_name);
      buf.Push("vm_snapshot_name", "POPString",1);
      buf.Pack(&snap,1);
      buf.Pop();

      POPString ip(vm_ip_address);
      buf.Push("vm_ip_address", "POPString",1);
      buf.Pack(&ip,1);
      buf.Pop();

      POPString appid(vm_reservedPOPAppId);
      buf.Push("vm_reservedPOPAppId", "POPString",1);
      buf.Pack(&appid,1);
      buf.Pop();

      POPString config(vm_config_file);
      buf.Push("vm_config_file", "POPString",1);
      buf.Pack(&config,1);
      buf.Pop();

      POPString volume(vm_volume);
      buf.Push("vm_volume", "POPString",1);
      buf.Pack(&volume,1);
      buf.Pop();
   
      POPString pki(vm_pki);
      buf.Push("vm_pki", "POPString", 1);
      buf.Pack(&pki, 1);
      buf.Pop();
   
      bool keySent = vm_keySent;
      buf.Push("vm_keySent", "bool", 1);
      buf.Pack(&keySent, 1);
      buf.Pop();

      int crtState = vm_crtState;
      buf.Push("vm_crtState", "int", 1);
      buf.Pack(&crtState, 1);
      buf.Pop();

      POPString host_username(vm_host_username);
      buf.Push("vm_host_username", "POPString", 1);
      buf.Pack(&host_username, 1);
      buf.Pop();

      POPString host_password(vm_host_password);
      buf.Push("vm_host_password", "POPString", 1);
      buf.Pack(&host_password, 1);
      buf.Pop();

      int maxjobs = vm_maxjobs;
      buf.Push("vm_maxjobs", "int", 1);
      buf.Pack(&maxjobs, 1);
      buf.Pop();

      int running = vm_rstate;
      buf.Push("vm_rstate", "int", 1);
      buf.Pack(&running, 1);
      buf.Pop();    
   }
   //Unmarshalling
	else {
      POPString name;
		buf.Push("vm_name","POPString",1);
		buf.UnPack(&name,1);
		buf.Pop();
      vm_name = name;
      
      POPString os;
      buf.Push("vm_os", "POPString",1);
      buf.UnPack(&os,1);
      buf.Pop();
      vm_os = os;

      POPString snap(vm_snapshot_name);
      buf.Push("vm_snapshot_name", "POPString",1);
      buf.UnPack(&snap,1);
      buf.Pop();
      vm_snapshot_name = snap;

      POPString ip;
      buf.Push("vm_ip_address", "POPString",1);
      buf.UnPack(&ip,1);
      buf.Pop();
      vm_ip_address = ip;

      POPString appid;
      buf.Push("vm_reservedPOPAppId", "POPString",1);
      buf.UnPack(&appid,1);
      buf.Pop();
      vm_reservedPOPAppId = appid;

      POPString config;
      buf.Push("vm_config_file", "POPString",1);
      buf.UnPack(&config,1);
      buf.Pop();
      vm_config_file = config;

      POPString volume;
      buf.Push("vm_volume", "POPString",1);
      buf.UnPack(&volume,1);
      buf.Pop();
      vm_volume = volume;
   
      POPString pki;
      buf.Push("vm_pki", "POPString", 1);
      buf.UnPack(&pki, 1);
      buf.Pop();
      vm_pki = pki;

      bool keySent;
      buf.Push("vm_keySent", "bool", 1);
      buf.UnPack(&keySent, 1);
      buf.Pop();
      vm_keySent = keySent;

      int crtState;
      buf.Push("vm_crtState", "int", 1);
      buf.UnPack(&crtState, 1);
      buf.Pop();
      vm_crtState = crtState;

      POPString host_username;
      buf.Push("vm_host_username", "POPString", 1);
      buf.UnPack(&host_username, 1);
      buf.Pop();
      vm_host_username = host_username;

      POPString host_password;
      buf.Push("vm_host_password", "POPString", 1);
      buf.UnPack(&host_password, 1);
      buf.Pop();
      vm_host_password = host_password;

      int maxjobs;
      buf.Push("vm_maxjobs", "int", 1);
      buf.UnPack(&maxjobs, 1);
      buf.Pop();
      vm_maxjobs = maxjobs;

      int running;
      buf.Push("vm_rstate", "int", 1);
      buf.UnPack(&running, 1);
      buf.Pop();
      vm_rstate = running;
	}
}




