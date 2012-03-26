#include <string.h>
#include "paroc_buffer_raw-zlib_factory.h"

extern "C"
{

	paroc_buffer_factory *ParocBufferFactory()
	{
		return new paroc_buffer_raw_zlib_factory;
	}
}
