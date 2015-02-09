#include <algorithm>

#include "parser_common.h"

int CountCodeLines(const CArrayChar& code) {
    return std::count(code.begin(), code.end(), '\n');
}
