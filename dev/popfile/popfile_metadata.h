/**
 * PROJECT:		POPFile
 * AUTHOR:		clementval
 *	FILENAME:	popfile_metadata.h
 * CREATION:	03.25.2012
 * 
 * Change Log
 * ----------
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
 *
 */
class MetaDataInfo
{
public:
	std::string info_absolute_path;
	std::string info_original_name;
};

/**
 *
 */
class MetaDataAccessPoint
{
public:
	std::string accesspoint_hostname;
	std::string accesspoint_ip_address;
	int accesspoint_port;		
};

/**
 *
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
 *
 */
class POPFileMetaData
{
public: 

	static const char* POPFILE_METADATA_COMMENT;
	static const char* POPFILE_METADATA_NODE_ROOT;
	static const char* POPFILE_METADATA_NODE_INFOS;
	static const char* POPFILE_METADATA_NODE_INFOS_ABS_PATH;
	static const char* POPFILE_METADATA_NODE_INFOS_ORGI_NAME;	
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
			
	POPFileMetaData();

	bool is_loaded();
	long get_offset();
	void set_offset(long value);	
	std::string get_filename();
	void set_filename(std::string filename, std::string path);
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
	int convertStringToInt(std::string value);
	
};

#endif /* POPFILEMETADATA_H_INCLUDE */