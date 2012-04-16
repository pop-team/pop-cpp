/**
 * File: popfile.cpp
 * Author: Valentin Clement
 * Description: Implementation of popfile object. A popfile object is a parallel file distributed over the nodes available on the network.
 * Creation date: 2012/03/25
 * 
 * Modifications: 
 * Authors		Date			Comment
 * clementval		2012/03/25  		Creation of this file
 */

#include "popfile.h"
#include "popfile_datathread.h"
#include "popfilemanager.ph"
#include <unistd.h>


using namespace popfile;

// Constant declaration
const char* POPFStream::POPFILE_METADATA_PREFIX = ".popfile_";
const char* POPFStream::POPFILE_METADATA_SUFFIX = ".xml";
const char* POPFStream::POPFILE_POPFILEMANAGER_LOCAL = "socket://127.0.0.1:2712";


/**
 * POPFStream constructor without parameters.
 */
POPFStream::POPFStream()
{	
	//Initialite internal values
	popfile_init();
}

/**
 * POPFStream constructor with parameter. The stream will be opened. 
 * @param filename 
 */
POPFStream::POPFStream(const char* filename)
{
	//Initialize internal values
	popfile_init();
	POPFileManager pfm(pfm_ap);
	cout << "[POPFILEMANAGER] POPFileManger is connected to: " << pfm.GetAccessPoint().GetAccessString() << popcendl;
	if(pfm.createStrip()){
		cout << "[POPFILEMANAGER] Call to POPFileManager succeed" << popcendl;	
	}
	
	//Try to open the file
	open(filename);
}

/**
 *
 */
POPFStream::~POPFStream()
{
	//TODO
}

/**
 * Initialize the internal flag used in a POPFile object
 * @return void 
 */
void POPFStream::popfile_init()
{
	popfile_parallel = false;
	popfile_open = false;
	popfile_offset = 0;
	pfm_ap.SetAccessString(POPFILE_POPFILEMANAGER_LOCAL);
}

/**
 * Initialize the name of different files used by a POPFile object
 * @return void 
 */
void POPFStream::popfile_init_filename(const char* filename)
{
	popfile_filename = filename;
	popfile_metadata_filename = filename;
	popfile_metadata_filename.insert(0, POPFILE_METADATA_PREFIX);
	popfile_metadata_filename.append(POPFILE_METADATA_SUFFIX);	
}


/**
 * Open the file linked with the given path.
 * @param filename
 * @return void
 */
void POPFStream::open(const char* filename)
{
	if(!popfile_open){
		popfile_init_filename(filename);
		if(popfile_try_open_parallel()){
			popfile_parallel = true;
		} else {
			popfile_parallel = false;
			popfile_fstream.open(popfile_filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
			if(popfile_fstream.is_open()){
				popfile_open = true;
			}
		} 
	}
}

/**
 * Try to open the file in parallel mode. Open the file in standard mode if the file is not parallel.
 * @return TRUE if the file could be open in parallel way. FALSE in any other cases.
 */
bool POPFStream::popfile_try_open_parallel()
{
	popfile_fstream.open(popfile_metadata_filename.c_str());
	if(popfile_fstream.is_open()){
		popfile_fstream.close();
		//load meta data
		bool isLoaded = popfile_metadata.load(popfile_metadata_filename.c_str());
		if(isLoaded)
			return true;
		else 
			return false;
	} else {
		//TODO look for remote file
		return false;
	}
	return false;
}


/**
 * Strip a standard file into a parallel file
 * @return void
 */
void POPFStream::scatter(){
	if(!popfile_parallel){
		//TODO
	} else {
		//Can't do it ... already parallel
		//TODO throw exception
	}
}

/**
 * Get all the strip and write all in a standard file
 * @return void
 */
void POPFStream::gather(){
	if(popfile_parallel){
		//TODO
		
	} else {
		//Can't do it, not parallel
		//TODO throw exception
	}
}


/**
 * Check if the file is currently open
 * @return True if the file is open
 */
bool POPFStream::is_open()
{
	if(popfile_parallel)
		return popfile_metadata.is_loaded();
	else
		return popfile_fstream.is_open();
} 

/**
 * Check if the file is parallel
 * @return True if the file is parallel
 */
bool POPFStream::is_parallel()
{
	return popfile_parallel;
} 

/**
 * Get information about the parallel file.
 */
void POPFStream::get_infos(infos_t* info)
{
	if(popfile_parallel){
		(*info).nb_strips = popfile_metadata.meta_strips.size();
		(*info).offset = popfile_metadata.get_offset();	
	} else {
		//TODO
	}
} 


/**
 * Close the POPFile.
 */
void POPFStream::close(){
	if(popfile_parallel){
		//Flush any local data
		//TODO
		//Save the metadat in the XML file
		popfile_metadata.save(popfile_metadata_filename.c_str());
	} else {
		popfile_fstream.close();
	}
}

bool POPFStream::create(const char* filename, const int stripnumber=2, const long offset=1024){

	//Get path and filename to create the file
	popfile_metadata.set_offset(offset);
	std::string str_filename(filename);	
	std::string path;
  	std::size_t found;
	found=str_filename.find_first_of("/");
	if(found == std::string::npos){
		char * pPath;
		pPath = getenv("PWD");
		if (pPath!=NULL){
			cout << "GET CURRENT WORKING DIRECTORY" << (*pPath) << popcendl;
			path = (*pPath);
		} else {
			cout << "CURRENT WORKING DIRECTORY IS NULL" << popcendl;	
		}		
	} else {
		found = str_filename.find_last_of("/");
		if(found==std::string::npos)
			return false;
		path = str_filename.substr(0, found);
		str_filename = str_filename.substr(found+1);
	}
	popfile_metadata.set_filename(str_filename, path);
	
	cout << "[POPFILE] File will be create: name: " << str_filename << " path: " << path << popcendl;
	
	
	
}



void POPFStream::write(const char* s, std::streamsize n){
	if(popfile_parallel){
		
	} else {
		//TODO
	}
}
