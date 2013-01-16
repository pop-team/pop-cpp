/**
 * File : popvm.h
 * Author : Valentin Clement (clementval)
 * Description : Declaration of the POPvm object (This object holds information about the Virtual Machine)
 * Creation date : 2010/11/09
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2010/11/09	Creation of this file
 * clementval  2010/12/02  Add POPBase function to this object
 */

#ifndef _POPC_POPVM_H
#define _POPC_POPVM_H

#include "paroc_string.h"
#include "paroc_base.h"

extern "C"{
   #include <libvirt/libvirt.h>
   #include <libvirt/virterror.h>
}

class POPvm: public paroc_base {
public:
   POPvm();  //POPvm constructor
   POPvm(POPString name, POPString os, POPString snapshot_name, POPString ip_address);
   ~POPvm(); //POPvm destructor
   
   //Enum type
   enum state {FREE, RESERVED};
   enum running_state {SHUTDOWN, SUSPENDED, RUNNING};

   //POPvm methods
   void vm_reserve(POPString popAppId); //Reserve the VM
   bool vm_release();                        //Release the reservation
   void vm_free();         //Free the VM
   bool isFree();          //Check if the VM is free
   bool canExecuteAJob();  //Tell if the VM can execute a job
   bool isKeySent();       //Tell if the Admin key has been sent
   void keySent();         //Set the key sent flag to true

  
   //Getter and Setter
   void setName(POPString name);                   //Set the name of the VM
   void setReservedPOPAppId(POPString popAppId);   //Set the POPAppID for reservation
   void setSnapshotName(POPString ssname);         //Set the Snaphsot name
   void setMaxjobs(int max);                          //Set the maximum number of jobs executed on this VM
   int getMaxjobs();                                  //Get the maximum number of jobs executed on this VM
   int getJobsCount();                                //Get the current number of jobs executed on this VM
   POPString getName();                            //Get the VM name
   POPString getSnapshotName();                    //Get the snapshot name
   POPString getReservedPOPAppId();                //Get the POPAppID used for reservation
   POPString getHostUsername();                       //Get the username used on the VM
   void setHostUsername(POPString username);          //Set the username used on the VM
   POPString getHostPassword();                       //Get the password used on the VM
   void setHostPassword(POPString password);          //Set the password used on the VM
   void setDomainPtr(virDomainPtr domainPtr);         //Set the LIBVIRT domain pointer
   virDomainPtr getDomainPtr();                       //get the LIBVIRT domain pointer
   void setIPAddress(POPString ip);                   //Set the VM IP address
   POPString getIPAddress();                          //Get the VM IP address
   int getCurrentState();                             //Get the VM current state
   POPString getConfigFileName();                     //Get the configuration file name
   void setConfigFileName(POPString configFile);      //Set the configuration file name
   POPString getVolumeName();                         //Get the VM volume name
   void setVolumeName(POPString volume);              //Set the VM volume name
   POPString getPKI();                                //Get the VM PKI
   void setPKI(POPString pki);                        //Set the VM PKI
   bool hasPKI();                                     //Check if the PKI has been read
   void setRunningState(int state);                   //Set the running state
   int getRunningState();                             //Get the current running state
   void incrCloneProcess();                           //Increase the cloning process counter
   int getCloneProcess();                             //Get the cloning process counter
   void decrCloneProcess();                           //Decrease the cloning process counter
   
   virtual void Serialize(paroc_buffer &buf, bool pack); //Method used for marshalling/unmarshalling

private:
   //VM basic informations
   POPString vm_name;               //VM name
   POPString vm_os;                 //VM Host OS
   POPString vm_snapshot_name;      //VM Snapshot name
   POPString vm_ip_address;         //VM ip address
   POPString vm_reservedPOPAppId;   //POPAppID associated with the VM
   POPString vm_config_file;        //Configuration file of this VM
   POPString vm_volume;             //Volum on which the VM is stored
   POPString vm_pki;                //PKI of the VM

   bool vm_keySent;                 //Says if the pki of the has been sent
   int vm_crtState;                 //Current state of the VM (FREE, RESERVED or BUSY)
   POPString vm_host_username;      //The username to use on the host for POP-C++
   POPString vm_host_password;      //The password to use with the host username

   //VM jobs information
   int vm_maxjobs;                  //Maximum job reservation on a VM
   int vm_jobscount;                //Current number of reservation on a VM
   int vm_rstate;


   //Cloning information
   int cloneProcess;                //Counter of current cloning process related to this VM

   //Libvirt pointer
   virDomainPtr vm_domainPtr;       //Libvirt domain pointer

};

#endif
