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

#include "popfilemanager.ph"

POPFileManager::POPFileManager(const POPString &challenge, bool deamon, POPString host) : paroc_service_base(challenge) {


	if(deamon) Start();
}

POPFileManager::~POPFileManager(){

}

bool createStrip()
{
}
   
   
/**
 * POPFile: clementval
 * Write data to a strip
 */
void writeToStrip()
{
}




/**
 * POPFile: clementval
 * Save the accesspoint of POPSearchNode
 */
void POPFileManager::setPSNAccessPoint(paroc_accesspoint ap)
{
	psn = ap;
}

