
#ifndef PAROC_BUFFER_XML_H
#define PAROC_BUFFER_XML_H

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>


#include "paroc_accesspoint.h"
#include "paroc_string.h"
#include "paroc_od.h"
#include "paroc_interface.h"
#include "paroc_exception.h"
#include "paroc_array.h"

#define PAROC_URI "http://www.eif.ch/~i01nbras"
#define PAROC_PREFIX "paroc"
#define SOAP_ENVELOPE_URI "http://schemas.xmlsoap.org/soap/envelope/"
#define SOAP_ENVELOPE_PREFIX "soap-env"
#define SOAP_ENCODING_URI "http://schemas.xmlsoap.org/soap/encoding/"
#define SOAP_ENCODING_PREFIX "soap-enc"
#define XML_SCHEMA_INSTANCE_URI "http://www.w3.org/1999/XMLSchema-instance"
#define XML_SCHEMA_URI "http://www.w3.org/1999/XMLSchema"
#define N_STD_TYPES 11

XERCES_CPP_NAMESPACE_USE 

/**
 * The paroc_buffer_xml.
 * This class allows to create a instance using the encoding xml.
 */

typedef paroc_array<char> paroc_char_array;

class paroc_buffer_xml : public paroc_buffer{
public:

  paroc_buffer_xml();
  ~paroc_buffer_xml();
  
  void Finish();
  
  void Reset();
  void print();  
  void print(DOMNode * node);
  
  virtual void SetHeader(const paroc_message_header &data);
  
  virtual void Push(const char *paramname, const char *paramtype, int nelem);
  virtual void Pop();
  
  virtual void Pack(const int *data, int n);
  virtual void UnPack(int *data, int n);
  
  virtual void Pack(const unsigned *data, int n);
  virtual void UnPack(unsigned *data, int n);
  
  virtual void Pack(const long *data, int n);
  virtual void UnPack(long *data, int n);
  
  virtual void Pack(const unsigned long *data, int n);
  virtual void UnPack(unsigned long *data, int n);
  
  virtual void Pack(const short *data, int n);
  virtual void UnPack(short *data, int n);
  
  virtual void Pack(const unsigned short *data, int n);
  virtual void UnPack(unsigned short *data, int n);
  
  virtual void Pack(const bool *data, int n);
  virtual void UnPack(bool *data, int n);
  
  virtual void Pack(const char *data, int n);
  virtual void UnPack(char *data, int n);
  
  virtual void Pack(const unsigned char *data, int n);
  virtual void UnPack(unsigned char *data, int n);
  
  virtual void Pack(const float *data, int n);
  virtual void UnPack(float *data, int n);
  
  virtual void Pack(const double *data, int n);
  virtual void UnPack(double *data, int n);
  
  virtual void Pack(const paroc_string *list, int n);
  virtual void UnPack(paroc_string *list, int n);
  
  virtual bool Send(paroc_combox &s, paroc_connection *conn);
  virtual bool Recv(paroc_combox &s, paroc_connection *conn);
  
 private:

  int isStandardType(const char * type);

  DOMDocument* myDocument;
  DOMImplementation* impl;
  DOMElement* currentElem;
  
  paroc_list<paroc_string> paramStack;
  paroc_list<int> arrayStack;
  bool forPacking;
  static char stdTypes[N_STD_TYPES][16];
  static char XMLTypes[N_STD_TYPES][16];
};

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy 
//  trancoding of char* data to XMLCh data.
// ---------------------------------------------------------------------------
class XStr
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XStr(const char* const toTranscode)
    {
        // Call the private transcoding method
        fUnicodeForm = XMLString::transcode(toTranscode);
    }

    ~XStr()
    {
        XMLString::release(&fUnicodeForm);
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh* unicodeForm() const
    {
        return fUnicodeForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh*   fUnicodeForm;
};

#define X(str) XStr(str).unicodeForm()


#endif // PAROC_BUFFER_XML_H

