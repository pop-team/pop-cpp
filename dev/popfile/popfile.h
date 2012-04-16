/**
 * File: popfile.h
 * Author: Valentin Clement
 * Description: header file for popfile object
 * Creation date: 2012/03/25
 * 
 * Modifications: 
 * Authors		Date			Comment
 * clementval		2012/03/25  		Creation of this file
 */
 
#ifndef POPFILE_H_INCLUDE
#define POPFILE_H_INCLUDE

#include <iostream>
#include <fstream>
#include <string.h>

#include "popfile_metadata.h"
#include "paroc_accesspoint.h"


namespace popfile {
	
struct infos_t {
	int nb_strips;
	long offset;
};

class POPFStream {
public:

	// Standard functionalities of stream
	POPFStream();
	POPFStream(const char* filename);
	~POPFStream();	
			
	void open(const char* filename);		
	void close();
	

	
	
	
	// New functionalities of POPFile
	void scatter();
	void gather();	
	bool is_open();
	bool is_parallel();
	void get_infos(infos_t* infos);
	bool create(const char* filename, const int stripnumber, const long offset);
	
	
	void write(const char* s, std::streamsize n);
	
private:


	//Constnat declaration
	static const char* POPFILE_METADATA_PREFIX;
	static const char* POPFILE_METADATA_SUFFIX;
	static const char* POPFILE_POPFILEMANAGER_LOCAL;

	void popfile_init();
	void popfile_init_filename(const char* filename);

	
	
	bool popfile_try_open_parallel();
	bool popfile_parallel;
	bool popfile_open;
	long popfile_offset;
	
	
	
	std::string popfile_filename;
	std::string popfile_metadata_filename;
	
	POPFileMetaData popfile_metadata;
	
	//Internal C++ standard stream
	std::fstream popfile_fstream;	
	
	
	//AccessPoint to local POPFileManager
	paroc_accesspoint pfm_ap;
};	
	
	
} // namespace popfile


#endif
