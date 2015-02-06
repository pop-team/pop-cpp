
#include "parser_common.h"

//CodeData implementation
int CountCodeLines(CArrayChar &code) {
    int n=code.size();
    char *tmp=code;
    int l=0;
    while(n>0) {
        if(*tmp=='\n') {
            l++;
        }
        tmp++;
        n--;
    }
    return l;
}
