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

//#include "popfilemanager.ph"
#include "paroc_accesspoint.h"
#include "paroc_string.h"


class POPFileManager;

namespace popfile {

class POPFileBuffer {
public:
	POPFileBuffer();
	~POPFileBuffer();	
	
	std::string buffer_add(std::string value);
	
	void flush();
	void setCapacity(long value);
	void setIdentifier(int value);
	void setStripPath(std::string value);
	void setAssociatedPOPFileManager(paroc_accesspoint ap);
	
private:
	std::stringstream popfile_buffer;
	long capacity;
	long remainingCapacity;
	int identifier;
	POPString stripPath;
	paroc_accesspoint associatedPFM;
	
	POPFileManager* pfmref;
	
};	
	
	
} // namespace popfile


#endif /* POPFILEBUFFER_H_INCLUDE */
