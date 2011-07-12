#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "paroc_service.h"
#include "paroc_buffer_xml.h"
#include <xercesc/framework/StdOutFormatTarget.hpp>

char paroc_buffer_xml::stdTypes[N_STD_TYPES][16]={"int","unsigned int","long","unsigned long","short","unsigned short","bool","char","unsigned char","float","double"};
char paroc_buffer_xml::XMLTypes[N_STD_TYPES][16]={"int","unsignedInt","long","unsignedLong","short","unsignedShort","bool","byte","unsignedByte","float","double"};

paroc_buffer_xml::paroc_buffer_xml(){
  
  myDocument=NULL;
  currentElem=NULL;
  impl = DOMImplementationRegistry::getDOMImplementation(X("Core"));
  if(impl==NULL) paroc_exception::paroc_throw(UNKNOWN_EXCEPTION);
  Reset();
}
paroc_buffer_xml::~paroc_buffer_xml(){ 
	
  //Free the memory of the DOM Document
  myDocument->release();

}

void paroc_buffer_xml::Finish(){
}

void paroc_buffer_xml::Reset()
{
  
  //Free the old DOM Tree...
  if(myDocument!=NULL) myDocument->release();
 
  //Prepare the header for the message
  //DOM document creation
  myDocument = impl->createDocument(
				    X(SOAP_ENVELOPE_URI),
				    X("Envelope"),        
				    0);                 
  
  //Create the SOAP Envelope
  myDocument->getDocumentElement()->setPrefix(X(SOAP_ENVELOPE_PREFIX));
  
  //Add Namespace to the SOAP envelope
  myDocument->getDocumentElement()->setAttribute(X("xmlns:xsi"), X(XML_SCHEMA_INSTANCE_URI));
  myDocument->getDocumentElement()->setAttribute(X("xmlns:xsd"), X(XML_SCHEMA_URI));
  myDocument->getDocumentElement()->setAttribute(X("xmlns:soap-enc"), X(SOAP_ENCODING_URI));    	
  
  //Create SOAP body
  DOMElement*  elem = myDocument->createElementNS(X(SOAP_ENVELOPE_URI), X("body"));
  elem->setPrefix(X(SOAP_ENVELOPE_PREFIX));
  myDocument->getDocumentElement()->appendChild(elem); 	
  currentElem=elem;

  paramStack.RemoveAll();
  arrayStack.RemoveAll();

  forPacking=true;

}

void paroc_buffer_xml::SetHeader(const paroc_message_header &data)
{
  
  header=data;

  const char * methodName = data.GetMethodName();

  char method[256];
  if (methodName!=NULL) strcpy(method,methodName);
  else strcpy(method,"Unknown");

  int type=data.GetType();

  if(type==TYPE_RESPONSE)
    {
      strcat(method, "Response");
    }
  else if (type==TYPE_EXCEPTION)
    {
      strcat(method, "Exception");
    }


  try
    {
      DOMElement*  elem = myDocument->createElementNS(X(PAROC_URI), X(method));
      elem->setPrefix(X(PAROC_PREFIX));
      currentElem->appendChild(elem);
      currentElem=elem;
      paroc_string s="method element";
    }
  catch(...)
    {
      printf("********* AN EXCEPTION OCCURS !!! ***************\n");
    }
}
void paroc_buffer_xml::Push(const char *paramname, const char *paramtype, int nelem){

  paroc_string sName=paramname;

  bool isPreviousAnArray=false;
  if(arrayStack.GetCount()>0)
    if(arrayStack.GetAt(arrayStack.GetHeadPosition())>1) isPreviousAnArray=true;

  bool isArray=false;
  if(nelem>1) isArray=true;
  
  if(forPacking)
    {
      try
	{
	  DOMElement*  elem;
	  if(isPreviousAnArray)
	    { 
	      elem=myDocument->createElement(X("item"));
	      currentElem->appendChild(elem);
	      currentElem=elem;
	    }
	  
	  char strTab[256];
	  elem=myDocument->createElement(X(paramname));
	  int typeNumber=isStandardType(paramtype);
	  if(isArray)
	    {
	      elem->setAttribute(X("xsi:type"), X("soap_enc:Array"));
	      
	      if(typeNumber>=0)
		sprintf(strTab, "%s:%s[%i]", "xsd", XMLTypes[typeNumber], nelem);
	      else
		sprintf(strTab, "%s:%s[%i]", PAROC_PREFIX, paramtype, nelem);
	      
	      elem->setAttribute(X("soap_enc:arrayType"), X(strTab));
	    }
	  else
	    {
	      if(typeNumber>=0)
		sprintf(strTab, "%s:%s", "xsd", XMLTypes[typeNumber]);
	      else
		sprintf(strTab, "%s:%s", PAROC_PREFIX, paramtype);
	      elem->setAttribute(X("xsi:type"), X(strTab));
	    }
	  currentElem->appendChild(elem);
	  currentElem=elem;
	}
      catch(...)
	{
	  printf("********* An XML exception occurs paroc_buffer_xml::Push !!! ***************\n");
	}
    }
  else
    {
      try
	{
	  
	  DOMNodeList* childList = currentElem->getChildNodes(); 
	  for(int i=0; i<childList->getLength(); i++){
	    DOMElement * crtElem;
	    if(isPreviousAnArray)
	      crtElem = (DOMElement *)childList->item(i)->getFirstChild();
	    else 
	      crtElem = (DOMElement *)childList->item(i);
	    const XMLCh * tagName = crtElem->getTagName();
	    if(XMLString::compareIString(tagName,X(paramname))==0){
	      currentElem=crtElem;
	      break;
	    }
	  }

	}	  
      catch(...)
	{
	  printf("********* An XML exception occurs paroc_buffer_xml::Push !!! ***************\n");
	}
    }
      paramStack.AddHead(sName);
      arrayStack.AddHead(nelem);
}
void paroc_buffer_xml::Pop(){

  paramStack.RemoveHead();
  arrayStack.RemoveHead();

  currentElem=(DOMElement *)currentElem->getParentNode();
  

}
  
void paroc_buffer_xml::Pack(const int *data, int n)
{
  if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%d", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%d", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    } 
}
void paroc_buffer_xml::UnPack(int *data, int n)
{
 
  if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atoi(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atoi(value);
      XMLString::release(&value);
    }  
}

void paroc_buffer_xml::Pack(const unsigned *data, int n)
{ 
 if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%i", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%i", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    }   
}

void paroc_buffer_xml::UnPack(unsigned *data, int n){


 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atoi(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atoi(value);
      XMLString::release(&value);
    }  	
}

void paroc_buffer_xml::Pack(const long *data, int n)
{
if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%i", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%i", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    }  
}

void paroc_buffer_xml::UnPack(long *data, int n){


 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atol(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atol(value);
      XMLString::release(&value);
    }   
}

void paroc_buffer_xml::Pack(const unsigned long *data, int n)
{
if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%u", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%u", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    } 
}


void paroc_buffer_xml::UnPack(unsigned long *data, int n){


 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atol(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atol(value);
      XMLString::release(&value);
    }  
}

void paroc_buffer_xml::Pack(const short *data, int n)
{
if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%i", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%i", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    } 
}

void paroc_buffer_xml::UnPack(short *data, int n){


 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atoi(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atoi(value);
      XMLString::release(&value);
    }  
}

void paroc_buffer_xml::Pack(const unsigned short *data, int n)
{

  if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%u", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%u", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    } 
}

void paroc_buffer_xml::UnPack(unsigned short *data, int n){

 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atoi(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atoi(value);
      XMLString::release(&value);
    }   
}

void paroc_buffer_xml::Pack(const bool *data, int n)
{
if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%i", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%i", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    } 
}

void paroc_buffer_xml::UnPack(bool *data, int n){
  

 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atoi(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atoi(value);
      XMLString::release(&value);
    }  
}

void paroc_buffer_xml::Pack(const char *data, int n)
{

if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%i", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%i", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    }   
}

void paroc_buffer_xml::UnPack(char *data, int n){
  

 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atoi(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atoi(value);
      XMLString::release(&value);
    }  
}

void paroc_buffer_xml::Pack(const unsigned char *data, int n)
{

if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%u", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%u", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    }  
}

void paroc_buffer_xml::UnPack(unsigned char *data, int n){

 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atoi(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atoi(value);
      XMLString::release(&value);
    }  
}

void paroc_buffer_xml::Pack(const float *data, int n)
{

if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%.18f", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%.18f", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    }  
}

void paroc_buffer_xml::UnPack(float *data, int n){
  
 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atof(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atof(value);
      XMLString::release(&value);
    }  
}

void paroc_buffer_xml::Pack(const double *data, int n)
{

if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; i++)
	{
	  sprintf(value, "%.18f", *(data+i));
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X(value));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      sprintf(value, "%.18f", *data);
      DOMText* text = myDocument->createTextNode(X(value));
      currentElem->appendChild(text);
    } 
}

void paroc_buffer_xml::UnPack(double *data, int n){

 if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  char* value = XMLString::transcode(crtElem->getFirstChild()->getNodeValue());
	  *(data+i) = atof(value);
	  XMLString::release(&value);
	}
    }
  else
    {
      char* value = XMLString::transcode(currentElem->getFirstChild()->getNodeValue());
      *data = atof(value);
      XMLString::release(&value);
    }  
}


void paroc_buffer_xml::Pack(const paroc_string *string, int n)
{
 
  if(n<1) return;
  char value[256];
  if(n>1)
    {
      for(int i=0; i<n; string++)
	{
	  DOMElement* item = myDocument->createElement(X("item"));
	  DOMText* text = myDocument->createTextNode(X((const char *)(*string)));
	  item->appendChild(text);
	  currentElem->appendChild(item);
	}
    }
  else
    {
      DOMText* text = myDocument->createTextNode(X((const char *)(*string)));
      currentElem->appendChild(text);
    } 
 
}

void paroc_buffer_xml::UnPack(paroc_string *string, int n)
{
  if(n<1) return;
  if(n>1)
    {
      DOMNodeList* childList = currentElem->getChildNodes(); 
      for(int i=0; i<childList->getLength(); i++)
	{
	  DOMElement * crtElem = (DOMElement *)childList->item(i);
	  DOMElement* elem = (DOMElement*)crtElem->getFirstChild();
	  if(elem!=NULL){ 
	    char* value = XMLString::transcode(elem->getNodeValue());
	    *(string+i)=value;
	    XMLString::release(&value);
	  }
	  else
	    *(string+i)="";
	}
    }
  else
    {
      DOMElement* elem = (DOMElement*)currentElem->getFirstChild();
      if(elem!=NULL){ 
	char* value = XMLString::transcode(elem->getNodeValue());
	*string = value;
	XMLString::release(&value);
      }
      else
	*string="";
    }  
 
}


bool paroc_buffer_xml::Send(paroc_combox &combox, paroc_connection *conn)
{
  
  //DEBUG("Dans send\n");
  //print();
  DOMElement* methodElem = (DOMElement*)myDocument->getFirstChild()->getFirstChild()->getFirstChild();
  if(methodElem==NULL) paroc_exception::paroc_throw(PAROC_BUFFER_FORMAT);

  int type = header.GetType();

  char msgType[32];
  sprintf(msgType, "%d", type);
  methodElem->setAttribute(X("Type"), X(msgType));
  
  if(type==TYPE_REQUEST){

    char classID[32];
    char methodID[32];
    char semantics[32];
    
    sprintf(classID, "%d", header.GetClassID());
    sprintf(methodID, "%d", header.GetMethodID());
    sprintf(semantics, "%d", header.GetSemantics());

    methodElem->setAttribute(X("ClassID"), X(classID));
    methodElem->setAttribute(X("MethodID"), X(methodID));
    methodElem->setAttribute(X("Semantics"), X(semantics));
  }
  else if(type==TYPE_EXCEPTION){

    char exceptionType[32];
    sprintf(exceptionType, "%d", header.GetExceptionCode());
    methodElem->setAttribute(X("ExceptionType"), X(exceptionType));
  }

  DOMWriter * theSerializer = impl->createDOMWriter();
  if(theSerializer==NULL) paroc_exception::paroc_throw(PAROC_BUFFER_FORMAT);

  DOMNode * doc = myDocument->getDocumentElement();
  if(doc==NULL) paroc_exception::paroc_throw(PAROC_BUFFER_FORMAT);
  
  XMLCh * msg = theSerializer->writeToString(*doc);
  if(msg==NULL) paroc_exception::paroc_throw(PAROC_BUFFER_FORMAT);
  
  char * strMsg=XMLString::transcode(msg);
  //printf("[Send] Message size:%d\n", strlen(strMsg));
  int len=strlen(strMsg);
  int count=combox.Send(strMsg, len, conn); 
  if (len!=count) rprintf("Send error: return: %d, size=%d\n",count, len);

  theSerializer->release();
  XMLString::release(&msg);
  XMLString::release(&strMsg);
  return (len==count);

}


bool paroc_buffer_xml::Recv(paroc_combox &combox, paroc_connection *conn)
{

  Reset();
  
  forPacking=false;
 
  paroc_array<char> xmlMsg;
  char pattern[]="</soap-env:Envelope>";
  int len=strlen(pattern);

  char currentChar[256]; 
  int pos=0;

  while (pos<len)
    {
      int n=combox.Recv(currentChar, len-pos, conn);
      if (n<=0)
	{
	  rprintf("READ PROBLEM : Cannot read (return:%d, required: %d) !!!\n",n, len-pos);
	  return false;
	}
      
      xmlMsg.InsertAt(-1, currentChar,n);
      for (char *p=currentChar; n>0; n--, p++) 
	{
	  if(*p==pattern[pos])
	    {
	      pos++;
	    }
	  else
	    {
	      pos=0;
	    }
	}
    }

  XercesDOMParser theParser;

  try
    {
      char  memBufId[]="XMLMessage";
      MemBufInputSource memBufIS( (const XMLByte*)((char *)xmlMsg)
				  , xmlMsg.GetSize()
				  , memBufId
				  , false
				  );
      
      theParser.parse(memBufIS);
    }
  catch(const XMLException& toCatch)
    {
      rprintf("XML ERROR : Cannot parse the XML message...\n");
      print();
      paroc_exception::paroc_throw(PAROC_BUFFER_FORMAT);
    }


  if(myDocument!=NULL) myDocument->release();
  myDocument=theParser.adoptDocument(); 
  currentElem=myDocument->getDocumentElement();
    
  DOMElement* methodElem = (DOMElement*)myDocument->getFirstChild()->getFirstChild()->getFirstChild();
  if(methodElem==NULL) paroc_exception::paroc_throw(PAROC_BUFFER_FORMAT);
  currentElem=methodElem;
  
  char * cType;
  cType=XMLString::transcode(methodElem->getAttribute(X("type")));
  unsigned int type = atoi(cType);
  XMLString::release(&cType);
  
  header.SetType(type);
  //printf("Message type=%d\n", header.GetType());

  if(type==TYPE_REQUEST)
    {
      char * cClassID=XMLString::transcode(methodElem->getAttribute(X("ClassID")));
      header.SetClassID(atoi(cClassID));
      XMLString::release(&cClassID);

      char * cMethodID=XMLString::transcode(methodElem->getAttribute(X("MethodID")));
      header.SetMethodID(atoi(cMethodID));
      XMLString::release(&cMethodID);
      
      char * cSem=XMLString::transcode(methodElem->getAttribute(X("Semantics")));
      header.SetSemantics(atoi(cSem));
      XMLString::release(&cSem);

      //printf("ClassID=%d\n", header.GetClassID());
      //printf("MethodID=%d\n", header.GetMethodID());
      //printf("Semantics=%d\n", header.GetSemantics());

    }
  else if(type==TYPE_EXCEPTION)
    {
      char * cSem=XMLString::transcode(methodElem->getAttribute(X("Semantics")));
      header.SetExceptionCode(atoi(cSem));
      XMLString::release(&cSem);
    }

  return true;

}

void paroc_buffer_xml::print(){
  
  printf("\n\n\n\n");
  DOMWriter *theSerializer = impl->createDOMWriter();
  XMLFormatTarget *myFormTarget;
  myFormTarget= new StdOutFormatTarget();
  
  DOMNode *doc = myDocument->getFirstChild();
  theSerializer->writeNode(myFormTarget, *doc);
  printf("\n");
  delete(theSerializer);
}

void paroc_buffer_xml::print(DOMNode * nodeToPrint){
  
  printf("\n\n\n\n");
  DOMWriter *theSerializer = impl->createDOMWriter();
  XMLFormatTarget *myFormTarget;
  myFormTarget= new StdOutFormatTarget();
  
  theSerializer->writeNode(myFormTarget, *nodeToPrint);
  printf("\n");
  delete(theSerializer);
}

int paroc_buffer_xml::isStandardType(const char * type)
{
    
  for(int i=0; i<N_STD_TYPES; i++)
    if(strcmp(stdTypes[i], type)==0) return i;
  return -1;

}
