#include "popfile.h"


using namespace popfile;

const char* POPStream::POPFILE_METADATA_PREFIX = ".popfile_";
const char* POPStream::POPFILE_METADATA_SUFFIX = ".xml";


/**
 * POPStream constructor without parameters.
 */
POPStream::POPStream()
{
	popfile_init_flags();
}

/**
 * POPStream constructor with parameter. The stream will be opened. 
 * @param filename 
 */
POPStream::POPStream(const char* filename)
{
	popfile_init_flags();
	open(filename);
}

/**
 *
 */
POPStream::~POPStream()
{
	
}

/**
 *
 * @return void 
 */
void POPStream::popfile_init_flags()
{
	popfile_parallel = false;
	popfile_open = false;
}

/**
 *
 * @return void 
 */
void POPStream::popfile_init_filename(const char* filename)
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
void POPStream::open(const char* filename)
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
 * 
 */
bool POPStream::popfile_try_open_parallel()
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
		return false;
	}
	return false;
}

/**
 * Check if the file is currently open
 * @return True if the file is open.
 */
bool POPStream::is_open()
{
	if(popfile_parallel){
		return popfile_metadata.is_loaded();
	} else {
		return popfile_fstream.is_open();
	}
} 

/**
 *
 */
bool POPStream::is_parallel()
{
	return popfile_parallel;
} 

/**
 *
 */
void POPStream::get_infos(infos_t* info)
{
	(*info).nb_strips = popfile_metadata.meta_strips.size();
} 


/**
 *
 */
void POPStream::close(){
	if(popfile_parallel){
		popfile_metadata.save();
	} else {
		popfile_fstream.close();
	}
}