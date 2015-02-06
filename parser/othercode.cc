#include "popc_intface.h"
#include "parser.h"
#include "paroc_utils.h"
#include <assert.h>

// OtherCode implementation
OtherCode::OtherCode(CodeFile *file): CodeData(file) {}

void OtherCode::GenerateCode(CArrayChar &output) {
    std::copy(code.begin(), code.end(), std::back_inserter(output));
}

void OtherCode::AddCode(char *newcode) {
    std::copy(newcode, newcode+strlen(newcode), std::back_inserter(code));
}

void OtherCode::AddCode(char *newcode, int n) {
    if(n>0) {
        std::copy(newcode, newcode+n, std::back_inserter(code));
    }
}

void OtherCode::AddCode(CArrayChar &newcode) {
    std::copy(newcode.begin(), newcode.end(), std::back_inserter(code));
}
