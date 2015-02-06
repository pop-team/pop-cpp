#include <algorithm>

#include "parser_common.h"

//CodeData implementation
int CountCodeLines(CArrayChar &code) {
    return std::count(code.begin(), code.end(), '\n');
}
