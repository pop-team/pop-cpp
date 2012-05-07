/**
 * File: popfile.cpp
 * Author: Valentin Clement
 * Description: Implementation of popfile object. A popfile object is a parallel file distributed over the nodes available on the network.
 * Creation date: 2012/03/25
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	03.25.2012	Creation of this file
 */

#include "popfile.h"
#include "popfile_datathread.h"
#include "popfilemanager.ph"
#include "popfilereader.ph"

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
	popfile_currentBuffer = 0;
	popfile_stripNumber	= 0;
	pfm_ap.SetAccessString(POPFILE_POPFILEMANAGER_LOCAL);
	reader_ref = NULL;
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
	cout << "[POPFILE-DEBUG] Init metadata filename:" << popfile_metadata_filename << popcendl;	
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
		cout << "[POPFILE-ERROR] Can't do this action on a parallel file!" << popcendl;
		return;
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
		cout << "[POPFILE-ERROR] Can't do this action on a non-parallel file!" << popcendl;
		return;
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
		cout << "[POPFILE] Closing file" << popcendl;
		//Flush any local data	
		for(int i = 0; i < popfile_stripNumber; i++){
			popfile_writebuffers[i].flush();	
		}
		//Save the metadat in the XML file
		popfile_metadata.save(popfile_metadata_filename.c_str());
	} else {
		popfile_fstream.close();
	}
}

/**
 * Creation of a new parallel file
 * @param filename the filename in relatrive or absolute path
 * @param stripnumber Number of strip for the file. Default is 2.
 * @param offset Offset to write and read to strip. Default is 1024.
 * @return TRUE if the creation succeed. FALSE in any other case. Look the log file for more details. 
 */
bool POPFStream::open(const char* filename, const int stripnumber=2, const long offset=1024){
	//Init special filename for meta data
	popfile_init_filename(filename);

	std::string str_filename("/tmp/.");
	str_filename.append(filename);
	std::string stripPrefix = str_filename;
	str_filename.append("_strip0");	


	//TODO avoid create parallel file for already created parallel file. 


	//Get path and filename to create the file
	/*popfile_metadata.set_offset(offset);
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
	
	cout << "[POPFILE] File will be create: name: " << str_filename << " path: " << path << popcendl;*/
	
	
	//Create an array of possible popfilemanager accesspoint
	paroc_accesspoint candidates[stripnumber];	
	POPString stripNames[stripnumber];
	//Contact the local PFM to get resources
	POPFileManager pfm(pfm_ap);
	POPString localStrip(str_filename.c_str());
	if(!pfm.createStrip(localStrip)){
		cout << "[POPFILE] Error: can't create the local strip ... operation failed" << popcendl;
		return false;
	}
	candidates[0] = pfm_ap;
	stripNames[0] = localStrip;
	popfile_stripNumber++;
	int resources;
	POPString pops_stripPrefix = stripPrefix;
	if((resources = pfm.findResourcesForStrip(stripnumber-1, candidates, stripNames, pops_stripPrefix)) != 0){
		//Set metadata
		std::string metadata_filename(filename);
		std::string metadata_path("/Users/clementval/versioning/popc/popfile_popc2.0.1/dev/popfile/");
		popfile_metadata.set_filename(metadata_filename, metadata_path);
		popfile_metadata.set_offset(offset);
		
		//Procces found resources
		popfile_writebuffers = new POPFileBuffer[resources];	

		for(int i = 0; i < resources; i++){
			if(!candidates[i].IsEmpty()){
				std::string strip_path("/tmp/");
				std::string strip_name(stripNames[i].GetString());
				if(i == 0){
					popfile_metadata.addStripInfo(true, i, strip_path, strip_name, offset, candidates[i].GetAccessString());	
				} else{ 
					popfile_metadata.addStripInfo(false, i, strip_path, strip_name, offset, candidates[i].GetAccessString());
					popfile_stripNumber++;
				}
				popfile_writebuffers[i].set_capacity(offset);
				popfile_writebuffers[i].set_identifier(i);
				popfile_writebuffers[i].set_strip_path(strip_name);
				popfile_writebuffers[i].setAssociatedPOPFileManager(candidates[i]);
				popfile_writebuffers[i].setLocalPOPFileManager(pfm_ap);
				cout << "[POPFILE] Resource found (" << i << "): " << candidates[i].GetAccessString() << popcendl;					
			}
		}	
	} else {
		cout << "[POPFILE] Error: there is not enough resources to create the parallel file" << popcendl;		
		return false;		
	}


		
	// Set the current file as prallel file
	popfile_parallel = true;
	return true;
}



void POPFStream::write(const char* s, std::streamsize n){
	if(popfile_parallel){
//		cout << "[POPFILE] Call to write(char*)" << popcendl;
		std::string value(s);
		popfile_writeToBuffer(s);
	} else {
		//TODO
	}
}

void POPFStream::write(std::string value){
	if(popfile_parallel){
		//cout << "[POPFILE] Call to write(string)" << popcendl;
		popfile_writeToBuffer(value);
	} else {
		//TODO
	}	
}

std::string POPFStream::read()
{
	
}

void POPFStream::read_in_background()
{
	if(popfile_parallel){
		//Check if reader is already running
		if(reader_ref == NULL){
			reader_ref = new POPFileReader[popfile_stripNumber];
			for(int i = 0; i < popfile_stripNumber; i++){
				paroc_accesspoint ap;
				ap.SetAccessString(popfile_metadata.get_accessstring_for_strip(i).c_str());
				//cout << "[POPFSTREAM] Set ap to reader " << popfile_metadata.get_accessstring_for_strip(i) << popcendl;
				reader_ref[i].set_pfm_accesspoint(ap);
				//cout << "[POPFSTREAM] Set path to reader " << popfile_metadata.get_filepath_for_strip(i) << popcendl;
				POPString path(popfile_metadata.get_filepath_for_strip(i).c_str());
				reader_ref[i].set_strip_path(path);
			}
		}
		for(int i = 0; i < popfile_stripNumber; i++){
			//reader_ref[i].read_in_strip(0, 100000);
		}
	} else {
		cout << "[POPFILE-ERROR] Can't do this action on a non-parallel file!" << popcendl;
	}			
}

std::string get_read()
{
	
}

void POPFStream::printInfos(){
	popfile_metadata.dump_to_cout();
}


void POPFStream::popfile_writeToBuffer(std::string value){
	std::string remaining; 
	remaining = popfile_writebuffers[popfile_currentBuffer].buffer_add(value);
//	cout << "[POPFILEBUFFER] Remaining = " << remaining << popcendl;
	while(remaining.length() != 0){
//		cout << "[POPFILEBUFFER] process remaining = " << remaining << popcendl;
		get_next_buffer();	
		remaining = popfile_writebuffers[popfile_currentBuffer].buffer_add(remaining);	
	}	
}


/**
 *
 */
void POPFStream::get_next_buffer(){
	popfile_currentBuffer++;
	if(popfile_currentBuffer%popfile_stripNumber == 0)
		popfile_currentBuffer = 0;	
}



/* implementing operators */
template <class T> POPFStream& POPFStream::operator << (const T& ToLog)
{
	cout <<  "Call to << " << popcendl;   
   return this;
}	