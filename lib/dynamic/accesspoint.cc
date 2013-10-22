/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of network access point of parallel objects.
 *
 *
 */
 
// Deeply need refactoring: POPC_AccessPoint instead of paroc_accesspoint 

#include "popc_intface.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

#include "paroc_accesspoint.h"
#include "paroc_utils.h"

/**
 * Accesspoint constructor
 */
paroc_accesspoint::paroc_accesspoint()
{
	endpoint=NULL;  
   _security=NONSECURE;
   _service=false;
   _noaddref=false;
}

/**
 * Accesspoint copy constructor
 */
paroc_accesspoint::paroc_accesspoint(const paroc_accesspoint &p)
{
	endpoint=NULL;
	SetAccessString(p.GetAccessString());
   if(p.IsSecure())
      _security = SECURE;
   else
      _security = NONSECURE;
   if(p.IsService())
      SetAsService();
   _noaddref=GetNoAddRef();
}

/**
 * Accesspoint destructor
 */
paroc_accesspoint::~paroc_accesspoint()
{
	if (endpoint!=NULL) free(endpoint);
}

/**
 * Set the different access in a string format. Each access is separated by a whit space.
 * @param hostport  Access string to set as mai access
 */
void paroc_accesspoint::SetAccessString(const char *hostport)
{
	if (endpoint!=hostport)
	{
		if (endpoint!=NULL)  free(endpoint);
		if (hostport!=NULL) endpoint=popc_strdup(hostport);
		else endpoint=NULL;
	}
}

char* paroc_accesspoint::GetAccessString() const
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
 * Check if the access point is in secure mode
 * @return TRUE if the access point is in secure mode
 */ 
bool paroc_accesspoint::IsSecure() const {
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
bool paroc_accesspoint::IsService() const{
   return _service;
}


/**
 * Get the boolean value that says if the creation of an interface with this access point must increment the internal counter
 */
bool paroc_accesspoint::GetNoAddRef() const{
   return _noaddref;
}

/**
 * ViSaG : clementval
 * Set the variable _service to TRUE
 */
void paroc_accesspoint::SetAsService(){
   _service = true;
}

void paroc_accesspoint::SetNoAddRef() {
   _noaddref = true;
}





void paroc_accesspoint::Serialize(paroc_buffer &buf, bool pack)
{
	if (pack)
	{
		POPString s(endpoint);
		buf.Push("url","POPString",1);
		buf.Pack(&s,1);
		buf.Pop();      

      int sec = _security;
      buf.Push("_security", "int", 1);
      buf.Pack(&sec, 1);
      buf.Pop();
      
      bool serv = _service;
      buf.Push("_service", "bool", 1);
      buf.Pack(&serv,1);
      buf.Pop();

      bool noadd = _noaddref;
      buf.Push("_noaddref", "bool", 1);
      buf.Pack(&noadd,1);
      buf.Pop();
	}
	else
	{
		POPString s;
		buf.Push("url","POPString",1);
		buf.UnPack(&s,1);
		buf.Pop();
		SetAccessString(s);    

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

      bool noadd;
      buf.Push("_noaddref", "bool", 1);
      buf.UnPack(&noadd,1);
      buf.Pop();
      if(noadd)
         SetNoAddRef();
     
	}
}
