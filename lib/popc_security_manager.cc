/**
 * File : popc_security_manager.cc
 * Author : Valentin Clement (clementval)
 * Description : Implementation file of the security manager for POP-C++ runtime
 * Creation date : 2010/10/19
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval  2010/10/19  First version of this file
 * clementval  2010/10/21  All the code added for the ViSaG project is commented with the following signature (ViSaG : clementval)
 * clementval  2010/10/27  Implement the PKI rerouting for the reference passing
 */

#include "popc_security_manager.ph"
#include "popc_search_node.ph"


#include <fstream>
#include <iostream>
#include <sstream>
#include <signal.h>

using namespace std;


/**
 * ViSaG : clementval
 * Security Manager constructor
 * @param challenge  Challenge string to stop the service
 * @param deamon     Tell if the parallel object behaves as a deamon
 */
POPCSecurityManager::POPCSecurityManager(const POPString &challenge, bool deamon) : paroc_service_base(challenge) {
	popc_security_log("Security Manager created");
	if(deamon) Start();
}

/**
 * ViSaG : clementval
 * Security Manager destructor
 */
POPCSecurityManager::~POPCSecurityManager(){
	popc_security_log("POPCSecurityManager destroyed");
}

/**
 * ViSaG : clementval
 * Set the reference to the local Job Manager running on the same node than this Security Manager
 * @param jobmgr Access Point to the local Job Manager
 */
void POPCSecurityManager::setJobMgrRef(paroc_accesspoint jobmgr){
   _localJobMgr = jobmgr;
}

/**
 * ViSaG : clementval
 * Get the reference of the local Job Manager running on the same node than this Security Manager
 * @return Access Point to the local Job Manager
 */
paroc_accesspoint POPCSecurityManager::getJobMgrRef(){
   return _localJobMgr;
}
   
/**
 * ViSaG : clementval
 * Set the reference to the local POPC Search Node running on the same node than this Security Manager
 * @param jobmgr Access Point to the local POPC Search Node
 */
void POPCSecurityManager::setPSNRef(paroc_accesspoint psn){
   _localPSN = psn;
}

/**
 * ViSaG : clementval
 * Get the reference of the local POPC Search Node running on the same node than this Security Manager
 * @return Access Point to the local POPC Search Node
 */
paroc_accesspoint POPCSecurityManager::getPSNRef(){
   return _localPSN;
}


/**
 * ViSaG : clementval
 * Get the local SSH public key of this node
 * @return the local SSH public key of this node
 */
POPString POPCSecurityManager::getLocalPKI(){
   return _localPublicKey;
}


/**
 * ViSaG : clementval
 * Write the public key into the authorized_keys file if this key is not yet in the file
 * @param pki	The public key to write in the local authorized_keys file
 * @param 
 */
void POPCSecurityManager::writePKI(POPString popAppId, POPString pki){
   POPString crtPki = pki;  
  
   if(strcmp(crtPki.GetString(), _localPublicKey.GetString())!=0){
      //Get the $HOME env variable
      char *path; 
      path = getenv("HOME");
      if(path==NULL)
         paroc_exception::paroc_throw(errno,"Cannot read $HOME");
      //Set the path of the public key
      char buffer[256];
      snprintf(buffer, 256, "%s/.ssh/authorized_keys", path);
      FILE *fp;
      int BUF_SIZE=15;
      char buf[BUF_SIZE];
      int error_code = 0;
      std::ostringstream cmd; 
      cmd.str("");  
      cmd.clear();
      //WARNING : code injection can occur
      //TODO replace with a data structure including all the keys
      cmd << "cat " << buffer << " | grep \"" << crtPki.GetString() << "\" && echo found";
      fp = popen(cmd.str().c_str(), "r");
      if(fp==NULL) error_code=-1;   
      if(fgets(buf, BUF_SIZE, fp) == NULL) error_code=-1;

      //Key not found in the file
      if(error_code != 0){
         ofstream os;
         os.open(buffer, ios::out | ios::app);
         if(os.is_open()){
            os << crtPki.GetString() << endl;
            os.close();
         } else {
            paroc_exception::paroc_throw(errno,"Cannot Add external PKI");
         }
         sprintf(log, "PSM_ADD_NEW_PK:%s", crtPki.GetString());
         popc_security_log(log);
      }  
   }
}

/**
 * ViSaG : clementval
 * Initialize the SSH secure mode. Read the local SSH public keys.
 * TODO : Read the current authorized_keys file.
 */
void POPCSecurityManager::initSSHMode(){
   /*
    * Read the local public key
    */
  
   int length;

   //Get the $HOME env variable
   char *path; 
   path = getenv("HOME");
   if(path==NULL){
      popc_security_log("Can't read $HOME");
      paroc_exception::paroc_throw(errno,"Cannot read $HOME");
   }

   //Set the path of the public key
   char buffer[256];
   sprintf(buffer, "%s/.ssh/id_rsa.pub", path);

   //Check if the public key exists
   ifstream is;
   is.open(buffer, ios::binary);

   //Get length of the file
   is.seekg(0, ios::end);
   length = is.tellg();
   if(length == -1){
      popc_security_log("No SSH public key");
      paroc_exception::paroc_throw(errno,"No SSH Public Key found");
   }
   is.seekg(0, ios::beg);

   std::string line;
   getline(is, line);
   is.close();
   _localPublicKey = line.c_str();
   
   sprintf(log, "PUBLIC_KEY:%s", _localPublicKey.GetString());
   popc_security_log(log);


   POPCSearchNode psn(_localPSN);
   psn.setPKI(_localPublicKey);

   /*
    * Read the local authorized_keys file
    */

   
}

/**
 * ViSaG : clementval
 * Return the PKI of the node running the main of the application defined by the POPAppId
 * @param popapid The POP Application ID that defined the main node
 * @return The PKI of the main node or an empty POPString
 */
POPString POPCSecurityManager::getMainPKIFromMapping(POPString popappid){
   POPString foo("");
   if(_mainPKIMapping.empty())
      return foo;
   map<POPString, POPString>::iterator it;
   for(it = _mainPKIMapping.begin(); it != _mainPKIMapping.end(); it++){
      POPString crt = (*it).first;
      if(strcmp(crt.GetString(), popappid.GetString()) == 0){
         POPString found = (*it).second;
         return found;
      }
   }
   return foo;
}

/**
 * ViSaG : clementval
 * Return the Access Point of the node running the main of the application defined by the POPAppId
 * @param popapid The POP Application ID that defined the main node
 * @return The Access Point of the main node or an empty POPString
 */
paroc_accesspoint POPCSecurityManager::getMainAPFromMapping(POPString popappid){
   //Defined a blank access point   
   paroc_accesspoint foo;
   //Return the blank access point if the map ios empty
   if(_initiatorMapping.empty())
      return foo;
   
   //Look for the right mapping with the POPAppId
   map<POPString, paroc_accesspoint>::iterator it;
   for(it = _initiatorMapping.begin(); it != _initiatorMapping.end(); it++){
      POPString crt = (*it).first;
      //Compare the current POPAppId with the given POPAppId (parameter)
      if(strcmp(crt.GetString(), popappid.GetString()) == 0){
         paroc_accesspoint found = (*it).second;
         return found;
      }
   }
   return foo;
}

/**
 * ViSaG : clementval
 * Insert a new mapping between the POPAppId and the Main PKI
 * @param popapid The POP Application ID that defined the main node
 * @param mainPKI The public key of the node running the main for this POPAppId
 */
void POPCSecurityManager::addMainPKIMapping(POPString popappid, POPString mainPKI){
   //Avoid NULL insertion
   if(popappid.Length() < 0 || mainPKI.Length() < 0)
      return;
   POPString pki = getMainPKIFromMapping(popappid);
   if(strcmp(pki.GetString(), "") == 0){
      _mainPKIMapping.insert(pair<POPString, POPString>(popappid, mainPKI));
      sprintf(log, "ADDMAPPING;POPAPPID;%s;KEY%s", popappid.GetString(), mainPKI.GetString());
      popc_security_log(log);
   }
}

/**
 * ViSaG : clementval
 * Insert a new mapping between the POPAppId and the Main Access Point
 * @param popapid The POP Application ID that defined the main node
 * @param ap The Access Point of the Main
 */
void POPCSecurityManager::addMainAPMapping(POPString popappid, paroc_accesspoint ap){
   //Avoid NULL POPAppID insertion
   if(popappid.Length() < 0 || ap.IsEmpty())
      return;
   paroc_accesspoint _ap = getMainAPFromMapping(popappid);
   if(_ap.IsEmpty()){
      _initiatorMapping.insert(pair<POPString, paroc_accesspoint>(popappid, ap));
      sprintf(log, "[PSM] ADDMAPPING;POPAPPID;%s;NODE;%s", popappid.GetString(), ap.GetAccessString());
      popc_security_log(log);
   }
}

/**
 * ViSaG : clementval
 * Route a PKI to the main node of an application. Use the mapping AP <-> POPAppId to route the message.
 * @param popappid The POPAppId of the application
 * @param pki The public key to route to the main node
 */
void POPCSecurityManager::reroutePKIToMain(POPString popappid, POPString pki){
   popc_security_log("[PSM] REROUTE_PKI_TO_MAIN");
   paroc_accesspoint nextNode_ap = getMainAPFromMapping(popappid);  
   if(nextNode_ap.IsEmpty() || (nextNode_ap==GetAccessPoint())){
      //It's the final destination
      popc_security_log("[PSM] MAPPING_FINAL_WRITE_PKI_TO_LOCAL_PSM");
      POPString noAppId;
      writePKI(noAppId, pki);
   } else {
      //route to next node
      sprintf(log, "[PSM] MAPPING_REROUTE;%s", nextNode_ap.GetAccessString());
      popc_security_log(log);
      POPCSecurityManager nextNode(nextNode_ap);
      nextNode.reroutePKIToMain(popappid, pki);         
   }
}

/**
 * ViSaG : clementval
 * @param wayToNode The way back to the node running the parallel object
 * @param pki The public key of the node having the reference to the parallel object
 */
void POPCSecurityManager::rerouteRef(POPWayback wayToNode, POPString pki, POPString popAppId){
  

   //Set the local public key as the key
   if(strcmp(pki.GetString(), "")==0){
      sprintf(log, "[PSM] REROUTE_FOR_REF:%s", wayToNode.getAsString().GetString());
      popc_security_log(log);
      pki = _localPublicKey;
   }
   
   //If there is no node in the way back, this node is the last node
   if(wayToNode.isEmpty()){
      POPString noAppId;
      writePKI(noAppId, pki);
      sprintf(log, "[PSM] REROUTE_FOR_REF:WRITE_PKI:%s", pki.GetString());
      popc_security_log(log);
   } else {
      POPString nextNode_str = wayToNode.getNextNode();
      sprintf(log, "[PSM] REROUTE_FOR_REF:TO:%s", nextNode_str.GetString());
      popc_security_log(log);
      wayToNode.deleteNextNode();
      paroc_accesspoint nextNode_ap;
      nextNode_ap.SetAccessString(nextNode_str);
      POPCSecurityManager psm(nextNode_ap);
      psm.rerouteRef(wayToNode, pki, popAppId);
   }
}


/**
 * ViSaG : clementval
 * Write log into the Security Manager log file
 * WARNING : use this method only in development
 */
int POPCSecurityManager::popc_security_log(const char *log){
	char *tmp=getenv("POPC_TEMP");
	char logfile[256];
	if (tmp!=NULL) sprintf(logfile,"%s/popc_security_log",tmp);
	else strcpy(logfile, "/tmp/popc_security.log");

	FILE *f=fopen(logfile,"a");
	if (f==NULL) return 1;
	time_t t=time(NULL);
	fprintf(f,"%s", ctime(&t));
	/*va_list ap;
	va_start(ap, log);
	vfprintf(f, log, ap);*/
	fprintf(f,"%s\n",log);
	//va_end(ap);
	fclose(f);
	return 0;
}
