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
#include "popfile_grip.h"
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
	
	// popfile destrcutor
	~POPFStream();	
			
	// Open a file 
	void open(const char* filename);		
	
	// Check if the file is open
	bool is_open();
	
	// Close the current file
	void close();
	
	// Write char data in the file
	void write(const char* s, std::streamsize n);	
	
	// Write string data in the file
	void write(std::string value);
	
	// Read string data from the file
	std::string read(long size);
	
	/** popfile special functionnalities **/
	
	// Tell if the current file is parallel or not
	bool is_parallel();
	
	// Get a struct conataining internal information about the popfile 
	void get_infos(infos_t* infos);
	
	// Open a file and create it if it doesn't exists
	bool open(const char* filename, const int stripnumber, const long striping_factor);

	// Scatter a standard file into a parallel file
	void scatter();
	
	// Gather a parallel file into a standard file
	void gather();

	// Call read in background	
	POPFileGrip read_in_background(long size);
	
	// Get data read by the read in background call
	std::string get_read(POPFileGrip grip);	

	/** popfile operators **/	
	
	// 
	template <class T> POPFStream& operator << (const T& toWrite);	
	
	// Print meta data information to stdout
	void printInfos();
	


private:
	/** Private constants of popfile **/
	static const char* POPFILE_METADATA_PREFIX;
	static const char* POPFILE_METADATA_SUFFIX;
	static const char* POPFILE_POPFILEMANAGER_LOCAL;


	/** Private attributes of popfile **/
	
	// Flag telling if the current opened file is parallel or not
	bool popfile_parallel;
	
	// Flag telling if the popfile is open or not
	bool popfile_open;
	
	// Offset used for the writing and reading process in the popfile
	long popfile_offset;
	
	// Number of strip in the popfile
	int popfile_strip_number;
	
	// Index of the current popfile output buffer
	int popfile_current_output_buffer;
	
	// Index of the current popfile input buffer
	int popfile_current_input_buffer;
	
	// string representing the name of the original file 
	std::string popfile_filename;
	
	// String represnting the name of the meta data file
	std::string popfile_metadata_filename;
	
	// Object storing the meta data of the popfile	
	POPFileMetaData popfile_metadata;
	
	//Array of buffers 
	POPFileBuffer* popfile_writebuffers;
	
	//Internal C++ standard stream
	std::fstream popfile_fstream;		
	
	//AccessPoint to local POPFileManager
	paroc_accesspoint pfm_ap;
	
	// References to parallel objects POPFile readers 
	POPFileReader* popfile_reader_ref;
	
	// Value pointing to the next byte to be read
	long popfile_internal_read_pointer;
	
	// Value represnting the total number of byte in a popfile
	long popfile_total_bytes;
	
	// Value represnting the number of bytes to be added when opening an old strip
	long popfile_first_write_pointer;
	
	// Value representing the current reader to be called
	int popfile_current_reader;
	
	//
	int popfile_current_reader_offset;
	
	


	/** Private methods of popfile **/

	//	Initialize internal attribute of a popfile
	void popfile_init();
	
	// Initialize internal filename used in popfile
	void popfile_init_filename(const char* filename);
	
	// Try to open the file in parallel way. If fails opens it in normal way.	
	bool popfile_try_open_parallel();
	
	// Write value into the buffer
	void popfile_writeToBuffer(std::string value);
	
	// Move the buffer pointer to the next buffer
	void get_next_buffer();	
	
	void get_next_input_buffer();	
	
	// Move the reader pointer to the next reader
	void get_next_reader();
	
	// Check if a file exist
	bool is_file_exist(std::string filename);
	
};	
		
} // namespace popfile


#endif /* POPFILE_H_INCLUDE */
