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


#include "paroc_accesspoint.h"


parclass POPFileReader {
public:  

   //POPFileReader constructor
   POPFileReader() @{ od.runLocal(true); };
   
   //POPFileReader destrcutor   
   ~POPFileReader();
   
   
   //Asynchronous read of the strip to further usage
   async seq void read_strip(POPString stripName, long begin, long end);
   
   //
   sync seq POPString read_current_buffer();
   
	



   //Save the local PFM accesspoint
   sync seq void set_pfm_accesspoint(paroc_accesspoint ap);
   
   //Get the local PFM accesspoint
   sync seq paroc_accesspoint get_pfm_accesspoint();
   
   
   classuid(52);
private:
	paroc_accesspoint pfm_ap;
	
};