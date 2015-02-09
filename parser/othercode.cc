#include "popc_intface.h"
#include "parser.h"
#include "paroc_utils.h"
#include <assert.h>

// OtherCode implementation
OtherCode::OtherCode(CodeFile *file): CodeData(file) {}

void OtherCode::GenerateCode(CArrayChar &output) {
    output += code;
}

void OtherCode::AddCode(char *newcode) {
    code += std::string(newcode, strlen(newcode));
}

void OtherCode::AddCode(char *newcode, int n) {
    code += std::string(newcode, n);
}

void OtherCode::AddCode(const char *newcode, int n) {
    code += std::string(newcode, n);
}

void OtherCode::AddCode(CArrayChar &newcode) {
    code += std::string(newcode.data(), newcode.size());
}

void OtherCode::AddCode(const std::string& newcode) {
    code += newcode;
}
