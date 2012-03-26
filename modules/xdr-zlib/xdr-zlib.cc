#include <string.h>
#include "paroc_buffer_xdr-zlib_factory.h"

extern "C"
{

	paroc_buffer_factory *ParocBufferFactory()
	{
		return new paroc_buffer_xdr_zlib_factory;
	}
}
