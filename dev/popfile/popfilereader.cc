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
#include "popfilemanager.ph"
#include "popfilebuffer.h"

//
POPFileReader::POPFileReader()
{
	cout << "[POPFILEREADER] Created on " << POPGetHost() << popcendl;	
	popfilebuffer_ref = new POPFileBuffer();
}
   
//POPFileReader destructor   
POPFileReader::~POPFileReader()
{

}
   
//Asynchronous read of the strip to further usage
void POPFileReader::read_in_strip(long start, long offset)
{	
	cout << "[POPFILEREADER] Read in strip " << strip_path.GetString() << " from:" << start << " to:" << start+offset << popcendl;	
	POPString data = pfm_ref->readFromStrip(strip_path, start, offset);
	cout << "[POPFILEREADER] Read from strip" << strlen(data.GetString()) << popcendl;	
	popfilebuffer_ref->add_data(data);
}

POPString POPFileReader::read_current_buffer(long size)
{
	POPString data;
	if(size != -1)
		data = popfilebuffer_ref->buffer_get(size).c_str();
	else 
		data = popfilebuffer_ref->buffer_get_offset().c_str();
	cout << "[POPFILEREADER] Sent data size" << strlen(data.GetString()) << popcendl;	
	return data;
}

void POPFileReader::set_offset(long offset)
{
	pfr_offset = offset;
	popfilebuffer_ref->set_capacity(pfr_offset);
}
   
//Save the local PFM accesspoint
void POPFileReader::set_pfm_accesspoint(paroc_accesspoint ap)
{
	pfm_ap = ap;
	pfm_ref = new POPFileManager(pfm_ap);
}
   
/**
 * Get the local PFM accesspoint
 * @return 
 */
paroc_accesspoint POPFileReader::get_pfm_accesspoint()
{
	return pfm_ap;
}

/** 
 * Save the associated strip path
 * @param path The absolute strip file path associated with this reader
 */
void POPFileReader::set_strip_path(POPString path)
{
	strip_path = path;
}
   
/**
 * Get the associated strip path
 * @return the absolute strip file path associated with this reader
 */
POPString POPFileReader::get_strip_path()
{
	return strip_path;
}

@pack(POPFileReader);