#include "popc_intface.h"
#include "parser.h"
#include "paroc_utils.h"
#include <assert.h>

//PackObject implementation

PackObject::PackObject(CodeFile *file): CodeData(file), startline(-1), endline(-1) {}

void PackObject::GenerateCode(CArrayChar &output) {
    char str[1024];
    char *fname = GetCodeFile()->GetFileName();
    if(startline > 0 && fname != NULL) {
        sprintf(str,"\n# %d \"%s\"\n",startline,fname);
        std::copy(str, str+strlen(str), std::back_inserter(output));
    }

    sprintf(str, "\n// Generate code for pack directive\n");
    std::copy(str, str+strlen(str), std::back_inserter(output));

    //New code: BEGIN===================
    strcpy(str,"void paroc_registerbroker() {\n");
    std::copy(str, str+strlen(str), std::back_inserter(output));
    int n = objects.size();
    for(int i = 0; i < n; i++) {
        sprintf(str,"  %s%s::_popc_factory.test(\"%s\");\n", objects[i], Class::POG_BROKER_POSTFIX, objects[i]);
        std::copy(str, str+strlen(str), std::back_inserter(output));
    }
    strcpy(str,"}\n");
    std::copy(str, str+strlen(str), std::back_inserter(output));

    // Check if the object broker is packed
    strcpy(str, "bool CheckIfPacked(const char *objname)\n{\n\tif (objname==0) return false;\n");
    std::copy(str, str+strlen(str), std::back_inserter(output));
    int sz=objects.size();
    for(int j=0; j<sz; j++) {
        sprintf(str,"\n\tif (paroc_utils::isEqual(objname, \"%s\")) return true;",objects[j]);
        std::copy(str, str+strlen(str), std::back_inserter(output));
    }
    strcpy(str,"\n\treturn false;\n}\n");
    std::copy(str, str+strlen(str), std::back_inserter(output));
    if(endline>0 && fname!=NULL) {
        sprintf(str,"\n# %d \"%s\"\n",endline,fname);
        std::copy(str, str+strlen(str), std::back_inserter(output));
    }

    if(endline>0 && fname!=NULL) {
        sprintf(str,"\n# %d \"%s\"\n",endline,fname);
        std::copy(str, str+strlen(str), std::back_inserter(output));
    }
    return;
}


void PackObject::AddObject(string64 objname) {
    int n=objects.size();
    for(int i=0; i<n; i++) if(paroc_utils::isEqual(objects[i],objname)) {
            return;
        }

    objects.resize(n+1);
    strcpy(objects[n],objname);
}

int PackObject::GetNumObject() {
    return objects.size();
}


void  PackObject::SetStartLine(int l) {
    startline=l;
}

void  PackObject::SetEndLine(int l) {
    endline=l;
}
