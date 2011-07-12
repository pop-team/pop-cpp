#include <unistd.h>
#include <stdio.h>

#include "paroc_buffer_xml_factory.h"
#include "paroc_buffer_xml.h"

paroc_buffer_xml_factory::paroc_buffer_xml_factory(){
 
  //Xerces initialization
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    printf("FATAL ERROR:Xerces XML parser initialization failure...");
    XMLPlatformUtils::Terminate();
    exit(-1);
  }
}
paroc_buffer_xml_factory::~paroc_buffer_xml_factory(){

 //Xerces termination
  XMLPlatformUtils::Terminate();

}
paroc_buffer * paroc_buffer_xml_factory::CreateBuffer(){
  paroc_buffer * bufXML=new paroc_buffer_xml();
  return bufXML;
}

bool paroc_buffer_xml_factory::GetBufferName(paroc_string & bufferName){
   bufferName="xml";
   return true;
}


