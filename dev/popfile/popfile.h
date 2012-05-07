/**
 * File: popfile.h
 * Author: Valentin Clement
 * Description: header file for popfile object
 * Creation date: 2012/03/25
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	03.25.2012	Creation of this file
 */

 
#ifndef POPFILE_H_INCLUDE
#define POPFILE_H_INCLUDE

#include <iostream>
#include <fstream>
#include <string.h>

#include "popfile_metadata.h"
#include "popfilebuffer.h"
#include "paroc_accesspoint.h"

class POPFileReader;

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
	
	bool is_open();
	void close();
	void write(const char* s, std::streamsize n);	
	
	
	// New functionalities of POPFile
	
	
	bool is_parallel();
	void get_infos(infos_t* infos);
	
	
	
	//TODO rename open and keep parameters
	bool open(const char* filename, const int stripnumber, const long offset);


	void scatter();
	void gather();
	


	//To simulate << operator
	void write(std::string value);
	
	std::string read();
	void read_in_background();
	std::string get_read();	
	
	template <class T> POPFStream& operator << (const T& ToLog);	
	
	void printInfos();


//	friend std::ostream& operator<<(ostream& out, const std::string& value);	

	
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
	int popfile_stripNumber;
	int popfile_currentBuffer;

	
	
	
	void popfile_writeToBuffer(std::string value);
	
	

		
	std::string popfile_filename;
	std::string popfile_metadata_filename;
	
	POPFileMetaData popfile_metadata;
	
	POPFileBuffer* popfile_writebuffers;
	
	//Internal C++ standard stream
	std::fstream popfile_fstream;	
	
	
	void get_next_buffer();
	
	//AccessPoint to local POPFileManager
	paroc_accesspoint pfm_ap;
	

	
	
	POPFileReader* reader_ref;
	

};	
		
} // namespace popfile


#endif /* POPFILE_H_INCLUDE */
