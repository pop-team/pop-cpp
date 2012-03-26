/**
 *
 */
#ifndef POPFILE_H_INCLUDE
#define POPFILE_H_INCLUDE

#include <iostream>
#include <fstream>
#include <string.h>

#include "popfile_metadata.h"

namespace popfile{
	
struct infos_t {
	int nb_strips;
};

class POPStream {
public:
	POPStream();
	POPStream(const char* filename);
	~POPStream();	
			
	void open(const char* filename);		
	void close();
	
	
	bool is_open();
	bool is_parallel();
	void get_infos(infos_t* infos);
	
private:



	static const char* POPFILE_METADATA_PREFIX;
	static const char* POPFILE_METADATA_SUFFIX;

	void popfile_init_flags();
	void popfile_init_filename(const char* filename);

	
	
	bool popfile_try_open_parallel();
	bool popfile_parallel;
	bool popfile_open;
	
	
	
	std::string popfile_filename;
	std::string popfile_metadata_filename;
	
	POPFileMetaData popfile_metadata;
	
	//Internal C++ standard stream
	std::fstream popfile_fstream;	
};	
	
	
} // namespace popfile


#endif
