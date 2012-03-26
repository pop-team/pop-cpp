/**
 * File : virtual_jobmgr.cc
 * Author : Valentin Clement
 * Description : Implementation of the parallel object VirtualJobMgr (POP-C++ Global Services)
 * Creation date : 2010/11/12
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2010/11/12  Creation of this file
 */





#include "virtual_jobmgr.ph"
#include "virtual_popc_search_node.ph"
#include "paroc_utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "rijndael.h"
#include "aes.h"

#define _AES_KEYBITS 256


/**
 * ---------- VirtualJobMgr implementation ----------
 */


/**
 * ViSaG : clementval
 * VirtualJobMgr constructor
 * @param daemon     Tell if the parallel object is a daemon   
 * @param conf       URL of the configuration file as a POPString
 * @param challenge  The challenge string used to shutdown the service
 * @param url        
 * @param nodeAccess Access Point of the associated PSN
 * WARNING : DO NEVER CREATE A PARALLEL OBJECT WITHOUT THE OD.URL INSIDE THE JOBMGR CONSTRUCTOR
 */
VirtualJobMgr::VirtualJobMgr(bool daemon, const POPString &virtconf, const POPString &conf, 
   const POPString &challenge, const POPString &url, const paroc_accesspoint &nodeAccess,
   const paroc_accesspoint &clonerRef, const paroc_accesspoint &psmRef) : JobMgr(daemon, conf, challenge, url, nodeAccess, psmRef) {

   popc_node_log("VirtualJobMgr Started %s", nodeAccess.GetAccessString());

   //Save the reference to the cloner
   vm_clonerRef = clonerRef;
   
   //Virtual Configuration variables
   POPString configFile;
   std::string hypervisorUri;
   std::string hypervisorUser;
   std::string hypervisorPass;
   std::string datastoreName;
   std::string workerName;
   std::string hostUsername;
   std::string hostPassword;
   std::string cleanWorkerSnapshotName;

   unsigned long _aes_rk[_AES_RKLENGTH(_AES_KEYBITS)];
   unsigned char _aes_key[_AES_KEYLENGTH(_AES_KEYBITS)];
   int _aes_i;
   int _aes_nrounds;
   const char *_aes_password;
   std::string _aes_virtConfFilePath;
   char* _aes_popclocation;
   _aes_popclocation = getenv("POPC_LOCATION");
   if(_aes_popclocation != NULL){
      _aes_virtConfFilePath.append(_aes_popclocation);
      _aes_virtConfFilePath.append("/etc/virtual.conf.cr");
   } else {
      _aes_virtConfFilePath.append("/usr/local/popc/etc/virtual.conf.cr");
   }

   std::string _aes_virtConf;

   //Decoded the virtConfiguration file
   FILE *_aes_input;
   std::string _aes_pkey(_AES_KEY);
   _aes_password = _aes_pkey.c_str();
   for (_aes_i = 0; _aes_i < sizeof(_aes_key); _aes_i++)
      _aes_key[_aes_i] = *_aes_password != 0 ? *_aes_password++ : 0;
   _aes_input = fopen(_aes_virtConfFilePath.c_str(), "rb");
   if (_aes_input == NULL)
   {
      popc_node_log("ERROR: Cannot decipher the virtual configuration file: %s",  _aes_virtConfFilePath.c_str());
   }

   _aes_nrounds = rijndaelSetupDecrypt(_aes_rk, _aes_key, 256);
   while (1)
   {
      unsigned char _aes_plaintext[16];
      unsigned char _aes_ciphertext[16];
      int _aes_j;
      if (fread(_aes_ciphertext, sizeof(_aes_ciphertext), 1, _aes_input) != 1)
         break;
     
      std::string _aes_cipher_decode((char*)_aes_ciphertext);

      rijndaelDecrypt(_aes_rk, _aes_nrounds, _aes_ciphertext, _aes_plaintext);
      //Add the decoded bloc to the virtConfiguration string
     
      //Remove cipher text incrusted in plain text
      std::string _aes_plain_decode((char*)_aes_plaintext);
      size_t pos = _aes_plain_decode.find(_aes_cipher_decode);
      std::string _aes_clean_plain = _aes_plain_decode.substr(0, pos);
      //Add decoded text to the full configuration string
      _aes_virtConf.append(_aes_clean_plain);
   }
   
   //Remove useless end of the string
   size_t lastRet = _aes_virtConf.rfind("\n");
   _aes_virtConf = _aes_virtConf.substr(0, lastRet);

   //Parse the decoded virtConfiguration string
   while(_aes_virtConf.size()>0){
      std::string virtConfLine("");
      size_t found;
      found = _aes_virtConf.find("\n");
      if(found!=std::string::npos){
         virtConfLine = _aes_virtConf.substr(0, found);
         _aes_virtConf = _aes_virtConf.substr(found+1, std::string::npos);
      } else {
         virtConfLine = _aes_virtConf.substr(0, std::string::npos);
         _aes_virtConf = "";
      }
      size_t pos;
      pos = virtConfLine.find(" ");
      if (pos != std::string::npos){
         std::string key = virtConfLine.substr(0, pos);
         std::string value = virtConfLine.substr(pos+1);
         if(key.compare("popc_esx_uri") == 0){
            hypervisorUri.append(value);
            std::size_t end = value.rfind("/?no_verify=1")-6;
            POPString ip(value.substr(6, end).c_str());
            if(!paroc_utils::isIPv4Address(ip)){
               popc_node_log("[VJM]ERROR: The ESXi IP address is not well formatted");
               paroc_exception::paroc_throw(errno,"Virtual JobMgr initialization failed");
            }
         } else if (key.compare("popc_esx_username") == 0){
            hypervisorUser.append(value);
            POPString checkedVal(hypervisorUser.c_str());
            if(!paroc_utils::isValidName(checkedVal)){
               popc_node_log("[VJM]ERROR: The ESXi username is not well formatted");
               paroc_exception::paroc_throw(errno,"Virtual JobMgr initialization failed");
            }
         } else if (key.compare("popc_esx_password") == 0){
            hypervisorPass.append(value);
         } else if (key.compare("popc_esx_datastore") == 0){
            datastoreName.append(value);
         } else if (key.compare("popc_esx_maxvm") == 0){
            maxvm = atoi(value.c_str());
         } else if (key.compare("popc_esx_num_clone") == 0){
            vm_clone_base = atoi(value.c_str());
         } else if (key.compare("popc_esx_worker_name") == 0){
            workerName.append(value);
            POPString checkedVal(workerName.c_str());
            if(!paroc_utils::isValidName(checkedVal)){
               popc_node_log("[VJM]ERROR: The ESXi worker name is not well formatted");
               paroc_exception::paroc_throw(errno,"Virtual JobMgr initialization failed");
            }
         } else if (key.compare("popc_esx_hostuser") == 0){
            hostUsername.append(value);
            POPString checkedVal(hostUsername.c_str());
            if(!paroc_utils::isValidName(checkedVal)){
               popc_node_log("[VJM]ERROR: The ESXi guest name is not well formatted");
               paroc_exception::paroc_throw(errno,"Virtual JobMgr initialization failed");
            }
         } else if (key.compare("popc_esx_hostpass") == 0){
            hostPassword.append(value);
         } else if (key.compare("popc_esx_snapshot") == 0){
            cleanWorkerSnapshotName.append(value);
            POPvm newVM;
            POPString _vm_name = workerName.c_str();
            newVM.setName(_vm_name);
            if(vm_list.size()==0){
               std::string file;
               file.append(workerName);
               file.append(".vmx");
               configFile = file.c_str();
            }

            newVM.setConfigFileName(configFile);
            newVM.setVolumeName(datastoreName);
                  
            POPString _vm_snap = cleanWorkerSnapshotName.c_str();
            newVM.setSnapshotName(_vm_snap);
            POPString _vm_hostuser = hostUsername.c_str();
            newVM.setHostUsername(_vm_hostuser);
            POPString _vm_hostpass = hostPassword.c_str();
            newVM.setHostPassword(_vm_hostpass);

            //Put the new POPvm object in the list
            vm_list.push_back(newVM);

            //Clear variable used to read the file
            workerName.clear();
            cleanWorkerSnapshotName.clear();
            hostUsername.clear();
            hostPassword.clear();
         }
      }
   }

   fclose(_aes_input);
 
   //Check if the needed informations are available
   if(hypervisorUri.size() == 0 || hypervisorUser.size() == 0 || hypervisorPass.size() == 0 || vm_list.size() == 0){
      popc_node_log("[VJM]ERROR: VirtualJobMgr initialization failed for configuration file");
      paroc_exception::paroc_throw(errno,"Virtual JobMgr initialization failed");
   }

   //Create the wrapper factory
   WrapperFactory wFactory;
      
   //Create an instance of ESXWrapper via the factory method
   vWrapper = wFactory.createWrapper(WrapperFactory::ESXWRAPPER, vm_clonerRef);

   //Connect to hypervisor
   if(vWrapper->_popc_connectOpenAuth(hypervisorUri, hypervisorUser, hypervisorPass) < 0){
      popc_node_log("[VJM]ERROR: Can't connect to hypervisor...");
      paroc_exception::paroc_throw(errno, "Hypervisor connection failure");
   }
   

   //Get free RAM of hypervisor. The method returns kilobytes
   unsigned long tmpMem;
   if((tmpMem = vWrapper->_popc_nodeGetFreeMemory()) > 0)
      total.mem= (float)(tmpMem / 1024);

   //Divide the total available memory by the number of VM
   float memVM = (total.mem / (vm_list.size()));
   
   //Check existence of the worker VM given at installation
   string _vm_name(vm_list.back().getName().GetString());
   vm_list.back().setDomainPtr(vWrapper->_popc_domainLookupByName(_vm_name));
   if(vm_list.back().getDomainPtr() == NULL){
      popc_node_log("VIRTUAL: Failed to get domain by name.");
      paroc_exception::paroc_throw(errno,"Missing VM");
   }

   //If the worker is running, suspend it
   string snapshotName(vm_list.back().getSnapshotName().GetString());
   vWrapper->_popc_domainRevertToSnapshot(vm_list.back(), snapshotName);
   vm_list.back().setRunningState(POPvm::SHUTDOWN);

   //TODO be more flexible with the worker name
   sscanf((vm_list.back()).getName().GetString(), "%*[^_]_worker%d", &vm_last_number);
   stringstream convert;
   convert << vm_last_number;
   string fullname((vm_list.back()).getName().GetString());
   string prefix(fullname.substr(0, (fullname.size()-convert.str().size())));
   vm_prefix = prefix.c_str();

   //Check if more than one VM
   bool checkingVM = true;
   while(checkingVM){
      string checkedVM(prefix);
      vm_last_number+=1;
      stringstream number;
      number << vm_last_number;
      checkedVM.append(number.str());
      POPvm checkedPOPvm;
      checkedPOPvm.setDomainPtr(vWrapper->_popc_domainLookupByName(checkedVM));
      if(checkedPOPvm.getDomainPtr() == NULL){
         checkingVM = false;
         vm_last_number-=1;
      } else {
         POPString foundVMName(checkedVM.c_str());
         checkedPOPvm.setName(foundVMName);
         checkedPOPvm.setVolumeName(vm_list.front().getVolumeName());
         checkedPOPvm.setConfigFileName(vm_list.front().getConfigFileName());
         checkedPOPvm.setHostUsername(vm_list.front().getHostUsername());
         checkedPOPvm.setHostPassword(vm_list.front().getHostPassword());
         checkedPOPvm.setSnapshotName(vm_list.front().getSnapshotName());
         checkedPOPvm.setMaxjobs(vm_list.front().getMaxjobs());
         string newWorkerState;
         string snapshotName(checkedPOPvm.getSnapshotName().GetString());
         vWrapper->_popc_domainRevertToSnapshot(checkedPOPvm, snapshotName);   
         checkedPOPvm.setRunningState(POPvm::SHUTDOWN);
         vm_list.push_back(checkedPOPvm);
      }
   }

   
    

   // Start cloning process (0 = cloning off, >0 = number of VM to clone, <0 = default behavior)
   if(vm_clone_base != 0){
      //If number of VM to clone at first startup is set by the user
      if(vm_clone_base > 0){
         //Check number of VM to clone
         int available_position = (maxvm-vm_list.size());
         if(vm_clone_base <= available_position){
            vWrapper->_popc_domainClone(vm_list.back(), vm_clone_base, vm_prefix, vm_last_number, clonerRef);
         } else {
            vWrapper->_popc_domainClone(vm_list.back(), available_position, vm_prefix, vm_last_number, clonerRef);
         }        
      } 
      //Cloning VM at first startup set to default value
      else {
         if(vm_list.size() < maxvm){
            //Compute how many clone we need now
            int numberOfClone= (ADVANCE_VM+1) - vm_list.size();
            if(numberOfClone > 0){
               if((numberOfClone + vm_list.size()) > maxvm){
                  numberOfClone = (numberOfClone + vm_list.size()) - maxvm;       
               }
               vWrapper->_popc_domainClone(vm_list.back(), numberOfClone, vm_prefix, vm_last_number, clonerRef);
            }
         }
      }
   }


}

/**
 * ViSaG : clementval
 * VirtualJobMgr destructor
 */
VirtualJobMgr::~VirtualJobMgr(){
   popc_node_log("VirtualJobMgr Destroyed");
}



/**
 * ViSaG : wyssen, clementval
 * This method prepares the worker guest and adds the ssh command to start the object
 * to the argv array which is then executed.
 * @param argv Pointer to the arguments
 * @param n    Pointer to the local counter variable for moving inside the arguments array
 * @return     True if the worker guest could be prepared, false if there was a problem.
 */
bool VirtualJobMgr::PrepareVM(char** argv, int* n, POPString popAppId, POPString reqID)
{
   POPvm *reservedVM;
   //Retrieve the VM reserved for this job
   std::list<POPvm>::iterator it;
   for(it=vm_list.begin(); it != vm_list.end(); it++){
      if(strcmp((*it).getReservedPOPAppId().GetString(), popAppId.GetString()) == 0){
         popc_node_log("MATCHED_VM:%s", (*it).getName().GetString());
         reservedVM = &(*it);               
         break;
      }   
   }

   string workerState;
   string workerIp;
   
   //If machine is not running, start it, resp. revert to the clean snapshot.
   if(vWrapper->_popc_domainState((*reservedVM), &workerState) < 0){
      popc_node_log("VIRTUAL: Failed to get state.");
      return false;
   }
   

   if(workerState.compare("running") != 0){
      string snapshotName((*reservedVM).getSnapshotName().GetString());
      popc_node_log("VIRTUAL: Machine does not run. Revert to snapshot [%s]", snapshotName.c_str());
      if(vWrapper->_popc_domainRevertToSnapshot((*reservedVM), snapshotName) < 0){
         popc_node_log("VIRTUAL: Could not revert to the snapshot.");
         return false;
      }
      else{
         popc_node_log("VIRTUAL: Sent revert action. Start waiting.");
      }
   } else {
      popc_node_log("VIRTUAL: Machine runs already.");
   }
   
   //Get the IP address of the worker guest
   if(vWrapper->_popc_domainGetIpAddress((*reservedVM)) < 0)
      return false;
   
   if(reservedVM->getIPAddress().Length() <= 0){
      popc_node_log("VIRTUAL: IP address could not be retrived");
      return false;
   }
   
   workerIp.append(reservedVM->getIPAddress().GetString());

   //Get local public key 
   if(!(reservedVM->hasPKI())){
      if(vWrapper->_popc_getLocalPublicKey((*reservedVM)) < 0){
         popc_node_log("VIRTUAL: Cannot get the VM public key");
         return false;
      }
   }
   
   /* Send the local public key in order to be able to do ssh command without providing a password
      It must be done each time as we revert from a snapshot which has not the key. */
   if(vWrapper->_popc_sendLocalPublicKey((*reservedVM)) < 0){
      popc_node_log("VIRTUAL: Cannot send local public key to worker guest.");
      return false;
   }
   
   //Prepare ssh command
   char *tmp=getenv("POPC_RSH");
   if(tmp == NULL)
      argv[(*n)++] = (char*)"/usr/bin/ssh";
   else
      argv[(*n)++] = tmp;
   
   argv[*n] = new char[workerIp.size()+1]; //This alloc will be deleted by the JobMgr service
   argv[*n][workerIp.size()] = NULL;
   memcpy(argv[(*n)++], workerIp.c_str(), workerIp.size());
   
   return true;
}


/**
 * ViSaG : clementval, wyssen
 * Execute an object with 
 * @param arguments Command arguments for the parallel object execution
 * @param env Environment to bind with the execution
 * @param pid The PID of the process running the parallel object
 * @return Return 0 if the execution succeed
 */
int VirtualJobMgr::Exec(char **arguments, char *env[], int &pid, POPString popAppId, POPString reqID)
{
	char *file=NULL;
	char *argv[1024];
	char *tmp;
	char sep[]=" \n\r\t";
	POPString str;
	int n=0;
   
   popc_node_log("[VJM] VIRTUAL: Prepare virtual machine now. %s/%s", popAppId.GetString(), reqID.GetString());
   if( ! PrepareVM(argv, &n, popAppId, reqID))
     return -1;
   popc_node_log("[VJM] VIRTUAL: VM ready !");
 


	if (Query("jobmgr",str) && str!=NULL)
	{
		char *tok=strtok_r(str.GetString(),sep,&tmp);
		while (tok!=NULL)
		{
			argv[n++]=tok;
			tok=strtok_r(NULL,sep,&tmp);
		}
	}
   

	while (*arguments!=NULL && n<1023)
	{
		argv[n++]=*arguments;
		arguments++;
	}
	argv[n]=NULL;
	
	
	//TODO remove in prod
	/* ### Added by Wyssen ### */
	int tmpCnt=0;
	char myBuffer[4048];
   char *myPtr;
   myPtr = myBuffer;
   while(argv[tmpCnt]){
      myPtr += sprintf(myPtr, " %s", argv[tmpCnt++]);
   }
   popc_node_log("VIRTUAL: Command: %s\n N=%d", myBuffer, n); 
   /* ### End ### */

	
	if (n==0) return ENOENT;
	file=argv[0];

#ifndef UC_LINUX
	pid=fork();
	if (pid==-1)
	{
		paroc_service_log("Execute command fail. Pause on error...");
		paroc_accesspoint empty;
		Pause(empty,SLEEP_TIME_ON_ERROR);
		return errno;
	}
	else if (pid==0)
	{
		int nf=getdtablesize();
		for (int fd=3;fd<nf;fd++) close(fd);
		if (localuid>=0)
		{
			int ret=setuid(localuid);
			if (ret!=0) perror("ERROR: can not setuid\n");
		}

		if (env!=NULL)
		{
			while (*env!=NULL)
			{
				putenv(strdup(*env));
				env++;
			}
		}
		//Child process
		execvp(file,argv);
		char str[256];
		paroc_service_log("Execution of [%s] fail\n",file);
		_exit(-1);
	}
#else
	pid=vfork();
	if (pid==-1)
	{
		paroc_service_log("Execute command fail. Pause on error...");
		paroc_accesspoint empty;
		Pause(empty,SLEEP_TIME_ON_ERROR);
		return errno;
	}
	else if (pid==0)
	{
		execve(file,argv,env);
		paroc_service_log("Execution of [%s] fail (vfork)\n",file);
		_exit(-1);
	}
#endif

	return 0;
}

/**
 * ViSaG : clementval
 * Check if there is a VM to execute this request
 * @param req The request to check for
 * @return true if there is a VM for that job
 */
bool VirtualJobMgr::checkVM(Request req){
   popc_node_log("[VJM] Check VM for req %s", req.getUniqueId().GetString());

   //Check failed if the job count is too high
   if (jobs.GetCount()>=maxjobs) return false;

   //Check if there is a VM reserved for this POPAppId
   std::list<POPvm>::iterator it;
   for(it=vm_list.begin(); it != vm_list.end(); it++){
      if(!(*it).isFree() && (strcmp(req.getPOPAppId().GetString(), (*it).getReservedPOPAppId().GetString()) == 0)){
         //If one VM has alreaedy been reservered for the App return true
         popc_node_log("CHECK_VM:%s:%d", (*it).getName().GetString(), (*it).getJobsCount());
         return true;
      }
   }

   //Check with free VM
   for(it=vm_list.begin(); it != vm_list.end(); it++){
      if((*it).isFree()){
         //If one VM is free return true;
         popc_node_log("CHECK_VM:%s:%d", (*it).getName().GetString(), (*it).getJobsCount());
         return true;
      }
   }
   return false;
}



/**
 * ViSaG : clementval
 * Reserve the resource. Add the POPAppID for the reservation
 * @param od The Object Description for the parallel object requierments
 * @param inoutfitness The fitness computed for this resource
 * @param popAppID The POP Application ID
 * @return The reservation ID
 */
int VirtualJobMgr::Reserve(const paroc_od &od, float &inoutfitness, POPString popAppId, POPString reqID){
	float flops=0;
	float walltime=0;
	float mem=0;
	float bandwidth=0;

	float require, min;

	mutex
	{
      
      if (jobs.GetCount()>=maxjobs) return 0;

      //Check od for the node
      std::list<POPvm>::iterator it;
      //Check if a VM is reserved for this POPAppID
      for(it=vm_list.begin(); it != vm_list.end(); it++){ //for
         if(!(*it).isFree() && (strcmp((*it).getReservedPOPAppId().GetString(), popAppId.GetString()) == 0)){ //if not free
            float fitness=1;
            if (!od.IsEmpty()){ 
	            //eventually, do the check with od again
            }
            inoutfitness=fitness;
  		      Resources &t=jobs.AddTailNew();
		      t.Id=counter;
		      t.flops=flops;
		      t.mem=mem;
		      t.bandwidth=bandwidth;
		      t.start=time(NULL);
		      t.walltime=walltime;
            t.popAppId=popAppId;
            t.reqID=reqID;
            counter=(counter%1000000000)+1;
            //Update the PSN
            VirtualPOPCSearchNode psn(_localPSN);
            psn.addJob(t.flops, t.mem, t.bandwidth);
            //Reserve the VM once again
            (*it).vm_reserve(popAppId);
            popc_node_log("GIVE_RESID;%d;ON_VM;%s;FOR:%s", t.Id, (*it).getName().GetString(), popAppId.GetString());
            return t.Id;
         } 
      } 

      for(it=vm_list.begin(); it != vm_list.end(); it++){ //for
         if((*it).isFree()){  //if free
            float fitness=1;
            if (!od.IsEmpty()){ //if od not empty
	            //eventually, do the check with od again
            }
            inoutfitness=fitness;
  		      Resources &t=jobs.AddTailNew();
		      t.Id=counter;
		      t.flops=flops;
		      t.mem=mem;
		      t.bandwidth=bandwidth;
		      t.start=time(NULL);
		      t.walltime=walltime;
            t.popAppId=popAppId; 
            t.reqID = reqID;
            counter=(counter%1000000000)+1;
            //Update the PSN
            VirtualPOPCSearchNode psn(_localPSN);
            psn.addJob(t.flops, t.mem, t.bandwidth);
            //Reserve the VM for the first time
            (*it).vm_reserve(popAppId);
            
            //Check remaining free VM
            if(vm_list.size() < maxvm){
               int nbFreeVM;
               std::list<POPvm>::iterator it2;
               for(it2=vm_list.begin(); it2 != vm_list.end(); it2++){
                  if((*it).isFree())
                     nbFreeVM++;
               }
               if(nbFreeVM < ADVANCE_VM){
                  std::list<POPvm>::iterator it2;
                  for(it2=vm_list.begin(); it2 != vm_list.end(); it2++){
                     if((*it).isFree()){
                        vWrapper->_popc_domainClone((*it), 1, vm_prefix, ++vm_last_number, vm_clonerRef);
                     }
                  }
               }
            }  
         	popc_node_log("GIVE_RESID;%d;ON_VM;%s;FOR:%s", t.Id, (*it).getName().GetString(), popAppId.GetString());
         	return t.Id;    
         } 
      } 
	}
   return 0;
}

/**
 * ViSaG : clementval   
 * Method called when an application has finished its execution. In the virtual mode, the VM used for this application will be 
 * suspended
 * @param popAppId   The POP App ID of the application
 * @param initiator  Set to true when the initiator called this method (Node running the main of the application)
 */
void VirtualJobMgr::ApplicationEnd(POPString popAppId, bool initiator){
   JobMgr::ApplicationEnd(popAppId, initiator);
   //Check if a VM has been reserved for this POPAppID and suspend it if found.
   std::list<POPvm>::iterator it;
   for(it=vm_list.begin(); it != vm_list.end(); it++){
      if(!(*it).isFree() && (strcmp((*it).getReservedPOPAppId().GetString(), popAppId.GetString()) == 0)){
         string snapshotName((*it).getSnapshotName().GetString());
         vWrapper->_popc_domainRevertToSnapshot((*it), snapshotName);
         (*it).vm_free();
      }
   }
}

/**
 * ViSaG : clementval
 * Adding a new cloned VM to the list of available VM
 * @param clone   The POPvm object holding the information of the new VM
 */
void VirtualJobMgr::AddClone(POPvm clone, POPString original_name){
   string vm_name(clone.getName().GetString());
   clone.setDomainPtr(vWrapper->_popc_domainLookupByName(vm_name));
   vm_list.push_back(clone);
   vm_list.back().vm_free();
   popc_node_log("New VM Added %d", vm_list.size());
   std::list<POPvm>::iterator it;
   for(it=vm_list.begin(); it != vm_list.end(); it++){
      if(strcmp((*it).getName().GetString(), original_name.GetString()) == 0){
         popc_node_log("Found original cloner");
         (*it).decrCloneProcess();
         if((*it).getCloneProcess() == 0)
            (*it).vm_free();
      }
   }
}

/**
 * ViSaG : clementval
 * Get the POPCloner reference
 * @return The POPCloner reference as a paroc_accesspoint
 */
paroc_accesspoint VirtualJobMgr::getPOPClonerRef(){
   return vm_clonerRef;
}
