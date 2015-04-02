#include "popc_intface.h"
#include "parser.h"
#include "pop_utils.h"
#include <assert.h>

// OtherCode implementation
OtherCode::OtherCode(CodeFile *file): CodeData(file) {}

void OtherCode::GenerateCode(std::string& output) {
    output += code;
}

void OtherCode::AddCode(const char *newcode) {
    code += newcode;
}

void OtherCode::AddCode(const char *newcode, int n) {
    code += std::string(newcode, n);
}

void OtherCode::AddCode(const std::string& newcode) {
    code += newcode;
}
