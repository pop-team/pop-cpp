#include "popfile.h"


using namespace popfile;

const char* POPStream::POPFILE_METADATA_PREFIX = ".popfile_";
const char* POPStream::POPFILE_METADATA_SUFFIX = ".xml";


/**
 *
 */
POPStream::POPStream()
{
	popfile_init_flags();
}

/**
 *
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
 */
void POPStream::popfile_init_flags()
{
	popfile_parallel = false;
	popfile_open = false;
}

/**
 *
 */
void POPStream::popfile_init_filename(const char* filename)
{
	popfile_filename = filename;
	popfile_metadata_filename = filename;
	popfile_metadata_filename.insert(0, POPFILE_METADATA_PREFIX);
	popfile_metadata_filename.append(POPFILE_METADATA_SUFFIX);	
}


/**
 *
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
 *
 */
bool POPStream::popfile_try_open_parallel()
{
	popfile_fstream.open(popfile_metadata_filename.c_str());
	if(popfile_fstream.is_open()){
		popfile_fstream.close();
		//load meta data
		bool isLoaded = popfile_metadata.load(popfile_metadata_filename.c_str());
		if(isLoaded){
			std::cout << "Meta-data loaded" << std::endl;
		}
		
      
		return true;
	} else {
		return false;
	}
	return false;
}

/**
 *
 */
bool POPStream::is_open()
{
	if(popfile_parallel){
		
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
		
	} else {
		popfile_fstream.close();
	}
}