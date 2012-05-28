/**
 * File: popfile.cpp
 * Author: Valentin Clement (clementval)
 * Description: Implementation of popfile object. A popfile object is a parallel file distributed over the nodes available on the network.
 * Creation date: 03.25.2012
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	03.25.2012	Creation of this file
 */

#include "popfile.h"
#include "popfilemanager.ph"
#include "popfilereader.ph"

#include <unistd.h>

using namespace popfile;

// Constant declaration
const char* POPFStream::POPFILE_METADATA_PREFIX = ".popfile_";
const char* POPFStream::POPFILE_METADATA_SUFFIX = ".xml";
const char* POPFStream::POPFILE_POPFILEMANAGER_LOCAL = "socket://127.0.0.1:2712";

const int POPFStream::POPFILE_SCATTER_STRIP_NUMBER = 4;			// 4 strips
const long POPFStream::POPFILE_SCATTER_STRIP_FACTOR = 1024; 	// 1MB Strip factor

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
 * Destructor of the POPFStream object
 */
POPFStream::~POPFStream()
{
	if(is_open()){
		close();
	}	
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
	popfile_current_output_buffer = 0;
	popfile_current_input_buffer = 0;
	popfile_strip_number	= 0;
	pfm_ap.SetAccessString(POPFILE_POPFILEMANAGER_LOCAL);
	popfile_reader_ref = NULL;
	popfile_total_bytes = 0;
	popfile_internal_read_pointer = 0;
	popfile_total_bytes = 0;
	popfile_first_write_pointer = 0;
	popfile_current_reader = 0;
	popfile_current_reader_offset = 0;
	popfile_current_grip = 0;
	popfile_served_grip = 0;
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
 * Check if a file exist
 * @param filename The absolute path of the file
 * @return TRUE if the file exists already, FALSE in any other cases
 */
bool POPFStream::is_file_exist(std::string filename){
	std::ofstream o;
	o.open(filename.c_str());
	if(o.is_open()){
		o.close();
		return true;
	} 
	return false;
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
		cout << "DEBUG 1" << popcendl;
		if(popfile_try_open_parallel()){
			popfile_parallel = true;
		} else {
			popfile_parallel = false;
			popfile_fstream.open(popfile_filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
			if(popfile_fstream.is_open()){
				popfile_open = true;
				popfile_parallel = false;
			}
		} 
	}
}

/**
 * Creation of a new parallel file
 * @param filename the filename in relatrive or absolute path
 * @param stripnumber Number of strip for the file. Default is 2.
 * @param offset Offset to write and read to strip in Kb. Default is 100Kb. Can't be equal or lower than 0.
 * @return TRUE if the creation succeed. FALSE in any other case. Look the log file for more details. 
 */
bool POPFStream::open(const char* filename, const int stripnumber=2, long offset=100, bool local=true){
	
	// Check offset to be greater than 0
	if(offset <= 0) offset = 1;
	
	offset = offset * 1024; // Offset in Kb
	
	//Init special filename for meta data
	popfile_init_filename(filename);

	
	
	/* 
	 * Set strip path. Should set in a different directory as tmp is not persistent. For the moment, the only 
	 * available directory on all nodes 
	 */
	std::string str_filename("/tmp/.");
	str_filename.append(filename);
	std::string stripPrefix = str_filename;
	str_filename.append("_strip0");	
	
	if(!popfile_try_open_parallel()){
		// Create an array of possible popfilemanager accesspoint
		paroc_accesspoint candidates[stripnumber];	
		POPString stripNames[stripnumber];
		// Contact the local PFM to get resources
		POPFileManager pfm(pfm_ap);
		
		// If local flag is TRUE, create a strip on the local node. 
		if(local){
			POPString localStrip(str_filename.c_str());
			if(!pfm.createStrip(localStrip)){
				cout << "[POPFILE] Error: can't create the local strip ... operation failed" << popcendl;
				return false;
			}
			candidates[0] = pfm_ap;
			stripNames[0] = localStrip;
			popfile_strip_number++;	
		}
		
		int resources;		
		POPString pops_stripPrefix = stripPrefix;
		if((resources = pfm.findResourcesForStrip(stripnumber, candidates, stripNames, pops_stripPrefix, local)) != 0){	
			// Set metadata
			std::string metadata_filename(filename);
		
			// Get the current working directory
			char *path=NULL;
			size_t size;
			path=getcwd(path,size);
	
			// Set the meta-data filename and path
			std::string metadata_path(path);
			metadata_path.append("/");	// Add ending slash
			popfile_metadata.set_filename(metadata_filename, metadata_path);
			popfile_metadata.set_offset(offset);
			
			// Procces found resources
			popfile_writebuffers = new POPFileBuffer[resources];	
	
			for(int i = 0; i < stripnumber; i++){
				if(!candidates[i].IsEmpty()){
					std::string strip_path("/tmp/");
					std::string strip_name(stripNames[i].GetString());
					if(i == 0 && local){
						popfile_metadata.addStripInfo(true, i, strip_path, strip_name, offset, candidates[i].GetAccessString());	
					} else{ 
						popfile_metadata.addStripInfo(false, i, strip_path, strip_name, offset, candidates[i].GetAccessString());
						popfile_strip_number++;
					}
					popfile_writebuffers[i].set_capacity(offset);
					popfile_writebuffers[i].set_identifier(i);
					popfile_writebuffers[i].set_strip_path(strip_name);
					popfile_writebuffers[i].setAssociatedPOPFileManager(candidates[i]);
					popfile_writebuffers[i].setLocalPOPFileManager(pfm_ap);
					cout << "[POPFILE-DEBUG] Resource found (" << i << "): " << candidates[i].GetAccessString() << popcendl;					
				}
			}	
		} else {
			cout << "[POPFILE-ERROR] There is not enough resources to create the parallel file" << popcendl;		
			return false;		
		}
	}		
	// Set the current file as prallel file
	popfile_parallel = true;
	return true;
}

/**
 * Try to open the file in parallel mode. Open the file in standard mode if the file is not parallel.
 * @return TRUE if the file could be open in parallel way. FALSE in any other cases.
 */
bool POPFStream::popfile_try_open_parallel()
{
	std::fstream dummystream;
	dummystream.open(popfile_metadata_filename.c_str());
	if(dummystream.is_open()){
		dummystream.close();
		//load meta data
		bool isLoaded = popfile_metadata.load(popfile_metadata_filename.c_str());
		int resources = popfile_metadata.get_strips_count();
		popfile_writebuffers = new POPFileBuffer[resources];

		int i = 0;
		MetaDataStripMap::const_iterator itr;
		for(itr = popfile_metadata.meta_strips.begin(); itr != popfile_metadata.meta_strips.end(); ++itr){
			popfile_writebuffers[i].set_capacity((*itr).second.strip_offset);
			popfile_writebuffers[i].set_identifier((*itr).second.strip_identifier);
			popfile_writebuffers[i].set_strip_path((*itr).second.strip_name);
			paroc_accesspoint ap; ap.SetAccessString(popfile_metadata.get_accessstring_for_strip((*itr).second.strip_identifier).c_str());			
			popfile_writebuffers[i].setAssociatedPOPFileManager(ap);
			popfile_writebuffers[i].setLocalPOPFileManager(pfm_ap);
			popfile_strip_number++;
			i++;
		}
		popfile_offset = popfile_metadata.get_offset_for_strip(0);
		popfile_current_output_buffer = popfile_metadata.get_ending_strip();
		popfile_total_bytes = popfile_metadata.get_ending_pointer();
		popfile_first_write_pointer = popfile_metadata.get_ending_pointer();
		popfile_first_write_pointer = popfile_metadata.get_offset_for_strip(popfile_current_output_buffer) - (popfile_first_write_pointer % popfile_metadata.get_offset_for_strip(popfile_current_output_buffer));
		
		if(isLoaded)
			return true;
		else 
			return false;
	} else {
		
		/* TODO: Look on remote nodes */
		
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
		if(is_open()){
			open(popfile_filename.c_str(), POPFILE_SCATTER_STRIP_NUMBER, POPFILE_SCATTER_STRIP_FACTOR);
			long begin, end, size;
			popfile_fstream.seekg(0, std::ios::beg);			
			begin = popfile_fstream.tellg();
  			popfile_fstream.seekg(0, std::ios::end);
  			end = popfile_fstream.tellg();  			
			size = end-begin;	
						
			long offset = 10000000;
			char* buffer;		
			buffer = new char[offset];
  			popfile_fstream.seekg(0, std::ios::beg); // Set the file pointer at the beginning			
			while(size > offset){
				popfile_fstream.read(buffer, offset);
				size -= offset;
				std::string value(buffer);				
				write(value);
			}
			popfile_fstream.read(buffer, size);
			buffer[size] = '\0';
			write(buffer, size);
			delete [] buffer;
		} else {
			cout << "[POPFILE-ERROR] Can't do this action on a closed file !" << popcendl;	
		}
	} else {
		cout << "[POPFILE-ERROR] Can't do this action on a parallel file !" << popcendl;
		return;
	}
}

/**
 * Get all the strip and write all in a standard file. This action is not meant to be performant
 * @return void
 */
void POPFStream::gather(){
	if(is_parallel()){
		if(is_open()){
			long fullsize = popfile_total_bytes;
			cout << "[POPFILE-DEBUG] (gather) Total bytes to be gather is " << fullsize << popcendl;
			std::ofstream gathered_file;
			gathered_file.open(popfile_filename.c_str());
			while(fullsize > popfile_offset){
				std::string data = read(popfile_offset);
				fullsize -= popfile_offset;
				gathered_file << data;
			} 
			cout << "[POPFILE-DEBUG] (gather) full size " << fullsize << popcendl;
			if(fullsize > 0){
				std::string data = read(fullsize);
				gathered_file << data;
			}
			gathered_file.close();
		} else {
			cout << "[POPFILE-ERROR] (gather) The parallel file is not open !" << popcendl;	
		}
	} else {
		cout << "[POPFILE-ERROR] (gather) Can't do this action on a non-parallel file !" << popcendl;
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
		(*info).strip_factor = popfile_metadata.get_offset();	
	} else {
		cout << "[POPFILE-ERROR] This action is not permitted on a non-parallel file !" << popcendl;
	}
} 


/**
 * Close the POPFile.
 */
void POPFStream::close(){
	if(popfile_parallel){
		cout << "[POPFILE] Closing file" << popcendl;
		//Flush any local data	
		for(int i = 0; i < popfile_strip_number; i++){
			popfile_writebuffers[i].flush();	
		}
		popfile_metadata.set_ending_pointer(popfile_total_bytes);
		popfile_metadata.set_ending_strip(popfile_current_output_buffer);
		//Save the metadat in the XML file
		popfile_metadata.save(popfile_metadata_filename.c_str());
	} else {
		popfile_fstream.close();
	}
}

/**
 * Flush the data still in buffer to the strips
 */
void POPFStream::flush()
{
	//Flush any local data from all buffers
	for(int i = 0; i < popfile_strip_number; i++){
		popfile_writebuffers[i].flush();	
	}
}




/**
 * Write an array of char into the parallel file
 * @param s	A char array
 * @param n	The size of the array
 */
void POPFStream::write(const char* s, std::streamsize n){
	if(popfile_parallel){
		std::string value(s);
		popfile_writeToBuffer(value);
	} else {
		cout << "[POPFILE-ERROR] (write) This action is not implement on a non-parallel file yet !" << popcendl;
	}
}

/**
 * Write a char in the stream
 * @param a	Char value to be written
 * @return void
 */
void POPFStream::write(char a){
	if(popfile_parallel){
		std::stringstream s;
		s << a;
		popfile_writeToBuffer(s.str());
	} else {
		cout << "[POPFILE-ERROR] (write) This action is not implement on a non-parallel file yet !" << popcendl;		
	}
}

/**
 * Write an integer in the stream
 * @param a	Int value to be written
 * @return void
 */
void POPFStream::write(int a)
{
	if(popfile_parallel){
		std::stringstream s;
		s << a;
		popfile_writeToBuffer(s.str());		
	} else {
		cout << "[POPFILE-ERROR] (write) This action is not implement on a non-parallel file yet !" << popcendl;		
	}	
}

/**
 * Write a long in the stream
 * @param a	Long value to be written
 * @return void
 */
void POPFStream::write(long a)
{
	if(popfile_parallel){
		std::stringstream s;
		s << a;
		popfile_writeToBuffer(s.str());
	} else {
		cout << "[POPFILE-ERROR] (write) This action is not implement on a non-parallel file yet !" << popcendl;		
	}
}

/**
 * Write a float in the stream
 * @param a	Float value to be written
 * @return void
 */
void POPFStream::write(float a)
{
	if(popfile_parallel){
		std::stringstream s;
		s << a;
		popfile_writeToBuffer(s.str());
	} else {
		cout << "[POPFILE-ERROR] (write) This action is not implement on a non-parallel file yet !" << popcendl;		
	}
}

/**
 * Write a double in the stream
 * @param a	Double value to be written
 * @return void
 */
void POPFStream::write(double a)
{
	if(popfile_parallel){
		std::stringstream s;
		s << a;
		popfile_writeToBuffer(s.str());
	} else {
		cout << "[POPFILE-ERROR] (write) This action is not implement on a non-parallel file yet !" << popcendl;		
	}	
}

/**
 * Write a string value to the parallel file
 * @param value	The string vakue to write
 */
void POPFStream::write(std::string value){
	if(popfile_parallel){
		popfile_writeToBuffer(value);
	} else {
		popfile_fstream << value.c_str();
	}	
}

/**
 * Read some data from the parallel file
 * @return Data formatted in a string object
 */
std::string POPFStream::read(long size)
{
	POPFileGrip grip = read_in_background(size);
	return get_read(grip);
}

/**
 * Read data from the parallel file in background. Allow to perform other computation during the reading process. 
 * Use the method get_read() when the data is really needed. 
 */
POPFileGrip POPFStream::read_in_background(long size)
{
	if(popfile_parallel){
		//Check if reader is already running
		if(popfile_reader_ref == NULL){
			// Create parallel object for the reading process and store their reference
			popfile_reader_ref = new POPFileReader[popfile_strip_number];
			
			// Add some useful information to the readers
			for(int i = 0; i < popfile_strip_number; i++){
				// Set the associated PFM
				paroc_accesspoint ap;
				ap.SetAccessString(popfile_metadata.get_accessstring_for_strip(i).c_str());
				popfile_reader_ref[i].set_pfm_accesspoint(ap);
				
				// Set the associated path for the strip
				POPString path(popfile_metadata.get_filepath_for_strip(i).c_str());
				popfile_reader_ref[i].set_strip_path(path);
				// Set the offset of the strip
				popfile_reader_ref[i].set_offset(popfile_metadata.get_offset_for_strip(i));
				// Set the idenitifer of the reader
				popfile_reader_ref[i].set_id(i);
			}
		}
		
		// Create the grip 
		POPFileGrip grip;
		grip.set_size(size);										// Define the size of the block top be read
		grip.set_first_reader(popfile_current_reader);	// Set the first reader called in this process
		grip.set_order(popfile_current_grip++);			// Set the order for this grip
		
		if(size >= popfile_offset){
			while (size >= popfile_offset){
				if(popfile_internal_read_pointer != 0){
					grip.set_first_read(popfile_internal_read_pointer);
					cout << "[POPFILE-DEBUG] Read from last pointer =" << popfile_internal_read_pointer << popcendl;
					popfile_reader_ref[popfile_current_reader].read_in_strip(popfile_current_reader_offset, popfile_internal_read_pointer);
					size -= popfile_internal_read_pointer;
					popfile_internal_read_pointer = 0;
				} else {
					popfile_reader_ref[popfile_current_reader].read_in_strip(popfile_current_reader_offset, popfile_offset);
					size -= popfile_offset;
				}
				//cout << "[POPFILE-DEBUG] Read in background size=" << size << popcendl;									
				get_next_reader();				
			}
		}
		if(size > 0){
			popfile_reader_ref[popfile_current_reader].read_in_strip(popfile_current_reader_offset, size);	
			popfile_internal_read_pointer = popfile_offset - size;
			cout << "[POPFILE-DEBUG] Next to be read size=" << popfile_internal_read_pointer << popcendl;
		}
		
		return grip;
	} else {
		cout << "[POPFILE-ERROR] Can't do this action on a non-parallel file!" << popcendl;
		POPFileGrip g;
		return g;
	}			
}

/**
 * Move the reader pointer to the next one
 */
void POPFStream::get_next_reader(){
	popfile_current_reader++;	
	if(popfile_current_reader % popfile_strip_number == 0){
		popfile_current_reader = 0;
		popfile_current_reader_offset += popfile_offset;
	}
	
}

/**
 * Read the parallel file by block of the size of offset. Block is the data is not read yet
 * @return String of offset's size filled with data
 */
std::string POPFStream::get_read(POPFileGrip grip)
{
	std::string data;
	if(grip.get_order() != popfile_served_grip){
		cout << "[POPFILE-WARNING] Reading order is not respected. Reading abort." << popcendl;
		return data;
	}
	
	long size = grip.get_size();
	popfile_current_input_buffer = grip.get_first_reader();
	if(size > popfile_offset){
		while(size > popfile_offset){
			if(grip.get_first_read() != 0){
				data.append(popfile_reader_ref[popfile_current_input_buffer].read_current_buffer(grip.get_first_read()).GetString());
				size -= grip.get_first_read();			
				cout << "[POPFILE-DEBUG] Get Read 1.1 size=" << grip.get_first_read() << "/ buffer="<< popfile_current_input_buffer << popcendl;					
				grip.set_first_read(0);				
			} else {
				data.append(popfile_reader_ref[popfile_current_input_buffer].read_current_buffer(-1).GetString());				
				size -= popfile_offset;		
				cout << "[POPFILE-DEBUG] Get Read 1.2 size=" << popfile_offset << "/ buffer="<< popfile_current_input_buffer << popcendl;							
			}
		
			get_next_input_buffer();	
		}
		if(size > 0){
			cout << "[POPFILE-DEBUG] Get Read 2 size=" << size << "/ buffer="<< popfile_current_input_buffer << popcendl;
			data.append(popfile_reader_ref[popfile_current_input_buffer].read_current_buffer(size).GetString());			
			get_next_input_buffer();
		}
	} else {
		data = popfile_reader_ref[popfile_current_input_buffer].read_current_buffer(size).GetString();
		get_next_input_buffer();
	}
	popfile_served_grip++;
	cout << "[POPFILE-DEBUG] Get Read size end result size=" << data.length() << popcendl;
	return data;
}

/**
 * Print information on the parallel file
 */
void POPFStream::printInfos(){
	popfile_metadata.dump_to_cout();
}


/**
 * Write data in the internal buffers
 * @param value Data to write
 */ 
void POPFStream::popfile_writeToBuffer(std::string value){
	if(popfile_first_write_pointer != 0) {
		popfile_writebuffers[popfile_current_output_buffer].set_capacity(popfile_first_write_pointer);
		popfile_first_write_pointer = 0;
	}
	
	popfile_total_bytes += value.length();
	std::string remaining; 
	remaining = popfile_writebuffers[popfile_current_output_buffer].buffer_add(value);
	while(remaining.length() != 0){
		if(remaining.compare(POPFileBuffer::POPFILEBUFFER_FULL_WITHOUT_REMAINING) == 0){
			popfile_writebuffers[popfile_current_output_buffer].set_capacity(popfile_metadata.get_offset_for_strip(popfile_current_output_buffer));
			get_next_buffer();	
			remaining.erase();	
		} else {
			popfile_writebuffers[popfile_current_output_buffer].set_capacity(popfile_metadata.get_offset_for_strip(popfile_current_output_buffer));			
			get_next_buffer();	
			remaining = popfile_writebuffers[popfile_current_output_buffer].buffer_add(remaining);		
		}	
	}	
}

/**
 * Swicth to the next available buffer. Round robin way.
 */
void POPFStream::get_next_buffer(){
	popfile_current_output_buffer++;
	if(popfile_current_output_buffer%popfile_strip_number == 0){
		popfile_current_output_buffer = 0;	
	}
}


/**
 * Swicth to the next available buffer. Round robin way.
 */
void POPFStream::get_next_input_buffer(){
	popfile_current_input_buffer++;
	if(popfile_current_input_buffer%popfile_strip_number == 0){
		popfile_current_input_buffer = 0;	
	}
}



/**
 * Write a string in the stream
 * @param a	String value to be written
 * @return The current object
 */
POPFStream& POPFStream::operator<< (std::string a)
{
	write(a);
	return *this;	
}

/**
 * Write a char in the stream
 * @param a	Char value to be written
 * @return The current object
 */
POPFStream& POPFStream::operator<< (char a)
{
	write(a);
	return *this;		
}

/**
 * Write a int in the stream
 * @param a	Int value to be written
 * @return The current object
 */
POPFStream& POPFStream::operator<< (int a)
{
	write(a);	
	return *this;	
}

/**
 * Write a long in the stream
 * @param a	Long value to be written
 * @return The current object
 */
POPFStream& POPFStream::operator<< (long a)
{
	write(a);	
	return *this;	
}

/**
 * Write a float in the stream
 * @param a	Float value to be written
 * @return The current object
 */
POPFStream& POPFStream::operator<< (float a)
{
	write(a);	
	return *this;	
}

/**
 * Write a double in the stream
 * @param a	Double value to be written
 * @return The current object
 */
POPFStream& POPFStream::operator<< (double a)
{
	write(a);	
	return *this;	
}