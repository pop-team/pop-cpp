/**
 * File: popfile_metadata.h
 * Author: Valentin Clement (clementval)
 * Description: Declaration of the parallel object POPFileManager. This object is in charge of POPFile management. 
 * Creation date: 03.25.2012
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	03.25.2012	Creation of this file 
 * clementval	04.23.2012	Add method to add strip to the metadata
 */
#ifndef POPFILEMETADATA_H_INCLUDE
#define POPFILEMETADATA_H_INCLUDE 
 
#include <string>
#include <sstream>
#include <map>

class MetaDataStrip;

//Define map of strip as a new type
typedef std::map<int, MetaDataStrip> MetaDataStripMap;

/**
 * This class holds basic information on the parallel file
 */
class MetaDataInfo
{
public:
	std::string info_absolute_path;
	std::string info_original_name;
	long info_ending_pointer;			// Define the pointer in the last strip used to write.
	int info_ending_strip;				// Define the last strip used to write. Will be used in the next writing process.
};

/**
 * This class holds value for an access point
 */
class MetaDataAccessPoint
{
public:
	std::string accesspoint_hostname;
	std::string accesspoint_ip_address;
	int accesspoint_port;		
};

/**
 * This class holds all necessary information about a single strip
 */
class MetaDataStrip
{
public:
	bool strip_is_local;
	int strip_identifier;
	std::string strip_absolute_path;
	std::string strip_name;
	long strip_offset;
	MetaDataAccessPoint strip_accesspoint;
};

/**
 * This class holds all information about a whole parallel file
 */
class POPFileMetaData
{
public: 

	static const char* POPFILE_METADATA_COMMENT;
	static const char* POPFILE_METADATA_NODE_ROOT;
	static const char* POPFILE_METADATA_NODE_INFOS;
	static const char* POPFILE_METADATA_NODE_INFOS_ABS_PATH;
	static const char* POPFILE_METADATA_NODE_INFOS_ORGI_NAME;
	static const char* POPFILE_METADATA_NODE_INFOS_END_POINTER;
	static const char* POPFILE_METADATA_NODE_INFOS_END_STRIP;			
	static const char* POPFILE_METADATA_NODE_STRIPS;
	static const char* POPFILE_METADATA_NODE_STRIP;	
	static const char* POPFILE_METADATA_NODE_STRIP_ATTRIBUTE_LOCAL;
	static const char* POPFILE_METADATA_NODE_STRIP_ID;
	static const char* POPFILE_METADATA_NODE_STRIP_ABS_PATH;
	static const char* POPFILE_METADATA_NODE_STRIP_STRIP_NAME;
	static const char* POPFILE_METADATA_NODE_STRIP_OFFSET;	
	static const char* POPFILE_METADATA_NODE_STRIP_AP;
	static const char* POPFILE_METADATA_NODE_STRIP_AP_HOSTNAME;
	static const char* POPFILE_METADATA_NODE_STRIP_AP_IPADDR;
	static const char* POPFILE_METADATA_NODE_STRIP_AP_PORT;
	static const char* POPFILE_METADATA_NULL;
			
	POPFileMetaData();

	bool is_loaded();
	long get_offset();
	void set_offset(long value);	
	std::string get_filename();
	void set_filename(std::string filename, std::string path);
	void set_ending_pointer(long value);
	void set_ending_strip(int index);
	long get_ending_pointer();
	int get_ending_strip();	
		
	void addStripInfo(bool isLocal, int identifier, std::string absolutePath, std::string stripName, long offset, std::string accesspoint);
	
	int get_strips_count();
	
	std::string get_filepath_for_strip(int i);
	std::string get_accessstring_for_strip(int i);
	long get_offset_for_strip(int i);

	MetaDataInfo meta_info;
	MetaDataStripMap meta_strips;
	
	void save(const char* filename);
	bool load(const char* filename);
	
	void dump_to_cout();
	
private:
	std::string popfile_metadata_filename;
	bool meta_loaded;
	long meta_offset;
	
	std::string convertInt(int number);
	std::string convertLong(long number);	
	long convertStringToLong(std::string value);	
	int convertStringToInt(std::string value);
	
};

#endif /* POPFILEMETADATA_H_INCLUDE */