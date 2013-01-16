/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: buffer factory abstraction.
 */

#ifndef POPC_BUFFER_FACTORY_H
#define POPC_BUFFER_FACTORY_H

#include <paroc_buffer.h>

/*This abstract class declares an interface creating abstract buffer*/
class paroc_buffer;

/**
 * @class paroc_buffer_factory
 * @brief Buffer factory abstraction, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class paroc_buffer_factory
{
public:
	paroc_buffer_factory();
protected:
	virtual ~paroc_buffer_factory();

public:
	virtual void Destroy();

	virtual paroc_buffer* CreateBuffer()=0;

	virtual bool GetBufferName(paroc_string & bufferName)=0;
};

#endif // POPC_BUFFER_FACTORY_H
