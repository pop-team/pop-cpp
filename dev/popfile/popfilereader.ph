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
#include <fcntl.h>
#include <semaphore.h>

class POPFileManager;

using namespace popfile;

parclass POPFileReader {
public:  


   // POPFileReader constructor
   POPFileReader() @{ od.runLocal(true); };
   
   // POPFileReader destrcutor   
   ~POPFileReader();
   
   // Asynchronous read of the strip to further usage
   async seq void read_in_strip(long start, long offset);
   
   // Read in the current buffer
   sync seq POPString read_current_buffer(long length);

	// Set the offset of the associated strip
	sync seq void set_offset(long offset);

   // Save the associated PFM accesspoint
   sync seq void set_pfm_accesspoint(paroc_accesspoint ap);
   
   // Get the associated PFM accesspoint
   sync seq paroc_accesspoint get_pfm_accesspoint();
   
   // Save the associated strip path
   sync seq void set_strip_path(POPString path);
   
   // Get the associated strip path
   sync seq POPString get_strip_path();
   
   // Set the identifier of this POPFileReader
   sync seq void set_id(int value);
   
   // Definition if the class uid
   classuid(52);
   
private:
	sem_t *pt_read_locker;					// Semaphor used to wait for data in the read process. 
	paroc_accesspoint pfm_ap;				// Access point of the POPFileManager
	long current_pos;							// Current position in the internal buffer
	long pfr_offset;							// Strip factor used by the POPFStream
	POPFileBuffer* popfilebuffer_ref;	// Reference to the internal buffer
	POPFileManager* pfm_ref;				// Reference to the POPFileManager
	POPString strip_path;					// Path to the associated strip
	int identifier; 							// Unique identifier of this POPFileManager in the POPFStream
	std::string reader_semname;			// Name of the semaphor
	
	
};

#endif /* POPFILEREADER_H_INCLUDE */