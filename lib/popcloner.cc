/**
 * File : popcloner.cc
 * Author : Valentin Clement
 * Description : Implementation of the parallel object POPCloner (POP-C++ Global Services). This object is responsible of the 
 *               VM cloning.
 * Creation date : 2010/11/12
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2010/11/12  Creation of this file
 */

#include "popcloner.ph"
#include "ESXWrapper.h"
#include "WrapperFactory.h"
#include "virtual_jobmgr.ph"

#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <list>

extern "C"{
   #include "vix.h"
}

/**
 * ViSaG : clementval
 * Constrcutor of the POPCloner
 * @param challenge  Challenge string needed to stop the service
 * @param deamon     Tell if the parallel object is a deamon or not 
 */
POPCloner::POPCloner(const POPString &challenge, bool deamon) : paroc_service_base(challenge) {
   hypervisorInfoSet = false;
   cloningEnable = false;
   //Use if the cloning method is concurrent
   //locker_counter=1;   

	if(deamon) Start();
}

/**
 * ViSaG : clementval
 * Destructor of the POPCloner
 */
POPCloner::~POPCloner(){

}



/*
 * ##### ESXi Cloning methods #####
 */


/**
 * ViSaG : clementval
 * Set the ESXi hypervisor needed value
 * @param hostname   The hostname or IP address of the ESXi hypervisor
 * @param username   The username with right on the hypervisor
 * @param password   The password on the hypervisor
 * @param urlsdk     The formatted sdk url
 * @param ipaddress  The IP address of the ESXi hypervisor
 */
void POPCloner::setESXiHypervisorData(POPString hostname, POPString username, POPString password, 
   POPString urlsdk, POPString ipaddress){
   _ESX_ipaddress.append(ipaddress.GetString());
   _ESX_host.append("esx://");
   _ESX_host.append(hostname.GetString());
   _ESX_host.append("/?no_verify=1");
   _ESX_user.append(username.GetString());
   _ESX_pass.append(password.GetString());
   _ESX_sdkurl.append(urlsdk.GetString());
   hypervisorInfoSet = true;
   cloningEnable = true;

   //TODO parse parameters to avoid injection
}

/**
 * ViSaG : clementval
 * This methods clone a VM on a ESXi platform
 * @param original   The original POPvm object to clone from
 * @param cloneName  Name of the new VM  
 */
void POPCloner::cloneESXi(POPvm original, POPString cloneName){
   if(!cloningEnable){
      popc_clone_log("ERROR: Cloning is not enable. Could be a problem with hypervisor information");
      return;
   }

   //Check if POPCloner has ESXi hypervisor information
   if(!hypervisorInfoSet){
      popc_clone_log("ERROR: ESXi hypervisor data not found");
      return;
   }
   
   //Create new POPvm object and set unchanged values from its orginal VM
   POPvm clone;
   clone.setName(cloneName);
   clone.setVolumeName(original.getVolumeName());
   clone.setConfigFileName(original.getConfigFileName());
   clone.setHostUsername(original.getHostUsername());
   clone.setHostPassword(original.getHostPassword());
   //popc_clone_log("SSNAME %s", original.getSnapshotName().GetString());
   clone.setSnapshotName(original.getSnapshotName());
   clone.setMaxjobs(original.getMaxjobs());


   ostringstream cmd, cfg;
   FILE *fp;
   int BUFSIZE = 512;
   char buf[BUFSIZE];
   
   //### Step 1 : check if the original VM is suspended or running. If so, shutdown it
   string state;
   
   string vm_path;
   vm_path.append("[");
   vm_path.append(original.getVolumeName().GetString());
   vm_path.append("] ");
   vm_path.append(original.getName().GetString());
   vm_path.append("/");
   vm_path.append(original.getConfigFileName().GetString());
   
   //Declare necessary handles
   VixHandle hostHandle;
   VixHandle jobHandle;
   VixHandle vmHandle;
   VixHandle snapshotHandle;
   VixHandle cloneHandle;
   VixError err;

   //Get the Host handle
   jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_VI_SERVER, _ESX_sdkurl.c_str(), 0, _ESX_user.c_str(), 
      _ESX_pass.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return;
   }
   Vix_ReleaseHandle(jobHandle);


   //Get VM handle
   jobHandle = VixHost_OpenVM(hostHandle, vm_path.c_str(), VIX_VMOPEN_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return;   
   }
   Vix_ReleaseHandle(jobHandle);   

   if(original.getRunningState() == POPvm::SUSPENDED){
       //Power on the guest
      jobHandle = VixVM_PowerOn(vmHandle, 0, VIX_INVALID_HANDLE, NULL, NULL);
      err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
      if(VIX_OK != err){
         popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
         Vix_ReleaseHandle(jobHandle);
         Vix_ReleaseHandle(vmHandle);
         VixHost_Disconnect(hostHandle);
         Vix_ReleaseHandle(hostHandle);
         return;   
      }
      Vix_ReleaseHandle(jobHandle);

      //Wait power on on guest (Doing it twice cause this function is not really reliable)
      for(int i=0; i < 2; i++){
         jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 0, NULL, NULL);
         err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
         if(VIX_OK != err){
            popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
            Vix_ReleaseHandle(jobHandle);
            Vix_ReleaseHandle(vmHandle);
            VixHost_Disconnect(hostHandle);
            Vix_ReleaseHandle(hostHandle);
            return;   
         }
         Vix_ReleaseHandle(jobHandle);
      }

      //Shutdown the VM
      int attempt=0;
      int max_attempt=3;
      bool done=false;
      do{      
         jobHandle = VixVM_PowerOff(vmHandle, VIX_VMPOWEROP_FROM_GUEST, NULL, NULL);
         err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
          if(VIX_OK != err){
            popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
            Vix_ReleaseHandle(jobHandle);
            Vix_ReleaseHandle(vmHandle);
            VixHost_Disconnect(hostHandle);
            Vix_ReleaseHandle(hostHandle);
            attempt++;
         } else {
            done = true;
         }
         Vix_ReleaseHandle(jobHandle);
      } while(attempt < max_attempt && !done);

      
      if(!done){
         popc_clone_log("ERROR: Failed to shutdown the original VM");
         return;
      }


   } else if (original.getRunningState() == POPvm::RUNNING){
      //Shutdown the VM
      jobHandle = VixVM_PowerOff(vmHandle, VIX_VMPOWEROP_FROM_GUEST, NULL, NULL);
      err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
       if(VIX_OK != err){
         popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
         Vix_ReleaseHandle(jobHandle);
         Vix_ReleaseHandle(vmHandle);
         VixHost_Disconnect(hostHandle);
         Vix_ReleaseHandle(hostHandle);
         return;   
      }
      Vix_ReleaseHandle(jobHandle);
   }
 
  
   
   
   //### Step 2 : retrieve the configuration file of the original VM
   cmd << "vmware-cmd -H " << _ESX_ipaddress << " -U " << _ESX_user << " -P " << _ESX_pass << " -l | grep \"/";
   cmd << original.getName().GetString() << "/\"";
   fp = popen(cmd.str().c_str(), "r");
   if(fp == NULL){
      popc_clone_log("Cannot get the cfg for %s", original.getName().GetString());
      return;
   }
   if(fgets(buf, BUFSIZE, fp) != NULL)
      cfg << buf;
      cmd.str(""); cmd.clear();
     // popc_clone_log("<cfg> for %s is %s", original.getName().GetString(), cfg.str().c_str());
      
   

      string formatted_datastore;
      formatted_datastore.append("[");
      formatted_datastore.append(clone.getVolumeName().GetString());
      formatted_datastore.append("]");
         

      //### Step 3 : Create the new folder on the datastore
      cmd << "vifs --server " << _ESX_ipaddress << " --username " << _ESX_user << " --password " << _ESX_pass << " --mkdir ";
      cmd << formatted_datastore << clone.getName().GetString();
      fp = popen(cmd.str().c_str(), "r");
      if(fp == NULL){
         popc_clone_log("Cloning Error : Can't create the new folder");
         return;
      } 
      cmd.str(""); cmd.clear();
         
      //### Step 5 : List the original folder files
          
      cmd << "vifs --server " << _ESX_ipaddress << " --username " << _ESX_user << " --password " << _ESX_pass << " --dir ";
      cmd << formatted_datastore << "/" << original.getName().GetString();
      cmd << "/ | grep -E '(vmdk|vmx|vmsn|vmsd|nvram)' | grep -v flat | grep -v delta";
      fp = popen(cmd.str().c_str(), "r");
      if(fp == NULL){
         popc_clone_log("Cloning Error : Can't list the original folder");
         return;
      } 
      cmd.str(""); cmd.clear();

      //read the output
      list<string> filelst;
      while(fgets(buf, 512, fp) != NULL){
         string file(buf);
         filelst.push_back(file);
      }

      string tmp_file1;
      string tmp_file2;
         
      //Step 6 : copying files
          
      list<string>::iterator it;
      for(it=filelst.begin(); it != filelst.end(); it++){
         string end = (*it).substr((*it).size()-5, (*it).size()-2);
         string base;
         base.append(formatted_datastore);
         base.append(original.getName().GetString());
         base.append("/");
         base.append((*it));
         base = base.substr(0, base.size()-1);

         string remote;
         remote.append(formatted_datastore);
         remote.append(clone.getName().GetString());
         remote.append("/");
         remote.append((*it));

         if(end.compare("vmdk\n") == 0){
            cmd << "vmkfstools --server " << _ESX_ipaddress << " --username " << _ESX_user << " --password ";
            cmd << _ESX_pass << " -i " << base << " " << remote << " && echo END";
            fp = popen(cmd.str().c_str(), "r");
            if(fp == NULL){
               popc_clone_log("Cloning Error : Can't copy file : %s", (*it).c_str());
               return;
            }
            if(fgets(buf, 512, fp) != NULL){
               if(strcmp(buf, "END") != 0)
                  popc_clone_log("Cloning Error : copy error");
            }
            cmd.str("");
            cmd.clear();
         } 
         //Process the vmx configuration file          
         else if (end.compare(".vmx\n") == 0){
            //Download the VMX file
            pid_t pid = getpid();
            cmd << "vifs --server " << _ESX_ipaddress << " --username " << _ESX_user << " --password " << _ESX_pass << " -g ";
            cmd << base << " /tmp/vmx_" << pid << ".vmx && echo END";
            fp = popen(cmd.str().c_str(), "r");
            if(fp == NULL){
               popc_clone_log("Can't can't copy file\n");
               return;
            }
            if(fgets(buf, 512, fp) != NULL){
               string output_cmd(buf);
               if(output_cmd.find("successfully") == string::npos)
                  popc_clone_log("Cloning Error : Download of VMX file failed.\n %s", buf);
            }
            cmd.str(""); cmd.clear();

               
            char cpid[10];
            sprintf(cpid, "%d", pid);

            //Read the original VMX file and write a new file
            string old_vmx_fn;
            old_vmx_fn.append("/tmp/vmx_");
            old_vmx_fn.append(cpid);
            old_vmx_fn.append(".vmx");
            tmp_file1.append(old_vmx_fn);
         
            string new_vmx_fn;
            new_vmx_fn.append("/tmp/vmx_");
            new_vmx_fn.append(cpid);
            new_vmx_fn.append("_2.vmx");
            tmp_file2.append(new_vmx_fn);
               
            ofstream new_vmx;
            new_vmx.open(new_vmx_fn.c_str());

            ifstream old_vmx(old_vmx_fn.c_str());
            if(old_vmx.is_open()){
               string line;
               while(old_vmx.good()){
                  getline(old_vmx, line);
                  if(line.find("displayName") != string::npos){
                     string newLine("displayName = \"");
                     newLine.append(clone.getName().GetString());
                     new_vmx << newLine << "\"\n";
                  } else if((line.find("uuid") != string::npos) 
                     || (line.find("ethernet0.addressType") != string::npos)
                     || (line.find("ethernet0.generatedAddress") != string::npos) 
                     || (line.find("ethernet0.generatedAddressOffset") != string::npos)){
                        
                  } else {
                     new_vmx << line << "\n";
                  }
               }
            }

            new_vmx.close();
            old_vmx.close();
             
            sleep(3);

            string vmx_filename = base.substr((base.rfind("/")+1));
            //Upload the file
            string remote_path(formatted_datastore);
            remote_path.append(clone.getName().GetString());
            remote_path.append("/");
            remote_path.append(vmx_filename);
            cmd << "vifs --server " << _ESX_ipaddress << " --username " << _ESX_user << " --password " << _ESX_pass << " -p ";
            cmd << new_vmx_fn << " " << remote_path << " && echo END";
            //printf("Upload : %s\n", cmd.str().c_str());
            fp = popen(cmd.str().c_str(), "r");
            if(fp == NULL){
               printf("Can't can't copy file\n");
               return;
            }
            if(fgets(buf, 512, fp) != NULL){
               string output_cmd(buf);
               if(output_cmd.find("successfully") == string::npos)
                  popc_clone_log("Cloning Error : upload VMX file %s -> %s\n %s\n %s", new_vmx_fn.c_str(), 
                     remote_path.c_str(), buf, cmd.str().c_str());
            }
            cmd.str(""); cmd.clear();
         } 

         //Copy other files   
         else {
            cmd << "vifs --server " << _ESX_ipaddress << " --username " << _ESX_user << " --password " << _ESX_pass << " -c ";
            cmd << base << " " << remote << " && echo END";
             
            fp = popen(cmd.str().c_str(), "r");
            if(fp == NULL){
               popc_clone_log("Can't can't copy file\n");
               return;
            }
            if(fgets(buf, 512, fp) != NULL){
               string output_cmd(buf);
               if(output_cmd.find("successfully") == string::npos)
                  popc_clone_log("Cloning Error : copying file %s\n%s", base.c_str(), buf);
            }
            cmd.str("");
            cmd.clear();
         }          
      }
      cmd.str(""); cmd.clear();

      //Step 7 : register the new VM

      cmd << "vmware-cmd -H " << _ESX_ipaddress << " -U " << _ESX_user << " -P " << _ESX_pass << " -s register ";
      cmd << formatted_datastore << clone.getName().GetString() << "/" << original.getConfigFileName().GetString();
      fp = popen(cmd.str().c_str(), "r");
      if(fp == NULL){
         popc_clone_log("Can't can't copy file\n");
         return;
      }   
      if(fgets(buf, 512, fp) != NULL){
         string output_cmd(buf);
         if(output_cmd.find("=1") == string::npos)
            popc_clone_log("Cloning Error : register VM\n%s", cmd.str().c_str());
      }

      //Step 8 : remove temporary files & update POPvm clone object information
      //Remove temporary files
      if(remove(tmp_file1.c_str()) < 0)
         popc_clone_log("Cannot remove temporary file : %s", tmp_file1.c_str());
      if(remove(tmp_file2.c_str()) < 0)
         popc_clone_log("Cannot remove temporary file : %s", tmp_file1.c_str());
         



      //Write the information of the new VM in the virtual.conf file. 
      string config_path;
      char* popc_location;
      popc_location = getenv("POPC_LOCATION");
      if(popc_location != NULL){
         config_path.append(popc_location);
      } else {
         config_path.append("/usr/local/popc");
      }
      config_path.append("/etc/virtual.conf");
    
      //Start and stop the new VM to have a functional VM ready to execute jobs
      string clone_vm_path;
      clone_vm_path.append("[");
      clone_vm_path.append(clone.getVolumeName().GetString());
      clone_vm_path.append("] ");
      clone_vm_path.append(clone.getName().GetString());
      clone_vm_path.append("/");
      clone_vm_path.append(clone.getConfigFileName().GetString());
      startNStopVMESXi(clone_vm_path);

      //Calling back the JobMgr with the new VM  
      VirtualJobMgr vjm(paroc_system::jobservice);
      vjm.AddClone(clone, original.getName());
}


/**
 * ViSaG : clementval
 * Start and stop a VM
 * @param vm_path Path of the VM to use with VIX
 */
void POPCloner::startNStopVMESXi(string vm_path){
   
   VixHandle hostHandle;
   VixHandle jobHandle;
   VixHandle vmHandle;
   VixHandle snapshotHandle;
   VixHandle cloneHandle;
   VixError err;

   //Get the Host handle
   jobHandle = VixHost_Connect(VIX_API_VERSION, VIX_SERVICEPROVIDER_VMWARE_VI_SERVER, _ESX_sdkurl.c_str(), 0, _ESX_user.c_str(), 
      _ESX_pass.c_str(), 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return;
   }
   Vix_ReleaseHandle(jobHandle);


   //Get VM handle
   jobHandle = VixHost_OpenVM(hostHandle, vm_path.c_str(), VIX_VMOPEN_NORMAL, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return;   
   }
   Vix_ReleaseHandle(jobHandle);   

   //Power on the guest
   jobHandle = VixVM_PowerOn(vmHandle, 0, VIX_INVALID_HANDLE, NULL, NULL);
   err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
   if(VIX_OK != err){
      popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
      Vix_ReleaseHandle(jobHandle);
      Vix_ReleaseHandle(vmHandle);
      VixHost_Disconnect(hostHandle);
      Vix_ReleaseHandle(hostHandle);
      return;   
   }
   Vix_ReleaseHandle(jobHandle);

   //Wait power on on guest (Doing it twice cause this function is not really reliable)
   for(int i=0; i < 2; i++){
      jobHandle = VixVM_WaitForToolsInGuest(vmHandle, 0, NULL, NULL);
      err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
      if(VIX_OK != err){
         popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
         Vix_ReleaseHandle(jobHandle);
         Vix_ReleaseHandle(vmHandle);
         VixHost_Disconnect(hostHandle);
         Vix_ReleaseHandle(hostHandle);
         return;   
      }
      Vix_ReleaseHandle(jobHandle);
   }

   int attempt=0;
   int max_attempt=3;
   bool done=false;
   do{
      //Shutdown the VM
      jobHandle = VixVM_PowerOff(vmHandle, VIX_VMPOWEROP_FROM_GUEST, NULL, NULL);
      err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
      if(VIX_OK != err){
         popc_clone_log("ERROR: %s", Vix_GetErrorText(err, NULL));
         Vix_ReleaseHandle(jobHandle);
         Vix_ReleaseHandle(vmHandle);
         VixHost_Disconnect(hostHandle);
         Vix_ReleaseHandle(hostHandle);
         attempt++; 
      } else {
         done = true;
      }
      Vix_ReleaseHandle(jobHandle);
   } while ((attempt < max_attempt) && !done);
}

/*
 * ##### End of ESXi Cloning methods #####
 */





/**
 * ViSaG : clementval
 * Method used to write log
 * @param String with format
 */
int popc_clone_log(const char *format,...)
{
	char *tmp=getenv("POPC_TEMP");
	char logfile[256];
	if (tmp!=NULL) sprintf(logfile,"%s/popc_clone_log",tmp);
	else strcpy(logfile, "/tmp/pop_clone.log");

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
