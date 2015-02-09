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
        output.InsertAt(-1,str,strlen(str));
    }

    sprintf(str, "\n// Generate code for pack directive\n");
    output.InsertAt(-1, str, strlen(str));

    //New code: BEGIN===================
    strcpy(str,"void paroc_registerbroker() {\n");
    output.InsertAt(-1, str, strlen(str));
    int n = objects.size();
    for(int i = 0; i < n; i++) {
        sprintf(str,"  %s%s::_popc_factory.test(\"%s\");\n", objects[i].c_str(), Class::POG_BROKER_POSTFIX, objects[i].c_str());
        output.InsertAt(-1,str,strlen(str));
    }
    strcpy(str,"}\n");
    output.InsertAt(-1, str, strlen(str));

    // Check if the object broker is packed
    strcpy(str, "bool CheckIfPacked(const char *objname)\n{\n\tif (objname==0) return false;\n");
    output.InsertAt(-1,str,strlen(str));
    int sz=objects.size();
    for(int j=0; j<sz; j++) {
        sprintf(str,"\n\tif (paroc_utils::isEqual(objname, \"%s\")) return true;",objects[j].c_str());
        output.InsertAt(-1,str,strlen(str));
    }
    strcpy(str,"\n\treturn false;\n}\n");
    output.InsertAt(-1,str,strlen(str));
    if(endline>0 && fname!=NULL) {
        sprintf(str,"\n# %d \"%s\"\n",endline,fname);
        output.InsertAt(-1,str,strlen(str));
    }

    if(endline>0 && fname!=NULL) {
        sprintf(str,"\n# %d \"%s\"\n",endline,fname);
        output.InsertAt(-1,str,strlen(str));
    }
    return;
}


void PackObject::AddObject(string64 objname) {
    for(auto& object : objects){
        if(object == objname){
            return;
        }
    }

    objects.push_back(objname);
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
