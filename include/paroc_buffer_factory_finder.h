#ifndef _POPC_BUFFER_FACTORY_FINDER_H
#define _POPC_BUFFER_FACTORY_FINDER_H

#include "paroc_buffer_factory.h"
#include "paroc_string.h"

#define MAX_FACTORY 10

/**
 * @class paroc_buffer_factory_finder
 * @brief Finds a buffer factory corresponding to the given buffer name, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class paroc_buffer_factory_finder
{
public:
	~paroc_buffer_factory_finder();

	int GetFactoryCount();
	paroc_buffer_factory * GetFactory(int index);
	paroc_buffer_factory * FindFactory(const paroc_string name);
	static paroc_buffer_factory_finder * GetInstance();
	bool GetBufferName(int index, paroc_string & bufferName);

private:
	paroc_buffer_factory_finder();
	void *LoadPlugin(char *fname, paroc_buffer_factory * &f);

	paroc_buffer_factory * bfArray[MAX_FACTORY];
	int size;
	void *plugins[MAX_FACTORY];

	static paroc_buffer_factory_finder* bff;

};
#endif
