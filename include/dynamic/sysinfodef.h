/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 01/01/2005
 * @brief system information
 *
 *
 */

#include "paroc_array.h"

struct HostInfo
{
	char name[64];
	char val[256];
};
typedef paroc_array<HostInfo> HostInfoDB;
typedef paroc_array<char *> CArrayCharPtr;
typedef paroc_array<int>  CArrayInt;
