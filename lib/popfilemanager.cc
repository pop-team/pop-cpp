/**
 * File : popcloner.cc
 * Author : Valentin Clement
 * Description : Implementation of the parallel object POPCloner (POP-C++ Global Services). This object is responsible of the 
 *               VM cloning.
 * Creation date : 2010/11/12
 * Change Log: 
 * Author		Date			Description
 * clementval	03.25.2012	Creation of this file
 */

#include "popfilemanager.ph"
#include "popc_search_node.ph"

#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdarg.h>


POPFileManager::POPFileManager(const POPString &challenge, bool deamon, POPString host) : paroc_service_base(challenge) {
	popfile_log("[POPFILEMANAGER] POPFileManager created.");

	if(deamon) Start();
}

POPFileManager::~POPFileManager(){

}

bool POPFileManager::createStrip(POPString absolutePath)
{
	popfile_log("[POPFILEMANAGER] Creating strip: %s", absolutePath.GetString());
  	std::ofstream strip;
 	strip.open(absolutePath.GetString());
 	if(strip.is_open()){
 		strip.close();
		return true;	
 	} 
	return false;
}
   
   
/**
 * POPFile: clementval
 * Write data to a strip
 * @param stringName	absloute path to the strip
 * @param data			Actual data to write to the strip
 */
void POPFileManager::writeToStrip(POPString stringName, POPString data)
{
	std::ofstream strip;
  	strip.open (stringName.GetString());
  	if(strip.is_open()){
  		strip << data.GetString();
 		strip.close();
  	} else {
  		popfile_log("[POPFILEMANAGER] Attempt to write data to %s failed", stringName.GetString());
  	}
}

void POPFileManager::writeToRemoteStrip(POPString stringName, POPString data, paroc_accesspoint ap){
	POPFileManager remote(ap);
	remote.writeToStrip(stringName, data);
}

void POPFileManager::asyncCall1(){
	popfile_log("[POPFILEMANAGER] ASYNC CALL 1");
}
	
void POPFileManager::asyncCall2(POPString data){
	popfile_log("[POPFILEMANAGER] ASYNC CALL 2");		
}




/**
 * POPFile: clementval
 * Save the accesspoint of POPSearchNode
 */
void POPFileManager::setPSNAccessPoint(paroc_accesspoint ap)
{
	psn_ap = ap;
}


/**
 * POPFile: clementval
 * Get list of neighbors as a string and create AP
 */
void POPFileManager::getNeighborsFromPSN(){
	POPCSearchNode psn(psn_ap);
	POPString neighborsList = psn.getNeighborsAsString();
	std::string lstNeighbors = neighborsList.GetString();
	std::size_t found;
  	found=lstNeighbors.find_first_of(";");
  	while (found!=std::string::npos){
  		std::string ap = lstNeighbors.substr(0, found);
  		lstNeighbors = lstNeighbors.substr(found+1);
  		std::size_t port_separator;
  		port_separator = ap.find_last_of(":");
  		if(port_separator != std::string::npos){
  			ap = ap.substr(0, port_separator+1);
  			ap.append("2712");
  			paroc_accesspoint neighborAP;
  			neighborAP.SetAccessString(ap.c_str());
  			pfm_neighbors.push_back(neighborAP);
  		} else {
  			popfile_log("[POPFILEMANAGER] Could not find port separator");		
  		}
  		found = lstNeighbors.find_first_of(";");
  	}
}


int POPFileManager::findResourcesForStrip(int nb, paroc_accesspoint* candidates, POPString* stripNames, POPString stripPrefix){
	int index=1;
	std::string str_stripname(stripPrefix.GetString());
	str_stripname.append("_strip");
	popfile_log("[POPFILEMANAGER] Look for %d nodes for strips", nb);
	std::list<paroc_accesspoint>::iterator it;
   for(it = pfm_neighbors.begin(); it != pfm_neighbors.end(); it++){
   	popfile_log("[POPFILEMANAGER] Check creation of strip on %s", (*it).GetAccessString());
   	POPFileManager tmpPfm((*it));
   	std::string strip = str_stripname;
   	std::stringstream intconverter;
   	intconverter << index;
   	strip.append(intconverter.str());
   	POPString stripname(strip.c_str());
   	if(tmpPfm.createStrip(stripname)){
   		candidates[index] = (*it); 		//store accesspoint of the node on which the strip is created
   		stripNames[index] = stripname;	//store the strip name
   		index++;
	   	popfile_log("[POPFILEMANAGER] Strip created on %s - %s", (*it).GetAccessString(), stripname.GetString());
   	}
   }
	return index; 
}






/**
 * ViSaG : clementval
 * Method used to write log
 * @param String with format
 */
int popfile_log(const char *format,...)
{
	char *tmp=getenv("POPC_TEMP");
	char logfile[256];
	if (tmp!=NULL) sprintf(logfile,"%s/popfile_log",tmp);
	else strcpy(logfile, "/tmp/popfile.log");

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
