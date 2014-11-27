#ifndef PARSER_COMMON_H
#define PARSER_COMMON_H
#include "paroc_array.h"
#include "paroc_list.h"


typedef char string64[64];
typedef paroc_array<int> CArrayInt;
typedef paroc_array<string64> CArrayString;
typedef paroc_array<char *> CArrayCharPtr;
typedef paroc_array<char> CArrayChar;

int CountCodeLines(CArrayChar &code);

#endif
