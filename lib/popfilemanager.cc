/**
 * File : popfilemanager.cc
 * Author : Valentin Clement
 * Description : Implementation of the parallel object POPFileManager. This object is in charge of POPFile management. 
 * Creation date : 2010/11/12
 *
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
#include <string.h>
#include <sys/time.h>
#include <unistd.h>


/**
 * Constructor of the POPFileManager with object description
 * @param challenge	A challenge string to stop the service
 * @param deamon		Boolean flag to set the service as a deamon or not
 * @param host			The url to create the service
 */
POPFileManager::POPFileManager(const POPString &challenge, bool deamon, POPString host) : paroc_service_base(challenge) {
	popfile_log("[POPFILEMANAGER] POPFileManager created.");
	if(deamon) Start();
}

/**
 * Destructor of the POPFileManager
 */
POPFileManager::~POPFileManager(){

}


/**
 * Create a strip file on the local computer
 * @param absolutePath 	The absolute path and filename of the strip file to create
 * @return TRUE if the file was created successfully. FALSE in all others cases.
 */
bool POPFileManager::createStrip(POPString absolutePath)
{
	popfile_log("[POPFILEMANAGER] Creating strip: %s", absolutePath.GetString());
  	std::ofstream strip;
 	strip.open(absolutePath.GetString());
 	if(strip.is_open()){
 		strip.close();
 		popfile_log("[POPFILEMANAGER] Strip created on local storage: %s", absolutePath.GetString());
		return true;	
 	} 
	return false;
}
   
   
/**
 * POPFile: clementval
 * Write data to a local strip
 * @param stringName	absloute path to the strip
 * @param data			Actual data to write to the strip
 */
void POPFileManager::writeToStrip(POPString stringName, POPString data)
{
	struct timeval start1, end1, start2, end2, start3, end3;
	long mtime, seconds, useconds; 
	gettimeofday(&start1, NULL);	
	std::ofstream strip;
  	strip.open (stringName.GetString(), std::ios::out | std::ios::app);
  	if(strip.is_open()){
  		strip << data.GetString();
 		strip.close();
		gettimeofday(&end1, NULL);		
		seconds  = end1.tv_sec  - start1.tv_sec;
   	useconds = end1.tv_usec - start1.tv_usec;
	   mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5; 		
  		popfile_log("[POPFILEMANAGER] Write in strip %d",  mtime);	   
  	} else {
  		popfile_log("[POPFILEMANAGER] Attempt to write data to %s failed", stringName.GetString());
  	}
}

/**
 * POPFile: clementval
 * Call a remote PFM to write to a remote strip
 * @param stringName	absloute path to the strip
 * @param data			Actual data to write to the strip
 * @param ap			Access point of thre remote PFM
 */
void POPFileManager::writeToRemoteStrip(POPString stringName, POPString data, paroc_accesspoint ap)
{
	POPFileManager remote(ap);
	remote.writeToStrip(stringName, data);
}

/**
 * POPFile: clementval
 * Read from a local strip
 * @param stringName	absloute path to the strip
 * @param begin		Size to begin to read
 * @param offset		Site to read
 */
POPString POPFileManager::readFromStrip(POPString stripName, long start, long offset)
{
	//TODO Check to not seek after the end of the strip
	int length=0;
	popfile_log("[POPFILEMANAGER] Opening strip for read operation : %s offset %ld", stripName.GetString(), offset);
	std::ifstream strip;
	strip.open(stripName.GetString(), ios::binary);
	
	strip.seekg (0, ios::end);		// Seek to end
	length = strip.tellg();			// Get length of the strip
	if(start >= length){
		POPString p;
		return p;	
	}
		
	popfile_log("[POPFILEMANAGER] opened size: %d", length);	
	strip.seekg (0, ios::beg);
	popfile_log("[POPFILEMANAGER] seek to begin");
	int crt_pos = strip.tellg();
	popfile_log("[POPFILEMANAGER] crt pos %d", crt_pos);	
	strip.seekg(start, ios::cur);
	popfile_log("[POPFILEMANAGER] seek to start");
	char* buffer;
	buffer = new char[offset+1];
	buffer[offset] = '\0';
	strip.read(buffer, offset);
	popfile_log("[POPFILEMANAGER] read into buffer start");
	strip.close();
	popfile_log("[POPFILEMANAGER] close %d", strlen(buffer));
	POPString data(buffer);
	popfile_log("[POPFILEMANAGER] before return %d", data.Length());
	return data;
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
  			popfile_log("[POPFILEMANAGER] Neighbors is %s", ap.c_str());
  			neighborAP.SetAccessString(ap.c_str());
  			pfm_neighbors.push_back(neighborAP);
  		} else {
  			popfile_log("[POPFILEMANAGER] Could not find port separator");		
  		}
  		found = lstNeighbors.find_first_of(";");
  	}
}

/**
 * TODO use the PSN to perform an intelligent Resource Discovery
 * Find storage resources to store the strips of a new parallel file
 * @param nb 				The number of desired strips
 * @param candidates		An output array that will store the candidates for the strips
 * @param strNames		An output array that will store the real strip names
 * @param stripPrefix	The prefix used to create strip names
 * @return The actual number of strip created
 */
int POPFileManager::findResourcesForStrip(int nb, paroc_accesspoint* candidates, POPString* stripNames, POPString stripPrefix){
	int index=1;
	nb -= 1;
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
   		popfile_log("[POPFILEMANAGER] Strip creation success %d", index);
   		candidates[index] = (*it); 		//store accesspoint of the node on which the strip is created
   		popfile_log("[POPFILEMANAGER] Strip creation success 2");   		
   		stripNames[index] = stripname;	//store the strip name
   		popfile_log("[POPFILEMANAGER] Strip creation success3");   		
   		index++;
	   	popfile_log("[POPFILEMANAGER] Strip created on %s - %s", (*it).GetAccessString(), stripname.GetString());
   	}
   }
	return index; 
}

/**
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


void POPFileManager::asyncCall1(){
	popfile_log("[POPFILEMANAGER] ASYNC CALL 1");
}
	
void POPFileManager::asyncCall2(POPString data){
	popfile_log("[POPFILEMANAGER] ASYNC CALL 2");		
}

void POPFileManager::syncCall1(){
	popfile_log("[POPFILEMANAGER] SYNC CALL 1");
}
	
void POPFileManager::syncCall2(POPString data){
	popfile_log("[POPFILEMANAGER] SYNC CALL 2");		
}

