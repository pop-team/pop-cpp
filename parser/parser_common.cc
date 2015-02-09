
#include "parser_common.h"

//CodeData implementation
int CountCodeLines(CArrayChar &code) {
    //TODO(BW) Once replaced by std::vector, this code should
    //use std::count
    int l=0;
    for(int i = 0; i < code.size(); ++i){
        if(code[i] == '\n'){
            ++l;
        }
    }
    return l;
}
