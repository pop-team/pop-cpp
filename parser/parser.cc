#include <ctype.h>

#include "parser.h"
#include "paroc_utils.h"

#define MIN_CLASSID 1000

CodeData::CodeData(CodeFile *file) {
    codeFile=file;
}

CodeData::~CodeData() {
}

void CodeData::GenerateCode(std::string& /*output*/) {
}
