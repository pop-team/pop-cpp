#include "tinyxml/tinyxml.h"
#include "popfile_metadata.h"


const char* POPFileMetaData::POPFILE_METADATA_NODE_INFOS = "infos";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIPS = "strips";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_ATTRIBUTE_LOCAL = "local";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_ID = "id";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_ABS_PATH = "absolute-path";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_STRIP_NAME = "strip-name";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_OFFSET = "offset";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_AP = "accesspoint";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_AP_HOSTNAME = "hostname";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_AP_IPADDR = "ip-address";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP_AP_PORT = "port";

POPFileMetaData::POPFileMetaData()
{
	
}

/**
 * Save data to file
 */
void POPFileMetaData::save()
{
	meta_strips.clear();
}


/**
 * Load the value of XML in the objects
 */
bool POPFileMetaData::load(const char* filename)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile()) return false;

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	
	pElem=hDoc.FirstChildElement().Element();
	if(!pElem) return false;
	
	//Save the root
	hRoot=TiXmlHandle(pElem);
	
	//Getting values of infos node
	pElem = hRoot.FirstChild(POPFILE_METADATA_NODE_INFOS).FirstChild().Element();
	meta_info.info_absloute_path = pElem->GetText();
	pElem = pElem->NextSiblingElement();
	meta_info.info_original_name = pElem->GetText();
	
	//Getting values of strips node
	meta_strips.clear();
	pElem = hRoot.FirstChild(POPFILE_METADATA_NODE_STRIPS).FirstChild().Element();
	for (pElem; pElem; pElem=pElem->NextSiblingElement()){
		//Create ojbect strip to store information of the metadata
		MetaDataStrip strip;
		//Get the attribute local
		pElem->QueryBoolAttribute(POPFILE_METADATA_NODE_STRIP_ATTRIBUTE_LOCAL, &strip.strip_is_local);
		
		//Save the current node
		TiXmlHandle crtNode(0);
		crtNode = TiXmlHandle(pElem);
		TiXmlElement* node;
		
		//Read id node
		node = crtNode.FirstChild(POPFILE_METADATA_NODE_STRIP_ID).Element();
		strip.strip_identifier = atoi(node->GetText());
		
		//Read asbolute-path node
		node = crtNode.FirstChild(POPFILE_METADATA_NODE_STRIP_ABS_PATH).Element();
		strip.strip_absolute_path = node->GetText();		
		
		//Read strip-name node
		node = crtNode.FirstChild(POPFILE_METADATA_NODE_STRIP_STRIP_NAME).Element();
		strip.strip_name = node->GetText();		

		//Read offset node
		node = crtNode.FirstChild(POPFILE_METADATA_NODE_STRIP_OFFSET).Element();
		strip.strip_offset = atol(node->GetText());		

		//Read accesspoint node
		node = crtNode.FirstChild(POPFILE_METADATA_NODE_STRIP_AP).Element();
		crtNode = TiXmlHandle(node);

		node = crtNode.FirstChild(POPFILE_METADATA_NODE_STRIP_AP_HOSTNAME).Element();
		strip.strip_accesspoint.accesspoint_hostname = node->GetText();

		node = crtNode.FirstChild(POPFILE_METADATA_NODE_STRIP_AP_IPADDR).Element();
		strip.strip_accesspoint.accesspoint_ip_address = node->GetText();

		node = crtNode.FirstChild(POPFILE_METADATA_NODE_STRIP_AP_PORT).Element();
		strip.strip_accesspoint.accesspoint_port = atoi(node->GetText());
		
		//Insert the strip in the map
		meta_strips[strip.strip_name] = strip;
	}
	return true;
}

/** 
 * Print data to cout
 */
void POPFileMetaData::dump_to_cout(){
	std::cout << "### POPFileMetaData ###" << std::endl;
	std::cout << "- Infos :" << std::endl;	
	std::cout << "-- Absolute Path: " << meta_info.info_absloute_path << std::endl;	
	std::cout << "-- Original Filename: " << meta_info.info_original_name << std::endl;
	std::cout << "- Strips: " << std::endl;	
	
	MetaDataStripMap::const_iterator itr;
	for(itr = meta_strips.begin(); itr != meta_strips.end(); ++itr){
		std::cout << "-- Strip: (local) - " << (*itr).second.strip_is_local << std::endl;
		std::cout << "--- Identifier: " << (*itr).second.strip_identifier << std::endl;		
		std::cout << "--- Absolute Path: " << (*itr).second.strip_absolute_path << std::endl;	
		std::cout << "--- Filename: " << (*itr).second.strip_name << std::endl;	
		std::cout << "--- Offset: " << (*itr).second.strip_offset << std::endl;	
		std::cout << "--- Accesspoint: " << std::endl;
		std::cout << "---- Hostname: " << (*itr).second.strip_accesspoint.accesspoint_hostname << std::endl;
		std::cout << "---- IP address: " << (*itr).second.strip_accesspoint.accesspoint_ip_address << std::endl;		
		std::cout << "---- Port: " << (*itr).second.strip_accesspoint.accesspoint_port << std::endl;		
	}

	std::cout << "### POPFileMetaData ###" << std::endl;	
}