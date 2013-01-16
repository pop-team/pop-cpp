/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: null-terminated string implementation
*/


#ifndef _POPC_STRING_H
#define _POPC_STRING_H

#include <string>

/**
 * @class paroc_string
 * @brief C++ class : Implementation of a string for POPC runtime.
 * @author Tuan Anh Nguyen
 */
class paroc_string
{
public:
	paroc_string();
	paroc_string(const char *x);
	paroc_string(const char *x, int n);
	paroc_string(std::string x);
	paroc_string(const paroc_string &x);

	~paroc_string();
	/**
	 * @brief Cast to a (char*)
	 */
	operator const char *() const;
	/**
	 * @brief Cast to a (std::string)
	 * @author Laurent Winkler
	 */
	operator std::string () const;

	/**
	 * @brief A constructor for paroc_string
	 * @param tname Name of the type (without * &)
	 */
	const char *operator =(const char *x);
	inline const char *c_str() {return data;};
	const paroc_string & operator =(const paroc_string &x);
	void operator +=(const char *x);
	paroc_string operator +  (const paroc_string &x);

	/**
	 * @brief Extracts a substring
	 * @param start
	 * @param end
	 * @param sub Output
	 */
	void substring(int start, int end, paroc_string &sub);

	int Length() const;
	/**
	 * @brief Returns a pointer to the (char*) data
	 */
	char *GetString();

protected:
	char *data;
};

typedef paroc_string POPString;

#endif










