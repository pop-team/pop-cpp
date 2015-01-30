#include "popc_intface.h"
#include "parser.h"
#include "paroc_utils.h"
#include <assert.h>

// OtherCode implementation
OtherCode::OtherCode(CodeFile *file): CodeData(file), code(0, 8096) {
}

void OtherCode::GenerateCode(CArrayChar &output) {
    int n = code.GetSize();
    if(n) {
        output.InsertAt(-1, (char *)code, n);
    }
}

void OtherCode::AddCode(char *newcode) {
    code.InsertAt(-1, newcode, strlen(newcode));
}
void OtherCode::AddCode(char *newcode, int n) {
    if(n>0) {
        code.InsertAt(-1,newcode,n);
    }
}

void OtherCode::AddCode(CArrayChar &newcode) {
    int n=newcode.GetSize();
    if(n) {
        code.InsertAt(-1,(char *)newcode,n);
    }
}
