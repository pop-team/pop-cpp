#ifndef PARSER_COMMON_H
#define PARSER_COMMON_H

#include <vector>

#include "paroc_array.h"
#include "paroc_list.h"

typedef char string64[64];
typedef paroc_array<string64> CArrayString; //TODO: This seems like a terribly bad idea

typedef std::vector<char*> CArrayCharPtr;
typedef std::vector<char> CArrayChar;

int CountCodeLines(CArrayChar &code);

#endif
