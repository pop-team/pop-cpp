/**
 * File : accesspoint.cc
 * Author : Tuan Anh Nguyen
 * Description : implementation of network access point of parallel objects
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#include <stdio.h>
#include <string.h>
#include "paroc_accesspoint.h"
#include "paroc_utils.h"

//paroc_accesspoint class

paroc_accesspoint::paroc_accesspoint()
{
	endpoint=NULL;  
   _security=NONSECURE;
   _service=false;
}
// paroc_accesspoint::paroc_accesspoint(const char *hostport)
// {
//   endpoint=NULL;
//   SetAccessString(hostport);
// }

paroc_accesspoint::paroc_accesspoint(const paroc_accesspoint &p)
{
	endpoint=NULL;
	SetAccessString(p.GetAccessString());
//   SetPKI(p.GetPKI());
   if(p.IsSecure())
      _security = SECURE;
   else
      _security = NONSECURE;
   if(p.IsService())
      SetAsService();
}

paroc_accesspoint::~paroc_accesspoint()
{
	if (endpoint!=NULL) free(endpoint);
}

void paroc_accesspoint::SetAccessString(const char *hostport)
{
	if (endpoint!=hostport)
	{
		if (endpoint!=NULL)  free(endpoint);
		if (hostport!=NULL) endpoint=strdup(hostport);
		else endpoint=NULL;
	}
}
const char* paroc_accesspoint::GetAccessString() const
{
	return endpoint;
}

bool paroc_accesspoint::IsEmpty() const
{
	return (endpoint==NULL);
}

bool paroc_accesspoint::operator ==(const paroc_accesspoint &p) const
{
	return paroc_utils::isEqual(endpoint,p.GetAccessString());
}

paroc_accesspoint & paroc_accesspoint::operator =(const paroc_accesspoint &p)
{
	SetAccessString(p.GetAccessString());
   if(p.IsSecure())
      SetSecure();
   if(p.IsService())
      SetAsService();
	return *this;
}


/**
 * ViSaG : clementval
 * Get the Public Key Identifer of the Node running this object
 * @return The public key of the node running the parallel object pointed by this access point
 */
/*
const paroc_string paroc_accesspoint::GetPKI() const {
   return endpoint_pki;
}
*/

/**
 * ViSaG : clementval
 * Set the public key if the node running the parallel object pointed by this access point
 * @param pki The public key of the node
 */
/*
void paroc_accesspoint::SetPKI(paroc_string pki){
   endpoint_pki = pki;
}
*/
/**
 * ViSaG : clementval
 * Check if the access point is in secure mode
 * @return TRUE if the access point is in secure mode
 */ 
const bool paroc_accesspoint::IsSecure() const {
   if(_security==SECURE)
      return true;
   return false;
}

/**
 * ViSaG : clementval
 * Set the access point in a secure mode
 */
void paroc_accesspoint::SetSecure(){
   _security = SECURE;
}


/**
 * ViSaG : clementval
 * Return true is the accesspoint is reffered to a service
 * @return TRUE if the parallel object pointed by the access point is a service
 */
const bool paroc_accesspoint::IsService() const{
   return _service;
}

/**
 * ViSaG : clementval
 * Set the variable _service to TRUE
 */
void paroc_accesspoint::SetAsService(){
   _service = true;
}



void paroc_accesspoint::Serialize(paroc_buffer &buf, bool pack)
{
	if (pack)
	{
		paroc_string s(endpoint);
		buf.Push("url","paroc_string",1);
		buf.Pack(&s,1);
		buf.Pop();      
      
   /*   paroc_string pk(endpoint_pki);
      buf.Push("pki", "paroc_string", 1);
      buf.Pack(&pk, 1);
      buf.Pop();*/

      int sec = _security;
      buf.Push("_security", "int", 1);
      buf.Pack(&sec, 1);
      buf.Pop();
      
      bool serv = _service;
      buf.Push("_service", "bool", 1);
      buf.Pack(&serv,1);
      buf.Pop();
	}
	else
	{
		paroc_string s;
		buf.Push("url","paroc_string",1);
		buf.UnPack(&s,1);
		buf.Pop();
		SetAccessString(s);    

  /*    paroc_string pk;
      buf.Push("pki", "paroc_string", 1);
      buf.UnPack(&pk, 1);
      buf.Pop();
      SetPKI(pk);*/

      int sec;
      buf.Push("_security", "int", 1);
      buf.UnPack(&sec, 1);
      buf.Pop();
      if(sec==SECURE)
         SetSecure(); 

      bool serv;
      buf.Push("_service", "bool", 1);
      buf.UnPack(&serv,1);
      buf.Pop();
      if(serv)
         SetAsService();
     
	}
}
