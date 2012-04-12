/**
 * File : popfilemanager.cc
 * Author : Valentin Clement
 * Description : Implementation of the parallel object POPFileManager (POP-C++ Global Services). This object is responsible of the 
 *               parallel file management.
 * Creation date : 2012/04/06
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2012/04/06  Creation of this file
 */

#include "popfilemanager.ph"
#include <iostream>

/**
 * POPFile : clementval
 * Constrcutor of the POPFileManager
 * @param challenge  Challenge string needed to stop the service
 * @param deamon     Tell if the parallel object is a deamon or not 
 */
POPFileManager::POPFileManager(const POPString &challenge, bool deamon) : paroc_service_base(challenge) 
{
	
	if(deamon) Start();
}

/**
 * POPFile : clementval
 * Destructor of the POPCloner
 */
POPFileManager::~POPFileManager()
{

}

/**
 * POPFile : clementval
 * Destructor of the POPCloner
 */
void POPFileManager::getMetaData()
{
	
}


/**
 * POPFile : clementval
 * Check if the node host a specific strip of a file
 * @param path the absolute path of the strip
 * @return TRUE if the strip is hosted on this node, false in other way
 */
bool POPFileManager::hasStrip(POPString path)
{
	/*std::ifstream local_strip;
	local_strip(path.GetString());
	if(local_strip.is_open()){
		local_strip.close();
		return true;
	} else {
		return false;
	}*/
	return false;
}


@pack(POPFileManager);

