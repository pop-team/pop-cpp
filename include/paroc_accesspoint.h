/**
 * File : accesspoint.h
 * Author : Tuan Anh Nguyen
 * Description : abstract network access point for parallel objects, used by POP-C++ runtime.
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  2011/9/13   Add the method GetNoAddRef() and the variable _noaddref to be able to handle the THIS keyword correctly
 */

#ifndef POPC_ACCESSPOINT_H
#define POPC_ACCESSPOINT_H
#include "paroc_base.h"

class paroc_accesspoint: public paroc_base
{
public:
	paroc_accesspoint();
	//  paroc_accesspoint(const char *hostport);
	paroc_accesspoint(const paroc_accesspoint &p);
	~paroc_accesspoint();


	void SetAccessString(const char *hostport);
	const char *GetAccessString() const;
	bool IsEmpty() const;
	bool operator ==(const paroc_accesspoint &p) const;
	paroc_accesspoint & operator =(const paroc_accesspoint &p);
	//bool AddProtocolAccessString(const paroc_string &as);
   const bool IsSecure() const;
   void SetSecure();
   const bool IsService() const;
   void SetAsService();
   void SetNoAddRef() ;
   const bool GetNoAddRef() const;

	virtual void Serialize(paroc_buffer &buf, bool pack);
private:
	char *endpoint;
   bool _service;
   bool _noaddref;
   int _security;
   enum security { NONSECURE, SECURE };
};

#endif
