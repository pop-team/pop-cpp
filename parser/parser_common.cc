#include <algorithm>

#include "parser_common.h"

int CountCodeLines(const std::string& code) {
    return std::count(code.begin(), code.end(), '\n');
}
