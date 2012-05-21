/**
 * File: popfilebuffer.h
 * Author: Valentin Clement
 * Description: special buffer to run with popfile
 * Creation date: 04.23.2012
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	04.23.2012	Creation of this file
 */

 
#ifndef POPFILEBUFFER_H_INCLUDE
#define POPFILEBUFFER_H_INCLUDE

#include <iostream>
#include <sstream>

#include "paroc_accesspoint.h"
#include "paroc_string.h"

//Forward declaration of POPFileManager interface. It's currently needed as POPCC can't parse .h file. 
class POPFileManager;


namespace popfile {

class POPFileBuffer {
public:
	/** **/
	static const char* POPFILEBUFFER_FULL_WITHOUT_REMAINING;

	POPFileBuffer();
	~POPFileBuffer();	
	
	/**
	 * Used by output operation
	 */
	
	// Add 
	std::string buffer_add(std::string value);

	// Flushing the output buffer into the strip
	void flush();	
	
	


	/**
	 * Used by input operation
	 */

	// Read in the input buffer with a specific size
	std::string buffer_get(long size);
	
	// Read in the input buffer size of offset
	std::string buffer_get_offset();

	// Add data in the input buffer
	void add_data(POPString data);
	
	
	//
	long get_size_input_data();
	
	
	
	// Setter for internal attributes values
	void set_capacity(long value);
	void set_identifier(int value);
	void set_strip_path(std::string value);

	//Setter and Getter for PFM access point
	paroc_accesspoint get_associated_pfm();
	void setAssociatedPOPFileManager(paroc_accesspoint ap);
	void setLocalPOPFileManager(paroc_accesspoint ap);
	
private:
	//string stream buffer for output operation
	std::stringstream popfile_buffer_out;
	
	//string stream buffer for input operation
	std::stringstream popfile_buffer_in;
	
	//Attribute to manage capacity for output operation 
	long capacity;
	long remainingCapacity;
	
	//Unique identifier of the strip
	int identifier;
	
	//Absolute path of the strip associated with this buffer	
	POPString stripPath;
	
	//Access point of the PFM associated with this buffer
	paroc_accesspoint associatedPFM;
	
	//Reference to the remote PFM 
	POPFileManager* pfmref;
	
	//Reference to the local PFM
	POPFileManager* localpfmref;
	
};	
	
	
} // namespace popfile


#endif /* POPFILEBUFFER_H_INCLUDE */
