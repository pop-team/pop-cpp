/*
AUTHORS: Tuan Anh Nguyen
DESCRIPTION: abstract network access point for parallel objects
 */

#ifndef POPC_ACCESSPOINT_H
#define POPC_ACCESSPOINT_H
#include "paroc_base.h"

/**
 * @class paroc_accesspoint
 * @brief abstract network access point for parallel objects, used by POP-C++ runtime.
 *
 * The accesspoint is a string that specifies the unique location of each object
 *
 * @author Tuan Anh Nguyen
 */
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

	virtual void Serialize(paroc_buffer &buf, bool pack);
private:
	char *endpoint;
};

#endif
