/**
 * File : popfilemanager.cc
 * Author : Valentin Clement
 * Description : Implementation of the parallel object POPFileReader. This object is in charge of asynchronous read of strip. 
 * Creation date : 05/04/2012
 * Change Log: 
 * Author		Date			Description
 * clementval	05.04.2012	Creation of this file
 */

#include "popfilereader.ph"


POPFileReader::POPFileReader(const POPString &challenge, bool deamon, POPString host) @{ od.runLocal(true); od.service(true); od.url(host); };
   
   //POPFileReader destrcutor   
POPFileReader::~POPFileReader()
{
	
}
   
   
//Asynchronous read of the strip to further usage
void POPFileReader::read_strip(POPString stripName, long begin, long end)
{
	
}
   

POPString POPFileReader::read_current_buffer()
{
	
}
   
	



//Save the local PFM accesspoint
void POPFileReader::set_pfm_accesspoint(paroc_accesspoint ap)
{

}
   
//Get the local PFM accesspoint
POPFileReader::paroc_accesspoint get_pfm_accesspoint()
{
	
}