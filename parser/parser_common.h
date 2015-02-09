#ifndef PARSER_COMMON_H
#define PARSER_COMMON_H

#include <vector>
#include <string>
#include <cstring>
#include <cassert>

typedef std::vector<std::string> CArrayString;
typedef std::string CArrayChar;

int CountCodeLines(const std::string &code);

#endif
