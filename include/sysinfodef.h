#include "paroc_array.h"

struct HostInfo
{
	char name[64];
	char val[256];
};
typedef paroc_array<HostInfo> HostInfoDB;
typedef paroc_array<char *> CArrayCharPtr;
typedef paroc_array<int>  CArrayInt;
