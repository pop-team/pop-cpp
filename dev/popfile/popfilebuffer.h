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
	POPFileBuffer();
	~POPFileBuffer();	
	
	std::string buffer_add(std::string value);
	std::string buffer_get(long size);
	
	void add_data(POPString data);
	
	
	void flush();
	void set_capacity(long value);
	void set_identifier(int value);
	void set_strip_path(std::string value);
	void setAssociatedPOPFileManager(paroc_accesspoint ap);
	paroc_accesspoint get_associated_pfm();
	void setLocalPOPFileManager(paroc_accesspoint ap);
	
private:
	std::stringstream popfile_buffer_out;
	std::stringstream popfile_buffer_in;
	long capacity;
	long remainingCapacity;
	int identifier;
	
	
	POPString stripPath;
	paroc_accesspoint associatedPFM;
	
	POPFileManager* pfmref;
	
	POPFileManager* localpfmref;
	
};	
	
	
} // namespace popfile


#endif /* POPFILEBUFFER_H_INCLUDE */
