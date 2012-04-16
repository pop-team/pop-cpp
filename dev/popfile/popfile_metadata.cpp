/**
 * PROJECT:		POPFile
 * AUTHOR:		clementval
 *	FILENAME:	popfile_metadata.cpp
 * CREATION:	03.25.2012
 * 
 */

#include "tinyxml/tinyxml.h"
#include "popfile_metadata.h"




const char* POPFileMetaData::POPFILE_METADATA_COMMENT = "POPFile v1.0 - THIS FILE HAS BEEN GENERATED, DO NOT MODIFY IT";
const char* POPFileMetaData::POPFILE_METADATA_NODE_ROOT = "popfile";
const char* POPFileMetaData::POPFILE_METADATA_NODE_INFOS = "infos";
const char* POPFileMetaData::POPFILE_METADATA_NODE_INFOS_ABS_PATH = "absolute-path";
const char* POPFileMetaData::POPFILE_METADATA_NODE_INFOS_ORGI_NAME = "original-name";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIPS = "strips";
const char* POPFileMetaData::POPFILE_METADATA_NODE_STRIP = "strip";
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
void POPFileMetaData::save(const char* filename)
{
	meta_loaded = false;
	
	//
	TiXmlDocument doc;  
	TiXmlElement* msg;
	TiXmlComment* comment;
	
	//Create comment element
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild(decl); 
	comment = new TiXmlComment();
	comment->SetValue(POPFILE_METADATA_COMMENT);  
	doc.LinkEndChild(comment);  	
	
	//Create root element
	TiXmlElement* root = new TiXmlElement(POPFILE_METADATA_NODE_ROOT);  
	doc.LinkEndChild(root); 
	
	//Create the infos element and tie it to root 
	TiXmlElement* infos = new TiXmlElement(POPFILE_METADATA_NODE_INFOS);  
	root->LinkEndChild(infos);
	
	//
	TiXmlElement* infos_absolute_path = new TiXmlElement(POPFILE_METADATA_NODE_INFOS_ABS_PATH); 
	infos->LinkEndChild(infos_absolute_path);
	infos_absolute_path->LinkEndChild(new TiXmlText(meta_info.info_absolute_path));	
	
	TiXmlElement* infos_original_name = new TiXmlElement(POPFILE_METADATA_NODE_INFOS_ORGI_NAME);   	
	infos->LinkEndChild(infos_original_name);	
	infos_original_name->LinkEndChild(new TiXmlText(meta_info.info_original_name));	
	
	TiXmlElement* strips = new TiXmlElement(POPFILE_METADATA_NODE_STRIPS); 
	
	MetaDataStripMap::const_iterator itr;
	for(itr = meta_strips.begin(); itr != meta_strips.end(); ++itr){
		
		TiXmlElement* strip = new TiXmlElement(POPFILE_METADATA_NODE_STRIP);
		if((*itr).second.strip_is_local)
			strip->SetAttribute(POPFILE_METADATA_NODE_STRIP_ATTRIBUTE_LOCAL, "true");
		else
			strip->SetAttribute(POPFILE_METADATA_NODE_STRIP_ATTRIBUTE_LOCAL, "false");

		char buffer[10];

		TiXmlElement* strip_id = new TiXmlElement(POPFILE_METADATA_NODE_STRIP_ID);   	
		strip_id->LinkEndChild(new TiXmlText(convertInt((*itr).second.strip_identifier)));	
		strip->LinkEndChild(strip_id);	
			
		TiXmlElement* strip_abs_path = new TiXmlElement(POPFILE_METADATA_NODE_STRIP_ABS_PATH);   	
		strip_abs_path->LinkEndChild(new TiXmlText((*itr).second.strip_absolute_path));	
		strip->LinkEndChild(strip_abs_path);	
		
		TiXmlElement* strip_name = new TiXmlElement(POPFILE_METADATA_NODE_STRIP_STRIP_NAME);   	
		strip_name->LinkEndChild(new TiXmlText((*itr).second.strip_name));	
		strip->LinkEndChild(strip_name);	
		
		TiXmlElement* strip_offset = new TiXmlElement(POPFILE_METADATA_NODE_STRIP_OFFSET);   	
		strip_offset->LinkEndChild(new TiXmlText(convertLong((*itr).second.strip_offset)));	
		strip->LinkEndChild(strip_offset);
		
		TiXmlElement* strip_accesspoint = new TiXmlElement(POPFILE_METADATA_NODE_STRIP_AP); 
		TiXmlElement* strip_accesspoint_hostname = new TiXmlElement(POPFILE_METADATA_NODE_STRIP_AP_HOSTNAME); 
		strip_accesspoint_hostname->LinkEndChild(new TiXmlText((*itr).second.strip_accesspoint.accesspoint_hostname));	
		TiXmlElement* strip_accesspoint_ip_address = new TiXmlElement(POPFILE_METADATA_NODE_STRIP_AP_IPADDR); 
		strip_accesspoint_ip_address->LinkEndChild(new TiXmlText((*itr).second.strip_accesspoint.accesspoint_ip_address));			
		TiXmlElement* strip_accesspoint_port = new TiXmlElement(POPFILE_METADATA_NODE_STRIP_AP_PORT);   		
		strip_accesspoint_port->LinkEndChild(new TiXmlText(convertInt((*itr).second.strip_accesspoint.accesspoint_port)));		
		
		strip_accesspoint->LinkEndChild(strip_accesspoint_hostname);
		strip_accesspoint->LinkEndChild(strip_accesspoint_ip_address);
		strip_accesspoint->LinkEndChild(strip_accesspoint_port);			
		
		strip->LinkEndChild(strip_accesspoint);
			
	 	strips->LinkEndChild(strip);	
	}
	
	
	root->LinkEndChild(strips); 		
	
	
	doc.SaveFile(filename);  
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
	meta_info.info_absolute_path = pElem->GetText();
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
		
		if(meta_offset == 0) meta_offset = strip.strip_offset;	

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
	meta_loaded = true;
	return true;
}


/** 
 * Print data to cout
 */
bool POPFileMetaData::is_loaded()
{
	return meta_loaded;
}

long POPFileMetaData::get_offset()
{
	return meta_offset;
}

void POPFileMetaData::set_offset(long value)
{
	meta_offset = value;
}

std::string POPFileMetaData::get_filename(){
	return meta_info.info_original_name;
}

void POPFileMetaData::set_filename(std::string filename, std::string path){
	meta_info.info_original_name = filename;
	meta_info.info_absolute_path = path;
}

std::string POPFileMetaData::convertInt(int number) {
   std::stringstream ss;
   ss << number;
   return ss.str();
}

std::string POPFileMetaData::convertLong(long number) {
   std::stringstream ss;
   ss << number;
   return ss.str();
}

/** 
 * Print data to cout
 */
void POPFileMetaData::dump_to_cout()
{
	cout << "### POPFileMetaData ###" << popcendl;
	cout << "- Infos :" << popcendl;	
	cout << "-- Absolute Path: " << meta_info.info_absolute_path << popcendl;	
	cout << "-- Original Filename: " << meta_info.info_original_name << popcendl;
	cout << "- Strips: " << popcendl;	
	
	MetaDataStripMap::const_iterator itr;
	for(itr = meta_strips.begin(); itr != meta_strips.end(); ++itr){
		cout << "-- Strip: (local) - " << (*itr).second.strip_is_local << popcendl;
		cout << "--- Identifier: " << (*itr).second.strip_identifier << popcendl;		
		cout << "--- Absolute Path: " << (*itr).second.strip_absolute_path << popcendl;	
		cout << "--- Filename: " << (*itr).second.strip_name << popcendl;	
		cout << "--- Offset: " << (*itr).second.strip_offset << popcendl;	
		cout << "--- Accesspoint: " << popcendl;
		cout << "---- Hostname: " << (*itr).second.strip_accesspoint.accesspoint_hostname << popcendl;
		cout << "---- IP address: " << (*itr).second.strip_accesspoint.accesspoint_ip_address << popcendl;		
		cout << "---- Port: " << (*itr).second.strip_accesspoint.accesspoint_port << popcendl;		
	}

	cout << "### POPFileMetaData ###" << popcendl;	
}