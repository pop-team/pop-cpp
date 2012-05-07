/**
 * File : popfilereader.ph
 * Author : Valentin Clement
 * Description : Declaration of the asynchronous strip reader of POPFile. 
 * Creation date : 05/04/2012
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	05.04.2012	Creation of this file
 */
 
#ifndef POPFILEREADER_H_INCLUDE
#define POPFILEREADER_H_INCLUDE
 
#include "paroc_accesspoint.h"
#include "popfilebuffer.h"
#include <list>
#include <string.h>

class POPFileManager;

using namespace popfile;

parclass POPFileReader {
public:  

   //POPFileReader constructor
   POPFileReader() @{ od.runLocal(true); };
   
   //POPFileReader destrcutor   
   ~POPFileReader();
   
   
   //Asynchronous read of the strip to further usage
   async conc void read_in_strip(long begin, long end);
   
   //Read in the current buffer
   sync seq POPString read_current_buffer(long length);

   //Save the associated PFM accesspoint
   sync seq void set_pfm_accesspoint(paroc_accesspoint ap);
   
   //Get the associated PFM accesspoint
   sync seq paroc_accesspoint get_pfm_accesspoint();
   
   //Save the associated strip path
   sync seq void set_strip_path(POPString path);
   
   //Get the associated strip path
   sync seq POPString get_strip_path();
   
   classuid(52);
   
private:
	paroc_accesspoint pfm_ap;
	long current_pos;
	POPFileBuffer* popfilebuffer_ref;
	POPFileManager* pfm_ref;
	POPString strip_path;
	
	
};

#endif /* POPFILEREADER_H_INCLUDE */