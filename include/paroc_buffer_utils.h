#ifndef _POPC_BUFFER_UTILS_H
#define _POPC_BUFFER_UTILS_H
#define marshalString marshalstring

#include <string>
#include "paroc_buffer.h"
#include "paroc_memspool.h"

template <class T> void packarray (paroc_buffer &buf, T *param, int size, int flag, paroc_memspool *temp);

void marshalstring ( paroc_buffer &buf, char *str, int maxsize, int flag, paroc_memspool *temp);
//void marshalnull(paroc_buffer &buf, void * &param, int hint,  int flag, paroc_memspool *temp);


#endif
