#ifndef PARSER_COMMON_H
#define PARSER_COMMON_H

#include <vector>
#include <string>

#include "paroc_list.h"

typedef std::string string64; //TODO(BW) This should be removed I think
typedef std::vector<string64> CArrayString;

typedef std::string CArrayChar;

int CountCodeLines(const CArrayChar &code);

#endif
