/**
 *
 */
 
 
#include <string>
#include <map>

class MetaDataStrip;

//Define map of strip as a new type
typedef std::map<std::string, MetaDataStrip> MetaDataStripMap;

/**
 *
 */
class MetaDataInfo
{
public:
	std::string info_absloute_path;
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

	static const char* POPFILE_METADATA_NODE_INFOS;
	static const char* POPFILE_METADATA_NODE_STRIPS;
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

	MetaDataInfo meta_info;
	MetaDataStripMap meta_strips;
	
	void save();
	bool load(const char* filename);
	
	void dump_to_cout();
	
private:
	std::string popfile_metadata_filename;
	bool meta_loaded;
};

